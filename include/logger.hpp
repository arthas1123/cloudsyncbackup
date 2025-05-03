#pragma once
#include <string>
#include "event_bus.hpp"
#include <memory>

class Logger
{
public:
    static void init(const std::string &logDir);
    static void info(const std::string &msg);
    static void error(const std::string &msg);

    static void subscribeToBackupEvent(EventBus &bus);
};
