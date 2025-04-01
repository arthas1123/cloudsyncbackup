#include "database.hpp"
#include <iostream>

Database::Database(const std::string &dbPath)
    : dbPath_(dbPath), db_(nullptr)
{
    if (sqlite3_open(dbPath_.c_str(), &db_) == SQLITE_OK)
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
        sqlite3_close(db_);
        std::cout << "🧹 關閉資料庫\n";
    }
}

void Database::initialize()
{
    const char *sql = "CREATE TABLE IF NOT EXISTS notes ("
                      "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                      "content TEXT NOT NULL);";
    char *errMsg = nullptr;

    if (sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "❌ 建立資料表失敗：" << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "⚙️ 資料表建立完成\n";
    }
}

void Database::insertTestData()
{
    const char *sql = "INSERT INTO notes (content) VALUES ('這是測試資料');";
    char *errMsg = nullptr;

    if (sqlite3_exec(db_, sql, nullptr, nullptr, &errMsg) != SQLITE_OK)
    {
        std::cerr << "❌ 插入資料失敗：" << errMsg << std::endl;
        sqlite3_free(errMsg);
    }
    else
    {
        std::cout << "📝 成功插入測試資料\n";
    }
}
