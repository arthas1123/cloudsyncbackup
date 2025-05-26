#include "threading/backup_worker.hpp"
#include <thread>
#include "backup.hpp"
#include "event_bus.hpp"
#include "logger.hpp"
#include <string> // Required for std::to_string
std::vector<std::thread> BackupWorker::worker_threads_;
std::mutex BackupWorker::threads_mutex_;
bool BackupWorker::shutdown_ = false;

void BackupWorker::subscribe(EventBus &bus)
{
    bus.subscribe<BackupRequestedEvent>([&bus](const std::shared_ptr<EventBase> &event)
                                        {
        std::shared_ptr<BackupRequestedEvent> backup_req_event;
        bool should_process = false;
        {
            std::lock_guard<std::mutex> lock(threads_mutex_);
            if (!shutdown_) {
                should_process = true;
                backup_req_event = std::static_pointer_cast<BackupRequestedEvent>(event);
            }
        }

        if (!should_process) {
            Logger::info("BackupWorker is shutting down. Ignoring new backup request.");
            return;
        }

        Logger::info("📦 收到備份事件：" + backup_req_event->srcPath);

        // Create the task for the new thread
        auto task = [backup_req_event, &bus]() {
            Backup backup_instance;
            bool success = backup_instance.run(backup_req_event->srcPath, backup_req_event->destPath /* this is backupDir */);

            std::string status_str = success ? "SUCCESS" : "FAILED";
            std::string msg;
            std::string result_backup_file_path;

            if (success) {
                msg = "備份完成（背景執行）";
                result_backup_file_path = backup_instance.getLastBackupFilename();
            } else {
                msg = "備份失敗（背景執行）: " + backup_instance.getLastError();
                result_backup_file_path = ""; // Or some other indicator for failed backup path
            }

            auto result_event = std::make_shared<BackupEvent>(
                backup_req_event->srcPath,
                result_backup_file_path,
                status_str,
                msg);

            bool do_publish = false;
            {
                std::lock_guard<std::mutex> lock(threads_mutex_); // Protect read of shutdown_
                if (!shutdown_) {
                    do_publish = true;
                }
            }

            if (do_publish) {
                 bus.publish(result_event);
            } else {
                Logger::info("BackupWorker is shutting down. Suppressing BackupEvent publication for: " + backup_req_event->srcPath);
            }
        };

        // Create, store, and start the thread under lock protection for worker_threads_
        {
            std::lock_guard<std::mutex> lock(threads_mutex_);
            // Re-check shutdown_ flag immediately before creating the thread
            // to minimize race window if subscribe handler itself is slow.
            if (!shutdown_) {
                worker_threads_.emplace_back(task);
            } else {
                 Logger::info("BackupWorker shutdown initiated before thread creation for: " + backup_req_event->srcPath + ". Task not started.");
            }
        } });
}

void BackupWorker::shutdown()
{
    std::vector<std::thread> threads_to_join_local;
    {
        std::lock_guard<std::mutex> lock(threads_mutex_);
        if (shutdown_)
        {
            Logger::info("BackupWorker already shutting down or shut down.");
            return;
        }
        shutdown_ = true;
        Logger::info("BackupWorker initiating shutdown...");
        threads_to_join_local.swap(worker_threads_); // Move threads to local vector
    }

    Logger::info("Joining " + std::to_string(threads_to_join_local.size()) + " worker threads...");
    for (auto &th : threads_to_join_local)
    {
        if (th.joinable())
        {
            th.join();
        }
    }
    Logger::info("All BackupWorker threads joined. BackupWorker shutdown complete.");
}
