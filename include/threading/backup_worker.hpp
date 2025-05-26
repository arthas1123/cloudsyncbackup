#pragma once
#include <string>
#include "event_bus.hpp"
#include <vector>
#include <thread>
#include <mutex>
#include "event_bus.hpp"

class BackupWorker
{
public:
    static void subscribe(EventBus &bus);
    static void shutdown(); // new shutdown method

private:
    std::string backupDir_; // 若不再使用，可考慮移除
    static std::vector<std::thread> worker_threads_;
    static std::mutex threads_mutex_;
    static bool shutdown_;
};
