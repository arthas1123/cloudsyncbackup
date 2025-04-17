#pragma once
#include <string>
#include <thread>
#include <atomic>
#include "task_queue.hpp"

inline constexpr const char *EXIT_TASK = "__EXIT__";

class BackupWorker
{
public:
    BackupWorker(TaskQueue<std::string> &taskQueue, const std::string backupDir);
    ~BackupWorker();

    void start();
    void stop();

private:
    void run(); // 執行緒主迴圈

    TaskQueue<std::string> &taskQueue_;
    std::string backupDir_; // backup folder path
    std::thread thread_;
    std::atomic<bool> running_;
};
