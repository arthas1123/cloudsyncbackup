#include <iostream>
#include <filesystem>
#include "database.hpp"
#include "backup.hpp"

namespace fs = std::filesystem;

int main()
{

    fs::path basePath = ".."; // 回到根目錄
    fs::path dbPath = basePath / "mydata.db";
    fs::path backupDir = basePath / "backup_storage";

    std::cout << "🚀 cloudsyncbackup 啟動中...\n";

    Database db(dbPath.string());
    db.initialize();
    db.insertTestData();

    Backup::run(dbPath.string(), backupDir.string());

    return 0;
}
