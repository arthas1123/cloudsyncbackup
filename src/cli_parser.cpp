#include "cli_parser.hpp"
#include "backup.hpp"
#include "restore.hpp"
#include "database.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "emoji.hpp"
#include "config.hpp"

namespace fs = std::filesystem;

void CLIParser::handle(int argc, char *argv[],
                       const std::string &dbPath,
                       const std::string &backupDir)
{
    // scan if --no-icons is present
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--no-icons")
        {
            Emoji::enabled = false;
            std::cout << "Emoji::Check() 已關閉圖示顯示\n";
            break;
        }
    }

    if (argc < 2)
    {
        std::cout << Emoji::Menu() << "使用方法：\n"
                  << "  --backup                建立備份\n"
                  << "  --restore               還原最新備份\n"
                  << "  --list-backups          列出所有備份檔案\n"
                  << "  --delete-backup <file>  刪除指定備份檔\n"
                  << "  --add-note <content>    新增備註\n"
                  << "  --list-notes            列出所有備註\n"
                  << "  --update-note <id> <content> 更新備註\n"
                  << "  --delete-note <id>      刪除指定備註\n"
                  << "  --no-icons              不顯示圖示\n"
                  << "  --help                  顯示此幫助訊息\n";

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
            std::cout << Emoji::Error() << "備份資料夾不存在\n";
            return;
        }
        for (const auto &entry : fs::directory_iterator(backupDir))
        {
            if (entry.path().extension() == ".db")
            {
                std::cout << Emoji::File() << entry.path().filename() << std::endl;
            }
        }
    }
    else if (command == "--delete-backup")
    {
        if (argc < 3)
        {
            std::cerr << Emoji::Warning() << "請指定要刪除的備份檔名\n";
            return;
        }
        fs::path fileToDelete = fs::path(backupDir) / argv[2];
        if (fs::exists(fileToDelete))
        {
            fs::remove(fileToDelete);
            std::cout << Emoji::Trash() << " 已刪除：" << fileToDelete.filename() << std::endl;
        }
        else
        {
            std::cerr << Emoji::Error() << " 找不到檔案：" << fileToDelete << std::endl;
        }
    }
    /*     else if (command == "--add-note")
        {
            if (argc < 3)
            {
                std::cerr << Emoji::Warning() << " 請提供備註內容\n";
                return;
            }
            std::string noteContent = argv[2];
            Database db(dbPath);
            db.initialize();
            if (db.insertNote(noteContent))
            {
                std::cout << Emoji::Check() << " 已新增備註：" << noteContent << std::endl;
            }
            else
            {
                std::cerr << Emoji::Error() << " 新增備註失敗\n";
            }
        } */
    /*     else if (command == "--list-notes")
        {
            Database db(dbPath);
            db.initialize();
            auto notes = db.getAllNotes();
            for (const auto &note : notes)
            {
                std::cout << Emoji::Note() << " ID: " << note.first << ", 內容: " << note.second << std::endl;
            }
        } */

    /*     else if (command == "--update-note")
        {
            if (argc < 4)
            {
                std::cerr << Emoji::Warning() << " 請提供備註 ID 和新內容\n";
                return;
            }
            int noteId = std::stoi(argv[2]);
            std::string newContent = argv[3];
            Database db(dbPath);
            db.initialize();
            if (db.updateNote(noteId, newContent))
            {
                std::cout << Emoji::Check() << " 已更新備註 ID: " << noteId << "，新內容: " << newContent << std::endl;
            }
            else
            {
                std::cerr << Emoji::Error() << " 更新備註失敗\n";
            }
        } */
    /*     else if (command == "--delete-note")
        {
            if (argc < 3)
            {
                std::cerr << Emoji::Warning() << " 請提供備註 ID\n";
                return;
            }
            int noteId = std::stoi(argv[2]);
            Database db(dbPath);
            db.initialize();
            if (db.deleteNote(noteId))
            {
                std::cout << Emoji::Trash() << " 已刪除備註 ID: " << noteId << std::endl;
            }
            else
            {
                std::cerr << Emoji::Error() << " 刪除備註失敗\n";
            }
        } */
    else if (command == "--help")
    {
        handle(1, nullptr, dbPath, backupDir);
    }
    else if (command == "--log")
    {
        std::string configPath = "config.json";
        AppConfig config = ConfigLoader::loadConfig(configPath);
        Database db(config.dbPath);
        db.getAllBackupLogs();
    }
    else if (command == "--show-backup-log")
    {
        Database db("backup_log.db");
        db.initialize();
        db.getAllBackupLogs();
    }

    else
    {
        std::cerr << Emoji::Question() << " 未知指令：" << command << "\n";
    }
}
