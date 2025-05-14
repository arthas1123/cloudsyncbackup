#include "event_recorder.hpp"
#include "event_bus.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

EventRecorder::EventRecorder(const std::string &filename)
{
    logFile_.open(filename, std::ios::app);
    if (!logFile_.is_open())
    {
        throw std::runtime_error("無法開啟事件記錄檔案");
    }
}

EventRecorder::~EventRecorder()
{
    if (logFile_.is_open())
    {
        logFile_.close();
    }
}

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
