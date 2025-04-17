#include "backup.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip>

namespace fs = std::filesystem;

// 🧠 靜態變數定義
std::chrono::system_clock::time_point Backup::lastBackupTime_ = std::chrono::system_clock::from_time_t(0);
std::string Backup::lastBackupPath_;
BackupStatus Backup::lastStatus_ = BackupStatus::FAILED;
std::string Backup::lastError_;
size_t Backup::backupCount_ = 0;

bool Backup::run(const std::string &dbPath, const std::string &backupDir)
{
    try
    {
        if (!fs::exists(dbPath))
        {
            lastStatus_ = BackupStatus::FAILED;
            lastError_ = "原始檔案不存在：" + dbPath;
            return false;
        }

        // 產生備份檔名（包含時間戳）
        auto now = std::chrono::system_clock::now();
        auto t = std::chrono::system_clock::to_time_t(now);
        std::stringstream ss;
        ss << std::put_time(std::localtime(&t), "%Y%m%d_%H%M%S");

        std::string filename = fs::path(dbPath).stem().string() + "_" + ss.str() + ".db";
        fs::path destPath = fs::path(backupDir) / filename;

        // 建立目標資料夾（若不存在）
        fs::create_directories(backupDir);

        // 執行備份（複製檔案）
        fs::copy_file(dbPath, destPath, fs::copy_options::overwrite_existing);

        // 更新狀態
        lastBackupTime_ = now;
        lastBackupPath_ = destPath.string();
        lastStatus_ = BackupStatus::SUCCESS;
        lastError_.clear();
        backupCount_++;

        std::cout << "✅ 備份成功：" << destPath << std::endl;
        return true;
    }
    catch (const std::exception &e)
    {
        lastStatus_ = BackupStatus::FAILED;
        lastError_ = e.what();
        std::cerr << "❌ 備份失敗：" << lastError_ << std::endl;
        return false;
    }
}

bool Backup::shouldBackup(const std::string &dbPath, int minIntervalSec)
{
    if (!fs::exists(dbPath))
        return false;

    auto mtime = fs::last_write_time(dbPath);

    // 🧠 安全轉換為 system_clock
    auto mtime_sys = std::chrono::system_clock::now() +
                     std::chrono::duration_cast<std::chrono::system_clock::duration>(
                         mtime - fs::file_time_type::clock::now());

    auto diff = std::chrono::duration_cast<std::chrono::seconds>(
                    mtime_sys - lastBackupTime_)
                    .count();

    if (diff >= minIntervalSec)
        return true;

    std::cout << "⏩ 略過備份（" << diff << " 秒內無變動）\n";
    return false;
}

// 狀態查詢方法
std::chrono::system_clock::time_point Backup::getLastBackupTime()
{
    return lastBackupTime_;
}

std::string Backup::getLastBackupFilename()
{
    return lastBackupPath_;
}

BackupStatus Backup::getLastStatus()
{
    return lastStatus_;
}

std::string Backup::getLastError()
{
    return lastError_;
}
