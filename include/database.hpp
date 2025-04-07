#pragma once
#include <string>
#include <vector>
#include <utility> // for std::pair

class Database
{
public:
    Database(const std::string &dbPath);
    ~Database();

    void initialize();
    bool insertNote(const std::string &content);
    std::vector<std::pair<int, std::string>> getAllNotes();
    bool updateNote(int id, const std::string &newContent);
    bool deleteNote(int id);

private:
    std::string dbPath_;
    void *db_; // 目前還是 sqlite3*，先保留 void*
};
