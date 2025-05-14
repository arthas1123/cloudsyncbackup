# CloudSyncBackup

A lightweight, modular backup tool that allows CLI-triggered file backup, event logging, and planned cloud sync.

## 🧩 Features
- Modular C++ architecture with EventBus for event-driven design
- CLI interface to trigger backups
- Background thread execution for non-blocking operations
- Event-based logger for clean separation of concerns
- Future support for event history storage and cloud upload

## 📦 Directory Structure

cloudsyncbackup/
├── src/
│   ├── main.cpp                  # Entry point
│   ├── cli_parser.cpp            # CLI handler
│   ├── logger.cpp                # Logs events
│   ├── event_bus.hpp             # Event system
│   ├── backup.cpp                # File backup logic
│   └── threading/
│       └── backup_worker.cpp     # Event-based background backup
├── include/
│   └── *.hpp                     # Headers
├── test/                         # Unit test files
└── backup_output/                # Output folder for backups

## 🚀 Current Progress (as of 2025-05)
- [x] EventBus: publish/subscribe model
- [x] Logger: listens and records events
- [x] BackupWorker: reacts to BackupRequestedEvent using background thread
- [x] CLI command `--backup` triggers event
- [x] Modular structure for testing and reuse
- [ ] 🔜 Event recorder module: save structured events as JSON
- [ ] 🔜 ThreadPool for concurrency control (planned)
- [ ] 🔜 Cloud upload support (Cloudflare R2 / Google Drive)

## 🛠 Usage
```bash
# Compile (example with clang++)
clang++ -std=c++17 -g src/main.cpp -o cloudsync \
  src/cli_parser.cpp src/logger.cpp src/backup.cpp \
  src/threading/backup_worker.cpp -Iinclude

# Run backup
./cloudsync --backup
