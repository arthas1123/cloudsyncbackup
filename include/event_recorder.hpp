#pragma once
#include <fstream>
#include <string>
#include <memory>
#include <mutex>
#include "event_bus.hpp"

class EventRecorder
{
public:
    EventRecorder(const std::string &filename);
    ~EventRecorder();

    void recordEvent(const std::shared_ptr<EventBase> &event);

private:
    std::ofstream logFile_;
    std::mutex mutex_;
};
