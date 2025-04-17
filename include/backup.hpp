#pragma once
#include <string>
#include <chrono>

enum class BackupStatus
{
    SUCCESS,
    FAILED
};

class Backup
{
public:
    static bool run(const std::string &dbPath, const std::string &backupDir);
    static bool shouldBackup(const std::string &dbPath, int minIntervalSec = 60);

    // 狀態查詢
    static std::chrono::system_clock::time_point getLastBackupTime();
    static std::string getLastBackupFilename();
    static BackupStatus getLastStatus();
    static std::string getLastError();

private:
    // 狀態追蹤
    static std::chrono::system_clock::time_point lastBackupTime_;
    static std::string lastBackupPath_;
    static BackupStatus lastStatus_;
    static std::string lastError_;
    static size_t backupCount_;
};
