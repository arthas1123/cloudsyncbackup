#pragma once
#include <string>

class Restore
{
public:
    static bool restoreLatest(const std::string &backupDir, const std::string &dbPath);
    static bool restoreFromFile(const std::string &backupFilePath, const std::string &dbPath);
    // static bool deleteBackup(const std::string &backupFile);
    // static bool deleteAllBackups(const std::string &backupDir);
};
