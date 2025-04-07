# ☁️ cloudsyncbackup

A lightweight local backup system built with C++ and SQLite.

---

## ✅ Features

- 🧱 Modular architecture (Database / Backup / Restore / CLI)
- 🗂 Backup your SQLite `.db` with timestamped filenames
- 🔁 Restore latest or specified backups
- 📝 Manage notes: insert, list, (update/delete planned)
- 💻 CLI interface for all features
- 🌱 Cross-platform, CMake-based build (tested on macOS + Clang)

---

## 📁 Project Structure
cloudsyncbackup/
├── include/
│   ├── database.hpp
│   ├── backup.hpp
│   ├── restore.hpp
│   └── cli_parser.hpp
├── src/
│   ├── main.cpp
│   ├── database.cpp
│   ├── backup.cpp
│   ├── restore.cpp
│   └── cli_parser.cpp
├── backup_storage/      # 備份檔案自動儲存處
├── logs/                # 日誌（未來功能）
├── mydata.db            # SQLite 資料庫主檔（已 gitignore）
├── build/               # CMake build output
├── .gitignore
└── CMakeLists.txt

---

## 🧭 CLI Usage

```bash
./cloudsyncbackup --backup                 # ➕ 建立備份
./cloudsyncbackup --restore                # ♻️ 還原最新備份
./cloudsyncbackup --list-backups           # 📋 列出所有備份
./cloudsyncbackup --delete-backup <file>   # 🗑️ 刪除指定備份
./cloudsyncbackup --add-note "內容"        # 📝 新增筆記
./cloudsyncbackup --list-notes             # 📓 顯示所有筆記

---

## 🧪 How It Works
+----------------+
|  C++ Program   |
+----------------+
        |
        | Execute SQL
        v
+------------------------+
|  SQLite Engine (C API) |
+------------------------+
        |
        | Read / Write
        v
+----------------+
|  mydata.db     |
|  (SQLite file) |
+----------------+

---

## 🧭 Getting Started

```bash
# Build
mkdir -p build
cd build
cmake ..
cmake --build .

# Run
./cloudsyncbackup

🔐 Git Ignore

.gitignore excludes:
	•	mydata.db
	•	backup_storage/
	•	logs/
	•	build files

🧩 TODO / Roadmap

	•	--update-note / --delete-note
	•	Log module (write to logs/)
	•	config.json for paths & options
	•	Unit testing & packaging
