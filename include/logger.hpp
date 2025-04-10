#pragma once
#include <string>

class Logger
{
public:
    static void init(const std::string &logDir);
    static void info(const std::string &msg);
    static void error(const std::string &msg);
};
