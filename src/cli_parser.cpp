#include "cli_parser.hpp"
#include "backup.hpp"
#include "restore.hpp"
#include "database.hpp"
#include <iostream>
#include <filesystem>
#include <algorithm>
#include "emoji.hpp"
#include "config.hpp"
#include "logger.hpp" // 確保 Logger 被包含

namespace fs = std::filesystem;

void CLIParser::handle(int argc, char *argv[],
                       const std::string &dbPath,
                       const std::string &backupDir,
                       EventBus &bus)
{
    // scan if --no-icons is present
    for (int i = 1; i < argc; ++i)
    {
        if (std::string(argv[i]) == "--no-icons")
        {
            Emoji::enabled = false;
            Logger::info("Emoji::Check() 已關閉圖示顯示");
            break;
        }
    }

    if (argc < 2)
    {
        std::cout << Emoji::Menu() << "使用方法：\n"
                  << "  --backup                     建立備份\n"
                  << "  --restore                    還原最新備份\n"
                  << "  --list-backups               列出所有備份檔案\n"
                  << "  --delete-backup <file>       刪除指定備份檔\n"
                  // << "  --add-note <content>    新增備註\n" // 註解掉的功能
                  // << "  --list-notes            列出所有備註\n" // 註解掉的功能
                  // << "  --update-note <id> <content> 更新備註\n" // 註解掉的功能
                  // << "  --delete-note <id>      刪除指定備註\n" // 註解掉的功能
                  << "  --log                        顯示應用程式日誌 (來自設定檔中的 dbPath)\n"
                  << "  --show-backup-log            顯示 backup_log.db 中的備份日誌\n"
                  << "  --no-icons                   不顯示圖示\n"
                  << "  --help                       顯示此幫助訊息\n";
        return;
    }

    std::string command = argv[1];

    if (command == "--backup")
    {
        auto req = std::make_shared<BackupRequestedEvent>(dbPath, backupDir);
        bus.publish(req);
    }
    else if (command == "--restore")
    {
        Restore::restoreLatest(backupDir, dbPath);
    }
    else if (command == "--list-backups")
    {
        if (!fs::exists(backupDir))
        {
            Logger::error(Emoji::Error() + "備份資料夾不存在: " + backupDir);
            return;
        }
        for (const auto &entry : fs::directory_iterator(backupDir))
        {
            if (entry.path().extension() == ".db")
            {
                // 列表通常輸出到 stdout 是可接受的
                std::cout << Emoji::File() << entry.path().filename().string() << std::endl;
            }
        }
    }
    else if (command == "--delete-backup")
    {
        if (argc < 3)
        {
            Logger::error(Emoji::Warning() + "請指定要刪除的備份檔名");
            return;
        }
        fs::path fileToDelete = fs::path(backupDir) / argv[2];
        if (fs::exists(fileToDelete))
        {
            fs::remove(fileToDelete);
            Logger::info(Emoji::Trash() + " 已刪除：" + fileToDelete.filename().string());
        }
        else
        {
            Logger::error(Emoji::Error() + " 找不到檔案：" + fileToDelete.string());
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
        handle(1, nullptr, dbPath, backupDir, bus);
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
        Logger::error(Emoji::Question() + " 未知指令：" + command);
    }
}
