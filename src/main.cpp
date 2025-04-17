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
    db.insertNote("1234"); // 之後可以改掉，這只是測試

    // 執行備份
    if (Backup::shouldBackup(dbPath.string(), 5)) // 單位：秒
    {
        Backup::run(dbPath.string(), backupDir.string());
    }
    else
    {
        std::cout << "🛑 無需備份：距離上次修改時間過短。\n";
    }
    return 0;
}
