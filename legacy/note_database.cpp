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
    const char *sql = "CREATE TABLE IF NOT EXISTS notes ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "content TEXT NOT NULL);";
    char *errMsg = nullptr;
    if (sqlite3_exec((sqlite3 *)db_, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "❌ 建立資料表失敗：" << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
}

bool Database::insertNote(const std::string &content)
{
    std::string sql = "INSERT INTO notes (content) VALUES (?);";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2((sqlite3 *)db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        return false;
    }
    sqlite3_bind_text(stmt, 1, content.c_str(), -1, SQLITE_TRANSIENT);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

std::vector<std::pair<int, std::string>> Database::getAllNotes()
{
    std::vector<std::pair<int, std::string>> result;
    const char *sql = "SELECT id, content FROM notes ORDER BY id DESC;";
    sqlite3_stmt *stmt = nullptr;

    if (sqlite3_prepare_v2((sqlite3 *)db_, sql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        return result;
    }

    while (sqlite3_step(stmt) == SQLITE_ROW)
    {
        int id = sqlite3_column_int(stmt, 0);
        const unsigned char *content = sqlite3_column_text(stmt, 1);
        result.emplace_back(id, std::string(reinterpret_cast<const char *>(content)));
    }

    sqlite3_finalize(stmt);
    return result;
}

bool Database::updateNote(int id, const std::string &newContent)
{
    std::string sql = "UPDATE notes SET content = ? WHERE id = ?;";
    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2((sqlite3 *)db_, sql.c_str(), -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "❌ 更新筆記失敗：" << sqlite3_errmsg((sqlite3 *)db_) << std::endl;
        return false;
    }
    sqlite3_bind_text(stmt, 1, newContent.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_int(stmt, 2, id);
    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    sqlite3_finalize(stmt);
    return success;
}

bool Database::deleteNote(int id)
{
    std::string sql = "DELETE FROM notes WHERE id = ?;";
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
