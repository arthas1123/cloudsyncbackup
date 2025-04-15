#include "threading/backup_worker.hpp"
#include <iostream>
#include "backup.hpp"

BackupWorker::BackupWorker(TaskQueue<std::string> &taskQueue)
    : taskQueue_(taskQueue), running_(false) {}

BackupWorker::~BackupWorker()
{
    stop();
}

void BackupWorker::start()
{
    running_ = true;
    thread_ = std::thread(&BackupWorker::run, this);
}

void BackupWorker::stop()
{
    running_ = false;
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void BackupWorker::run()
{
    while (running_)
    {
        std::string file = taskQueue_.pop();
        if (!file.empty())
        {
            std::cout << "📦 處理備份任務：" << file << std::endl;
            // TODO: 在這裡呼叫 Backup::run(...) 或你自己的備份邏輯
            // Backup::run(file, "backup_storage"); // 假設備份到 backup_storage 資料夾
            printf("備份到 %s\n", file.c_str());
        }
    }
}
