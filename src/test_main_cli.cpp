#include <iostream>
#include <filesystem>
#include "config.hpp"
#include "logger.hpp"
#include "emoji.hpp"
#include "database.hpp"
#include "backup.hpp"
#include "cli_parser.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
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
    Database db("backup_log.db");
    db.initialize();
    CLIParser::handle(argc, argv, dbPath.string(), backupDir.string());
    return 0;
}
