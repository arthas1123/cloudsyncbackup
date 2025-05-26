#include <iostream>
#include <filesystem>
#include <memory>
#include "config.hpp"
#include "logger.hpp"
#include "emoji.hpp"
#include "database.hpp"
#include "backup.hpp"
#include "cli_parser.hpp"
#include "event_bus.hpp"
#include "event_recorder.hpp"
#include "threading/backup_worker.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{
    std::string configPath = "config.json";
    AppConfig config = ConfigLoader::loadConfig(configPath);

    // 初始化事件總線
    auto bus = std::make_shared<EventBus>();

    // 初始化事件記錄器
    std::shared_ptr<EventRecorder> recorder_ptr;
    try
    {
        // Construct EventRecorder first
        recorder_ptr = std::make_shared<EventRecorder>("events_log.json");
        recorder_ptr->subscribeToEvents(*bus); // Then, initialize its subscriptions
    }
    catch (const std::runtime_error &e)
    {
        Logger::error("初始化事件記錄器失敗：" + std::string(e.what())); // 或者直接 std::cerr 如果 Logger 未初始化
        return 1;
    }

    // 訂閱備份事件
    BackupWorker::subscribe(*bus);

    // emoji 控制
    if (!config.enableEmoji)
    {
        Emoji::enabled = false;
    }

    // log 控制
    if (config.enableLogging)
    {
        Logger::init(config.logDir);
        Logger::info("cloudsyncbackup 啟動");
    }

    Logger::info(Emoji::Rocket() + " cloudsyncbackup 啟動中...");

    // 處理路徑
    fs::path dbPath = config.dbPath;
    fs::path backupDir = config.backupDir;

    // 初始化資料庫
    Database db(dbPath.string());
    db.initialize();

    // 使用 CLI 解析器處理命令
    CLIParser::handle(argc, argv, dbPath.string(), backupDir.string(), *bus);
    Logger::info("Main: Initiating BackupWorker shutdown...");
    BackupWorker::shutdown();
    Logger::info("Main: BackupWorker shutdown complete.");
    Logger::info("cloudsyncbackup exiting normally.");

    return 0;
}
