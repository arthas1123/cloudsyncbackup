#include "backup.hpp"
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>
#include <iostream>

namespace fs = std::filesystem;

bool Backup::run(const std::string &dbPath, const std::string &backupDir)
{
    if (!fs::exists(dbPath))
    {
        std::cerr << "❌ 找不到資料庫檔案：" << dbPath << std::endl;
        return false;
    }

    if (!fs::exists(backupDir))
    {
        fs::create_directories(backupDir);
    }

    // 產生時間戳
    auto now = std::chrono::system_clock::now();
    auto t = std::chrono::system_clock::to_time_t(now);
    std::stringstream timestamp;
    timestamp << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S");

    // 設定備份檔案名稱
    std::string backupName = "backup_" + timestamp.str() + ".db";
    fs::path backupPath = fs::path(backupDir) / backupName;

    // 複製檔案
    try
    {
        fs::copy_file(dbPath, backupPath);
        std::cout << "✅ 備份成功：" << backupPath << std::endl;
        return true;
    }
    catch (fs::filesystem_error &e)
    {
        std::cerr << "❌ 備份失敗：" << e.what() << std::endl;
        return false;
    }
}
