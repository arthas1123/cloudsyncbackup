#include "threading/backup_worker.hpp"
#include <iostream>
#include <thread>
#include "backup.hpp"
#include "event_bus.hpp"

void BackupWorker::subscribe(EventBus &bus)
{
    bus.subscribe<BackupRequestedEvent>([&bus](const std::shared_ptr<EventBase> &event)
                                        {
        auto backupEvent = std::static_pointer_cast<BackupRequestedEvent>(event);
        std::cout << "📦 收到備份事件：" << backupEvent->srcPath << std::endl;

        std::thread([=, &bus]()
        {
            Backup::run(backupEvent->srcPath, backupEvent->destPath);

            auto result = std::make_shared<BackupEvent>(
                backupEvent->srcPath,
                backupEvent->destPath,
                "SUCCESS",
                "備份與上傳完成（背景執行）");
            bus.publish(result);
        }).detach(); });
}
