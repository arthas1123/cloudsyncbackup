#include <iostream>
#include <filesystem>
#include "config.hpp"
#include "logger.hpp"
#include "emoji.hpp"
#include "database.hpp"
#include "backup.hpp"

namespace fs = std::filesystem;

int main()
{
    std::string configPath = "config.json";
    AppConfig config = ConfigLoader::loadConfig(configPath);

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

    std::cout << Emoji::Rocket() << " cloudsyncbackup 啟動中...\n";

    // 處理路徑
    fs::path dbPath = config.dbPath;
    fs::path backupDir = config.backupDir;

    // 初始化資料庫
    Database db(dbPath.string());
    db.initialize();
    db.insertNote("5566"); // 之後可以改掉，這只是測試

    // 執行備份
    Backup::run(dbPath.string(), backupDir.string());

    return 0;
}
