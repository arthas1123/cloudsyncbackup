#include "threading/backup_worker.hpp"
#include <iostream>
#include "backup.hpp"

BackupWorker::BackupWorker(TaskQueue<std::string> &taskQueue, const std::string backupDir)
    : taskQueue_(taskQueue), backupDir_(backupDir), running_(false) {}

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
    taskQueue_.push(EXIT_TASK); // 發送退出訊號
    if (thread_.joinable())
    {
        thread_.join();
    }
}

void BackupWorker::run()
{
    while (true)
    {
        std::string task = taskQueue_.pop();

        if (task == EXIT_TASK)
        {
            std::cout << "🔴 停止備份工作者..." << std::endl;
            break; // 停止執行緒
        }

        if (!task.empty())
        {
            std::cout << "📦 處理備份任務：" << task << std::endl;
            // TODO: 在這裡呼叫 Backup::run(...) 或你自己的備份邏輯
            Backup::run(task, backupDir_); // 假設備份到 backup_storage 資料夾
            std::cout << "✅ 備份完成：" << task << " to " << backupDir_ << std::endl;
        }
    }
}
