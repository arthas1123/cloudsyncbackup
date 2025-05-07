#pragma once
#include <string>
#include "event_bus.hpp"

class BackupWorker
{
public:
    static void subscribe(EventBus &bus);

private:
    std::string backupDir_; // 若不再使用，可考慮移除
};
