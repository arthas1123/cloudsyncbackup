#include "logger.hpp"
#include "event_bus.hpp"
#include <fstream>
#include <ctime>
#include <filesystem>

namespace fs = std::filesystem;

static std::ofstream logFile;

void Logger::init(const std::string &logDir)
{
    fs::create_directories(logDir);

    time_t now = time(nullptr);
    char filename[64];
    strftime(filename, sizeof(filename), "log_%Y%m%d.txt", localtime(&now));
    fs::path logPath = fs::path(logDir) / filename;

    logFile.open(logPath, std::ios::app);
}

void Logger::info(const std::string &msg)
{
    time_t now = time(nullptr);
    logFile << "[INFO] " << std::ctime(&now) << "  " << msg << std::endl;
}

void Logger::error(const std::string &msg)
{
    time_t now = time(nullptr);
    logFile << "[ERR ] " << std::ctime(&now) << "  " << msg << std::endl;
}

void Logger::subscribeToBackupEvent(EventBus &bus)
{
    bus.subscribe<BackupEvent>([](const std::shared_ptr<EventBase> &event)
                               {
                                   auto backup = std::static_pointer_cast<BackupEvent>(event);
                                   std::string message = "[BackupEvent] file: " + backup->filePath +
                                                         ", status: " + backup->status +
                                                         ", message: " + backup->message;
                                   Logger::info(message); });
}
