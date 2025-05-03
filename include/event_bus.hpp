// event_bus.hpp
#pragma once
#include <functional>
#include <map>
#include <string>
#include <vector>
#include <memory>

class EventBase
{
public:
    virtual ~EventBase() = default;
};

class EventBus
{
public:
    using Handler = std::function<void(const std::shared_ptr<EventBase> &)>;

    template <typename EventType>
    void subscribe(const Handler &handler)
    {
        const std::string typeName = typeid(EventType).name();
        handlers_[typeName].push_back(handler);
    }

    template <typename EventType>
    void publish(const std::shared_ptr<EventType> &event)
    {
        const std::string typeName = typeid(EventType).name();
        auto it = handlers_.find(typeName);
        if (it != handlers_.end())
        {
            for (const auto &handler : it->second)
            {
                handler(event);
            }
        }
    }

private:
    std::map<std::string, std::vector<Handler>> handlers_;
};

// 定義簡單的備份事件
class BackupEvent : public EventBase
{
public:
    std::string filePath;
    std::string backupPath;
    std::string status; // SUCCESS / FAILED
    std::string message;

    BackupEvent(const std::string &file, const std::string &backup,
                const std::string &stat, const std::string &msg = "")
        : filePath(file), backupPath(backup), status(stat), message(msg) {}
};
