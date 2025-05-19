#include "restore.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <algorithm>
#include "logger.hpp" // 確保 Logger 被包含

namespace fs = std::filesystem;

bool Restore::restoreLatest(const std::string &backupDir, const std::string &dbPath)
{
    if (!fs::exists(backupDir))
    {
        Logger::error("❌ Restore::restoreLatest: 備份資料夾不存在：" + backupDir);
        return false;
    }

    std::vector<fs::directory_entry> backups;
    for (const auto &entry : fs::directory_iterator(backupDir))
    {
        if (entry.path().extension() == ".db")
        {
            backups.push_back(entry);
        }
    }

    if (backups.empty())
    {
        Logger::info("⚠️ Restore::restoreLatest: 沒有可用的備份檔案");
        return false;
    }

    std::sort(backups.begin(), backups.end(), [](const auto &a, const auto &b)
              {
                  return a.path().filename().string() > b.path().filename().string(); // 最新的排最前
              });

    const auto &latestBackup = backups.front();
    try
    {
        fs::copy_file(latestBackup.path(), dbPath, fs::copy_options::overwrite_existing);
        std::cout << "✅ 成功還原自最新備份：" << latestBackup.path() << std::endl;
        return true;
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "❌ 還原失敗：" << e.what() << std::endl;
        return false;
    }
}

bool Restore::restoreFromFile(const std::string &backupFilePath, const std::string &dbPath)
{
    fs::path path = backupFilePath;
    if (!fs::exists(path))
    {
        std::cerr << "❌ 找不到指定備份檔案：" << backupFilePath << std::endl;
        return false;
    }

    try
    {
        fs::copy_file(path, dbPath, fs::copy_options::overwrite_existing);
        Logger::info("✅ 成功還原自指定檔案：" + backupFilePath); // 使用傳入的 backupFilePath
        return true;
    }
    catch (const fs::filesystem_error &e)
    {
        Logger::error("❌ Restore::restoreFromFile: 還原失敗：" + std::string(e.what())); // 修正函數名稱
        return false;
    }
}
