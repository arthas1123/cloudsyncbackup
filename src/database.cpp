#include "database.hpp"
#include <sqlite3.h>
#include <iostream>

Database::Database(const std::string &dbPath)
    : dbPath_(dbPath), db_(nullptr)
{
    if (sqlite3_open(dbPath_.c_str(), (sqlite3 **)&db_) == SQLITE_OK)
    {
        std::cout << "📦 開啟資料庫成功：" << dbPath_ << std::endl;
    }
    else
    {
        std::cerr << "❌ 開啟資料庫失敗！\n";
    }
}

Database::~Database()
{
    if (db_)
    {
        sqlite3_close((sqlite3 *)db_);
        std::cout << "🧹 關閉資料庫\n";
    }
}

void Database::initialize()
{
    // const char *sql = "CREATE TABLE IF NOT EXISTS notes ("
    //                   "id INTEGER PRIMARY KEY AUTOINCREMENT, "
    //                   "content TEXT NOT NULL);";

    // char *errMsg = nullptr;
    // if (sqlite3_exec((sqlite3 *)db_, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    // {
    //     std::cerr << "❌ 建立資料表失敗：" << errMsg << std::endl;
    //     sqlite3_free(errMsg);
    // }

    const char *logTableSql = "CREATE TABLE IF NOT EXISTS backup_log ("
                              "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                              "file_path TEXT NOT NULL, "
                              "backup_path TEXT NOT NULL, "
                              "backup_time TEXT NOT NULL, "
                              "status TEXT NOT NULL, "
                              "error_message TEXT);";

    char *logErr = nullptr;
    if (sqlite3_exec((sqlite3 *)db_, logTableSql, nullptr, nullptr, &logErr) != SQLITE_OK)
    {
        std::cerr << "❌ 建立 backup_log 資料表失敗：" << logErr << std::endl;
        sqlite3_free(logErr);
    }
    else
    {
        std::cout << "📦 資料表初始化成功\n";
    }
}

bool Database::logBackUp(const std::string &filePath,
                         const std::string &backupPath,
                         const std::string &timeStamp,
                         const std::string &status,
                         const std::string &errorMsg)
{
    std::string sql = "INSERT INTO backup_log (file_path, backup_path, backup_time, status, error_message) VALUES (?, ?, ?, ?, ?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2((sqlite3 *)db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }
    sqlite3_bind_text(stmt, 1, filePath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, backupPath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, timeStamp.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, errorMsg.c_str(), -1, SQLITE_TRANSIENT);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool Database::getBackUpLog(int id, BackupRecord &record)
{
    std::string sql = "SELECT file_path, backup_path, backup_time, status, error_message FROM backup_log WHERE id = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2((sqlite3 *)db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool success = (sqlite3_step(stmt) == SQLITE_ROW);
    if (success)
    {
        record.id = id;
        record.filePath = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 0));
        record.backupPath = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 1));
        record.timestamp = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 2));
        record.status = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 3));
        record.errorMsg = reinterpret_cast<const char *>(sqlite3_column_text(stmt, 4));
    }
    sqlite3_finalize(stmt);
    return success;
}
int Database::getBackUpLogCount()
{
    const char *sql = "SELECT COUNT(*) FROM backup_log;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2((sqlite3 *)db_, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return -1;
    }
    int count = 0;
    if (sqlite3_step(stmt) == SQLITE_ROW)
    {
        count = sqlite3_column_int(stmt, 0);
    }
    sqlite3_finalize(stmt);
    return count;
}

bool Database::deleteBackLog(int id)
{
    std::string sql = "DELETE FROM backup_log WHERE id = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2((sqlite3 *)db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "❌ 刪除筆記失敗：" << sqlite3_errmsg((sqlite3 *)db_) << std::endl;
        return false;
    }
    sqlite3_bind_int(stmt, 1, id);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

// 獲取所有備份紀錄
// 備份用的表：保留並繼續維護
void Database::getAllBackupLogs()
{
    const char *sql = "SELECT id, file_path, backup_path, backup_time, status, error_message FROM backup_log ORDER BY id DESC;";
    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2((sqlite3 *)db_, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "❌ 無法查詢備份紀錄：" << sqlite3_errmsg((sqlite3 *)db_) << std::endl;
        return;
    }

    std::cout << "\n📋 備份紀錄列表：\n";
    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const char *file = (const char *)sqlite3_column_text(stmt, 1);
        const char *backup = (const char *)sqlite3_column_text(stmt, 2);
        const char *time = (const char *)sqlite3_column_text(stmt, 3);
        const char *status = (const char *)sqlite3_column_text(stmt, 4);
        const char *error = (const char *)sqlite3_column_text(stmt, 5);

        std::cout << "🔹 ID: " << id
                  << "\n    檔案：" << file
                  << "\n    備份：" << backup
                  << "\n    時間：" << time
                  << "\n    狀態：" << status
                  << "\n    錯誤：" << (error ? error : "無")
                  << "\n\n";
    }

    sqlite3_finalize(stmt);
}
