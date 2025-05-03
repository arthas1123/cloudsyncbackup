#!/bin/bash
clang++ -std=c++17 -fsanitize=address -g -Iinclude "$1" ./src/*.cpp -o a.out && ./a.out
