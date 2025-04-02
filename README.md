# ☁️ cloudsyncbackup

A lightweight local backup system built with C++ and SQLite.

---

## ✅ Features

- 🧱 **Modular Design**
  - `Database` module using native SQLite3 API
  - `Backup` module with timestamped copies
- 📦 **Single-file `.db` storage**
- 🧾 **Filesystem-based backup management**
- 🧪 Easy to test, build and extend
- 🔧 Cross-platform (tested on macOS with Clang)

---

## 📁 Project Structure
cloudsyncbackup/
├── include/          # Header files (database.hpp, backup.hpp)
├── src/              # Implementation files (main.cpp, database.cpp, backup.cpp)
├── backup_storage/   # Auto-created backup directory
├── mydata.db         # Main SQLite database (ignored by Git)
├── logs/             # Placeholder for future logs
├── build/            # CMake build output
├── CMakeLists.txt
└── README.md

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

🔜 Roadmap

	•	CLI support (--backup, --restore, --list)
	•	Restore from latest or chosen backup
	•	Logging module
	•	config.json for path/settings
