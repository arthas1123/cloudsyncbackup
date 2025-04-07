#pragma once
#include <string>
#include <vector>

class CLIParser
{
public:
    static void handle(int argc, char *argv[],
                       const std::string &dbPath,
                       const std::string &backupDir);
};
