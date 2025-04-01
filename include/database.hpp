#pragma once
#include <string>
#include <sqlite3.h>

class Database
{
public:
    Database(const std::string &dbPath);
    ~Database();
    void initialize();
    void insertTestData();

private:
    std::string dbPath_;
    sqlite3 *db_;
};
