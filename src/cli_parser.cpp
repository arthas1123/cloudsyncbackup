#include "cli_parser.hpp"
#include "backup.hpp"
#include "restore.hpp"
#include "database.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>

namespace fs = std::filesystem;

void CLIParser::handle(int argc, char *argv[],
                       const std::string &dbPath,
                       const std::string &backupDir)
{
    if (argc < 2)
    {
        std::cout << "🧭 使用方法：\n"
                  << "  --backup                建立備份\n"
                  << "  --restore               還原最新備份\n"
                  << "  --list-backups          列出所有備份檔案\n"
                  << "  --delete-backup <file>  刪除指定備份檔\n"
                  << "  --add-note <content>    新增備註\n"
                  << "  --list-notes            列出所有備註\n";
        return;
    }

    std::string command = argv[1];

    if (command == "--backup")
    {
        Backup::run(dbPath, backupDir);
    }
    else if (command == "--restore")
    {
        Restore::restoreLatest(backupDir, dbPath);
    }
    else if (command == "--list-backups")
    {
        if (!fs::exists(backupDir))
        {
            std::cout << "❌ 備份資料夾不存在\n";
            return;
        }
        for (const auto &entry : fs::directory_iterator(backupDir))
        {
            if (entry.path().extension() == ".db")
            {
                std::cout << "📁 " << entry.path().filename() << std::endl;
            }
        }
    }
    else if (command == "--delete-backup")
    {
        if (argc < 3)
        {
            std::cerr << "⚠️ 請指定要刪除的備份檔名\n";
            return;
        }
        fs::path fileToDelete = fs::path(backupDir) / argv[2];
        if (fs::exists(fileToDelete))
        {
            fs::remove(fileToDelete);
            std::cout << "🗑️ 已刪除：" << fileToDelete.filename() << std::endl;
        }
        else
        {
            std::cerr << "❌ 找不到檔案：" << fileToDelete << std::endl;
        }
    }
    else if (command == "--add-note")
    {
        if (argc < 3)
        {
            std::cerr << "⚠️ 請提供備註內容\n";
            return;
        }
        std::string noteContent = argv[2];
        Database db(dbPath);
        db.initialize();
        if (db.insertNote(noteContent))
        {
            std::cout << "✅ 已新增備註：" << noteContent << std::endl;
        }
        else
        {
            std::cerr << "❌ 新增備註失敗\n";
        }
    }
    else if (command == "--list-notes")
    {
        Database db(dbPath);
        db.initialize();
        auto notes = db.getAllNotes();
        for (const auto &note : notes)
        {
            std::cout << "📝 ID: " << note.first << ", 內容: " << note.second << std::endl;
        }
    }
    else
    {
        std::cerr << "❓ 未知指令：" << command << "\n";
    }
}
