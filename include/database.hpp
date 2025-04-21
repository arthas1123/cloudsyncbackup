#pragma once
#include <string>
#include <vector>

struct BackupRecord
{
    int id;
    std::string filePath;
    std::string backupPath;
    std::string timestamp;
    std::string status;
    std::string errorMsg;
};

class Database
{
public:
    Database(const std::string &dbPath);
    ~Database();

    void initialize();
    bool logBackUp(const std::string &filePath,
                   const std::string &backupPath,
                   const std::string &timeStamp,
                   const std::string &status,
                   const std::string &errorMsg = "");
    bool getBackUpLog(int id, BackupRecord &record);
    int getBackUpLogCount();
    // bool updateBackUpLog(int id, const std::string &newContent);
    bool deleteBackLog(int id);
    void getAllBackupLogs();

private:
    std::string dbPath_;
    void *db_; // 目前還是 sqlite3*，先保留 void*
};
