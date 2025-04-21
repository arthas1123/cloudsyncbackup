#!/bin/bash

clang++ -std=c++17 -Iinclude \
    src/test_main_cli.cpp \
    src/cli_parser.cpp \
    src/threading/backup_worker.cpp \
    src/backup.cpp \
    src/database.cpp \
    src/config.cpp \
    src/logger.cpp \
    src/restore.cpp \
    -o build/test_main_cli \
    -lsqlite3
