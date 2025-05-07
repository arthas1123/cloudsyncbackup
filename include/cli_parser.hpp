#pragma once
#include <string>
#include <vector>
#include "event_bus.hpp"
class CLIParser
{
public:
    static void handle(int argc, char *argv[],
                       const std::string &dbPath,
                       const std::string &backupDir,
                       EventBus &bus);
};
