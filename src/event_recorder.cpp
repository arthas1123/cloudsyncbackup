#include "event_recorder.hpp"
#include "event_bus.hpp"
#include <nlohmann/json.hpp>
#include "logger.hpp" // For Logger::error

using json = nlohmann::json;

EventRecorder::EventRecorder(const std::string &filename) : logFile_(filename)
{
    if (!logFile_.is_open())
    {
        Logger::error("無法開啟事件記錄檔案: " + filename);
        throw std::runtime_error("無法開啟事件記錄檔案: " + filename);
    }
}

EventRecorder::~EventRecorder() = default;

void EventRecorder::recordEvent(const std::shared_ptr<EventBase> &event)
{
    std::lock_guard<std::mutex> lock(mutex_);
    json j;
    if (auto e = std::dynamic_pointer_cast<BackupEvent>(event))
    {
        j["type"] = "BackupEvent";
        j["filePath"] = e->filePath;
        j["backupPath"] = e->backupPath;
        j["status"] = e->status;
        j["message"] = e->message;
    }
    else if (auto e = std::dynamic_pointer_cast<BackupRequestedEvent>(event))
    {
        j["type"] = "BackupRequestedEvent";
        j["srcPath"] = e->srcPath;
        j["destPath"] = e->destPath;
    }
    else
    {
        j["type"] = "UnknownEvent";
    }

    logFile_ << j.dump() << std::endl;
}

void EventRecorder::subscribeToEvents(EventBus &bus)
{
    // Now it's safe to call shared_from_this()
    std::weak_ptr<EventRecorder> weakSelf = shared_from_this();

    bus.subscribe<BackupEvent>([weakSelf](const std::shared_ptr<EventBase> &event)
                               {
        if (auto selfLocked = weakSelf.lock()) {
            auto backupEvent = std::static_pointer_cast<BackupEvent>(event);
            selfLocked->recordEvent(backupEvent);
        } });

    bus.subscribe<BackupRequestedEvent>([weakSelf](const std::shared_ptr<EventBase> &event)
                                        {
        if (auto selfLocked = weakSelf.lock()) {
            auto backupRequestedEvent = std::static_pointer_cast<BackupRequestedEvent>(event);
            selfLocked->recordEvent(backupRequestedEvent);
        } });
}
