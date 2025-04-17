#include "threading/task_queue.hpp"
#include "threading/backup_worker.hpp"
#include <chrono>
#include <thread>
#include <iostream>

int main()
{
    TaskQueue<std::string> taskQueue;
    BackupWorker worker(taskQueue, "backup_storage");
    worker.start();

    // 模擬加入任務
    std::cout << "加入備份任務: mydata.db\n";
    taskQueue.push("mydata.db");
    taskQueue.push("mydata.db");
    taskQueue.push("mydata.db");

    // 等待一段時間讓備份完成
    std::this_thread::sleep_for(std::chrono::seconds(2));

    worker.stop();

    std::cout << "測試結束\n";
    return 0;
}
