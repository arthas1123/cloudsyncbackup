clang++ -std=c++17 -Iinclude \
    src/test_main_backup.cpp \
    src/backup.cpp \
    src/threading/backup_worker.cpp \
    -o build/test_main_backup \
