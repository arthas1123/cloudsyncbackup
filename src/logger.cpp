#include "logger.hpp"
#include "event_bus.hpp"
#include <fstream>
#include <ctime>
#include <filesystem>
#include <iostream> // For std::cout, std::cerr

namespace fs = std::filesystem;

static std::ofstream logFile;
static std::mutex coutMutex; // Mutex for std::cout

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
    std::lock_guard<std::mutex> lock(coutMutex); // Acquire lock

    time_t now_tt = time(nullptr);
    char time_buf[80]; // Increased buffer size for strftime
    // Format time to avoid issues with std::ctime and its static buffer + newline
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&now_tt));

    std::string full_message = std::string("[INFO] ") + time_buf + "  " + msg;

    if (logFile.is_open())
    {
        logFile << full_message << std::endl;
    }
    std::cout << full_message << std::endl; // Output to console
}

void Logger::error(const std::string &msg)
{
    std::lock_guard<std::mutex> lock(coutMutex); // Acquire lock

    time_t now_tt = time(nullptr);
    char time_buf[80]; // Increased buffer size for strftime
    // Format time to avoid issues with std::ctime and its static buffer + newline
    strftime(time_buf, sizeof(time_buf), "%Y-%m-%d %H:%M:%S", localtime(&now_tt));

    std::string full_message = std::string("[ERR ] ") + time_buf + "  " + msg;

    if (logFile.is_open())
    {
        logFile << full_message << std::endl;
    }
    std::cerr << full_message << std::endl; // Output to console
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
