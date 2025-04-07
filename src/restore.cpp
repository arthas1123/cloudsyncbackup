#include "restore.hpp"
#include <filesystem>
#include <iostream>
#include <vector>
#include <algorithm>

namespace fs = std::filesystem;

bool Restore::restoreLatest(const std::string &backupDir, const std::string &dbPath)
{
    if (!fs::exists(backupDir))
    {
        std::cerr << "❌ 備份資料夾不存在：" << backupDir << std::endl;
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
        std::cerr << "⚠️ 沒有可用的備份檔案\n";
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
        std::cout << "✅ 成功還原自指定檔案：" << backupFilePath << std::endl;
        return true;
    }
    catch (const fs::filesystem_error &e)
    {
        std::cerr << "❌ 還原失敗：" << e.what() << std::endl;
        return false;
    }
}
