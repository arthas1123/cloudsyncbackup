# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
$(VERBOSE).SILENT:

# A target that is always out of date.
cmake_force:
.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /opt/homebrew/bin/cmake

# The command to remove a file.
RM = /opt/homebrew/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/alex11/cloudsyncbackup

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/alex11/cloudsyncbackup/build

# Include any dependencies generated for this target.
include CMakeFiles/cloudsyncbackup.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/cloudsyncbackup.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/cloudsyncbackup.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/cloudsyncbackup.dir/flags.make

CMakeFiles/cloudsyncbackup.dir/codegen:
.PHONY : CMakeFiles/cloudsyncbackup.dir/codegen

CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o: CMakeFiles/cloudsyncbackup.dir/flags.make
CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o: /Users/alex11/cloudsyncbackup/src/main.cpp
CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o: CMakeFiles/cloudsyncbackup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alex11/cloudsyncbackup/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o -MF CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o.d -o CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o -c /Users/alex11/cloudsyncbackup/src/main.cpp

CMakeFiles/cloudsyncbackup.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cloudsyncbackup.dir/src/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alex11/cloudsyncbackup/src/main.cpp > CMakeFiles/cloudsyncbackup.dir/src/main.cpp.i

CMakeFiles/cloudsyncbackup.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cloudsyncbackup.dir/src/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alex11/cloudsyncbackup/src/main.cpp -o CMakeFiles/cloudsyncbackup.dir/src/main.cpp.s

CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o: CMakeFiles/cloudsyncbackup.dir/flags.make
CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o: /Users/alex11/cloudsyncbackup/src/database.cpp
CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o: CMakeFiles/cloudsyncbackup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alex11/cloudsyncbackup/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o -MF CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o.d -o CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o -c /Users/alex11/cloudsyncbackup/src/database.cpp

CMakeFiles/cloudsyncbackup.dir/src/database.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cloudsyncbackup.dir/src/database.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alex11/cloudsyncbackup/src/database.cpp > CMakeFiles/cloudsyncbackup.dir/src/database.cpp.i

CMakeFiles/cloudsyncbackup.dir/src/database.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cloudsyncbackup.dir/src/database.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alex11/cloudsyncbackup/src/database.cpp -o CMakeFiles/cloudsyncbackup.dir/src/database.cpp.s

CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o: CMakeFiles/cloudsyncbackup.dir/flags.make
CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o: /Users/alex11/cloudsyncbackup/src/backup.cpp
CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o: CMakeFiles/cloudsyncbackup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alex11/cloudsyncbackup/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o -MF CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o.d -o CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o -c /Users/alex11/cloudsyncbackup/src/backup.cpp

CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alex11/cloudsyncbackup/src/backup.cpp > CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.i

CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alex11/cloudsyncbackup/src/backup.cpp -o CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.s

CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o: CMakeFiles/cloudsyncbackup.dir/flags.make
CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o: /Users/alex11/cloudsyncbackup/src/restore.cpp
CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o: CMakeFiles/cloudsyncbackup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alex11/cloudsyncbackup/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Building CXX object CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o -MF CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o.d -o CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o -c /Users/alex11/cloudsyncbackup/src/restore.cpp

CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alex11/cloudsyncbackup/src/restore.cpp > CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.i

CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alex11/cloudsyncbackup/src/restore.cpp -o CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.s

CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o: CMakeFiles/cloudsyncbackup.dir/flags.make
CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o: /Users/alex11/cloudsyncbackup/src/cli_parser.cpp
CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o: CMakeFiles/cloudsyncbackup.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Users/alex11/cloudsyncbackup/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_5) "Building CXX object CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o -MF CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o.d -o CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o -c /Users/alex11/cloudsyncbackup/src/cli_parser.cpp

CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/alex11/cloudsyncbackup/src/cli_parser.cpp > CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.i

CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/alex11/cloudsyncbackup/src/cli_parser.cpp -o CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.s

# Object files for target cloudsyncbackup
cloudsyncbackup_OBJECTS = \
"CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o" \
"CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o" \
"CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o" \
"CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o" \
"CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o"

# External object files for target cloudsyncbackup
cloudsyncbackup_EXTERNAL_OBJECTS =

cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/src/main.cpp.o
cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/src/database.cpp.o
cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/src/backup.cpp.o
cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/src/restore.cpp.o
cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/src/cli_parser.cpp.o
cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/build.make
cloudsyncbackup: CMakeFiles/cloudsyncbackup.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Users/alex11/cloudsyncbackup/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_6) "Linking CXX executable cloudsyncbackup"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/cloudsyncbackup.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/cloudsyncbackup.dir/build: cloudsyncbackup
.PHONY : CMakeFiles/cloudsyncbackup.dir/build

CMakeFiles/cloudsyncbackup.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/cloudsyncbackup.dir/cmake_clean.cmake
.PHONY : CMakeFiles/cloudsyncbackup.dir/clean

CMakeFiles/cloudsyncbackup.dir/depend:
	cd /Users/alex11/cloudsyncbackup/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/alex11/cloudsyncbackup /Users/alex11/cloudsyncbackup /Users/alex11/cloudsyncbackup/build /Users/alex11/cloudsyncbackup/build /Users/alex11/cloudsyncbackup/build/CMakeFiles/cloudsyncbackup.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/cloudsyncbackup.dir/depend

