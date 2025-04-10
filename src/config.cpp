#include "config.hpp"
#include <fstream>
#include <nlohmann/json.hpp> // need to install nlohmann/json
using json = nlohmann::json;

AppConfig ConfigLoader::loadConfig(const std::string &configPath)
{
    AppConfig config;

    std::ifstream file(configPath);
    if (!file)
        return config; // 無設定檔就用預設

    json j;
    file >> j;

    if (j.contains("db_path"))
        config.dbPath = j["db_path"];
    if (j.contains("backup_dir"))
        config.backupDir = j["backup_dir"];
    if (j.contains("log_dir"))
        config.logDir = j["log_dir"];
    if (j.contains("enable_emoji"))
        config.enableEmoji = j["enable_emoji"];

    if (j.contains("cloud"))
    {
        const auto &c = j["cloud"];
        if (c.contains("enabled"))
            config.cloud.enabled = c["enabled"];
        if (c.contains("provider"))
            config.cloud.provider = c["provider"];
        if (c.contains("api_key"))
            config.cloud.apiKey = c["api_key"];
        if (c.contains("sync_on_backup"))
            config.cloud.syncOnBackup = c["sync_on_backup"];
    }

    return config;
}
