#pragma once
#include <string>

struct AppConfig
{
    std::string dbPath = "mydata.db";
    std::string backupDir = "backup_storage";
    std::string logDir = "logs";
    bool enableEmoji = true;
    bool enableLogging = true;

    struct CloudConfig
    {
        bool enabled = false;
        std::string provider;
        std::string apiKey;
        bool syncOnBackup = false;
    } cloud; // ✅ 注意這個分號跟變數名稱
};

class ConfigLoader
{
public:
    static AppConfig loadConfig(const std::string &configPath);
    static void saveConfig(const std::string &configPath, const AppConfig &config);
};
