#pragma once
#include <string>

class Backup
{
public:
    static bool run(const std::string &dbPath, const std::string &backupDir);
};
