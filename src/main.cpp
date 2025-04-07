#include <iostream>
#include <filesystem>
#include "cli_parser.hpp"

namespace fs = std::filesystem;

int main(int argc, char *argv[])
{

    fs::path basePath = ".."; // 回到根目錄
    fs::path dbPath = basePath / "mydata.db";
    fs::path backupDir = basePath / "backup_storage";
    CLIParser::handle(argc, argv, dbPath.string(), backupDir.string());
    return 0;
}
