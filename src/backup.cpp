#include "backup.hpp"
#include <nlohmann/json.hpp>
#include "sqlite3.h"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>
#include "database.hpp"

namespace fs = std::filesystem;
using json = nlohmann::json;

namespace
{
    static constexpr const char *kStateFile = "backup_state.json";

    std::string nowToISO8601()
    {
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        std::tm tm = *std::localtime(&t);
        std::ostringstream oss;
        oss << std::put_time(&tm, "%Y-%m-%dT%H:%M:%S");
        return oss.str();
    }

    std::chrono::system_clock::time_point iso8601ToTimePoint(const std::string &iso8601)
    {
        std::tm tm = {};
        std::istringstream ss(iso8601);
        ss >> std::get_time(&tm, "%Y-%m-%dT%H:%M:%S");
        return std::chrono::system_clock::from_time_t(std::mktime(&tm));
    }
}

// 🧠 靜態變數定義
std::chrono::system_clock::time_point Backup::lastBackupTime_ = std::chrono::system_clock::from_time_t(0);
std::string Backup::lastBackupPath_;
BackupStatus Backup::lastStatus_ = BackupStatus::FAILED;
std::string Backup::lastError_;
size_t Backup::backupCount_ = 0;

bool Backup::logToDatabase(const std::string &dbFile,
                           const std::string &filePath,
                           const std::string &backupPath,
                           const std::string &isoTime,
                           const std::string &status,
                           const std::string &errorMsg)
{
    sqlite3 *db = nullptr;
    if (sqlite3_open(dbFile.c_str(), &db) != SQLITE_OK)
    {
        std::cerr << "❌ 無法開啟資料庫：" << dbFile << std::endl;
        return false;
    }

    // use raw string literal for SQL
    const char *sql = R"(
        CREATE TABLE IF NOT EXISTS backup_log (
            id INTEGER PRIMARY KEY AUTOINCREMENT,
            file_path TEXT NOT NULL,
            backup_path TEXT NOT NULL,
            backup_time TEXT NOT NULL,
            status TEXT NOT NULL,
            error_message TEXT
        );
    )";

    sqlite3_exec(db, sql, nullptr, nullptr, nullptr);

    const char *insertSql = R"(
        INSERT INTO backup_log (file_path, backup_path, backup_time, status, error_message)
        VALUES (?, ?, ?, ?, ?);
    )";

    sqlite3_stmt *stmt = nullptr;
    if (sqlite3_prepare_v2(db, insertSql, -1, &stmt, nullptr) != SQLITE_OK)
    {
        std::cerr << "❌ 無法準備 SQL 語句：" << sqlite3_errmsg(db) << std::endl;
        sqlite3_close(db);
        return false;
    }

    sqlite3_bind_text(stmt, 1, filePath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 2, backupPath.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 3, isoTime.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 4, status.c_str(), -1, SQLITE_TRANSIENT);
    sqlite3_bind_text(stmt, 5, errorMsg.empty() ? "" : errorMsg.c_str(), -1, SQLITE_TRANSIENT);

    bool success = (sqlite3_step(stmt) == SQLITE_DONE);
    if (!success)
    {
        std::cerr << "❌ 無法執行 SQL 語句：" << sqlite3_errmsg(db) << std::endl;
        return false;
    }
    sqlite3_finalize(stmt);
    sqlite3_close(db);
    return success;
}

bool Backup::run(const std::string &dbPath, const std::string &backupDir)
{
    Database db("backup_log.db");
    db.initialize();
    try
    {
        if (!fs::exists(dbPath))
        {
            lastStatus_ = BackupStatus::FAILED;
            lastError_ = "原始檔案不存在：" + dbPath;
            return false;
        }

        // 產生備份檔名（包含時間戳）
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S");

        std::string filename = fs::path(dbPath).stem().string() + "_" + ss.str() + ".db";
        fs::path destPath = fs::path(backupDir) / filename;

        // 建立目標資料夾（若不存在）
        fs::create_directories(backupDir);

        // 執行備份（複製檔案）
        fs::copy_file(dbPath, destPath, fs::copy_options::overwrite_existing);

        // 更新狀態
        lastBackupTime_ = now;
        lastBackupPath_ = destPath.string();
        lastStatus_ = BackupStatus::SUCCESS;
        lastError_.clear();
        backupCount_++;

        std::cout << "✅ 備份成功：" << destPath << std::endl;

        db.logBackUp(dbPath, destPath.string(), nowToISO8601(), "SUCCESS", "");
        // Backup::logToDatabase("backup_log.db", dbPath, destPath.string(), nowToISO8601(), "SUCCESS", "");
        return true;
    }
    catch (const std::exception &e)
    {
        lastStatus_ = BackupStatus::FAILED;
        lastError_ = e.what();
        std::cerr << "❌ 備份失敗：" << lastError_ << std::endl;
        // Backup::logToDatabase("backup_log.db", dbPath, "", nowToISO8601(), "FAILED", lastError_);
        db.logBackUp(dbPath, "", nowToISO8601(), "FAILED", lastError_);
        return false;
    }
}

bool Backup::shouldBackup(const std::string &dbPath, int minIntervalSec)
{
    if (!fs::exists(dbPath))
        return false;

    auto mtime = fs::last_write_time(dbPath);

    // 🧠 安全轉換為 system_clock
    auto mtime_sys = std::chrono::system_clock::now() +
                     std::chrono::duration_cast<std::chrono::system_clock::duration>(
                         mtime - fs::file_time_type::clock::now());

    auto diff = std::chrono::duration_cast<std::chrono::seconds>(
                    mtime_sys - lastBackupTime_)
                    .count();

    if (diff >= minIntervalSec)
        return true;

    std::cout << "⏩ 略過備份（" << diff << " 秒內無變動）\n";
    return false;
}

// 狀態查詢方法
std::chrono::system_clock::time_point Backup::getLastBackupTime()
{
    return lastBackupTime_;
}

std::string Backup::getLastBackupFilename()
{
    return lastBackupPath_;
}

BackupStatus Backup::getLastStatus()
{
    return lastStatus_;
}

std::string Backup::getLastError()
{
    return lastError_;
}
size_t Backup::getBackupCount()
{
    return backupCount_;
}
