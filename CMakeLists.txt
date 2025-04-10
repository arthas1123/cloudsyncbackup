cmake_minimum_required(VERSION 3.10)
project(cloudsyncbackup)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

add_executable(cloudsyncbackup
    src/main.cpp
    src/database.cpp
    src/backup.cpp
    src/restore.cpp
    src/cli_parser.cpp
    src/config.cpp
    src/logger.cpp
)

target_link_libraries(cloudsyncbackup sqlite3)
