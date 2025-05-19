cmake_minimum_required(VERSION 3.10)
project(cloudsyncbackup)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -fsanitize=thread")
set(CMAKE_EXE_LINKER_FLAGS_DEBUG "${CMAKE_EXE_LINKER_FLAGS_DEBUG} -fsanitize=thread")

include_directories(include)

add_executable(cloudsyncbackup
    src/main.cpp
    src/database.cpp
    src/backup.cpp
    src/restore.cpp
    src/cli_parser.cpp
    src/config.cpp
    src/logger.cpp
    src/threading/backup_worker.cpp
    src/event_recorder.cpp
)

target_link_libraries(cloudsyncbackup sqlite3)
