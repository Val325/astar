# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.28

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ghost/progects/pathfinding/dfs/dfs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ghost/progects/pathfinding/dfs/dfs

# Include any dependencies generated for this target.
include CMakeFiles/qlearn.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/qlearn.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/qlearn.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/qlearn.dir/flags.make

CMakeFiles/qlearn.dir/src/main.cpp.o: CMakeFiles/qlearn.dir/flags.make
CMakeFiles/qlearn.dir/src/main.cpp.o: src/main.cpp
CMakeFiles/qlearn.dir/src/main.cpp.o: CMakeFiles/qlearn.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/ghost/progects/pathfinding/dfs/dfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/qlearn.dir/src/main.cpp.o"
	/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/qlearn.dir/src/main.cpp.o -MF CMakeFiles/qlearn.dir/src/main.cpp.o.d -o CMakeFiles/qlearn.dir/src/main.cpp.o -c /home/ghost/progects/pathfinding/dfs/dfs/src/main.cpp

CMakeFiles/qlearn.dir/src/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/qlearn.dir/src/main.cpp.i"
	/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/ghost/progects/pathfinding/dfs/dfs/src/main.cpp > CMakeFiles/qlearn.dir/src/main.cpp.i

CMakeFiles/qlearn.dir/src/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/qlearn.dir/src/main.cpp.s"
	/bin/clang++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/ghost/progects/pathfinding/dfs/dfs/src/main.cpp -o CMakeFiles/qlearn.dir/src/main.cpp.s

# Object files for target qlearn
qlearn_OBJECTS = \
"CMakeFiles/qlearn.dir/src/main.cpp.o"

# External object files for target qlearn
qlearn_EXTERNAL_OBJECTS =

qlearn: CMakeFiles/qlearn.dir/src/main.cpp.o
qlearn: CMakeFiles/qlearn.dir/build.make
qlearn: CMakeFiles/qlearn.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/ghost/progects/pathfinding/dfs/dfs/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable qlearn"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/qlearn.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/qlearn.dir/build: qlearn
.PHONY : CMakeFiles/qlearn.dir/build

CMakeFiles/qlearn.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/qlearn.dir/cmake_clean.cmake
.PHONY : CMakeFiles/qlearn.dir/clean

CMakeFiles/qlearn.dir/depend:
	cd /home/ghost/progects/pathfinding/dfs/dfs && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ghost/progects/pathfinding/dfs/dfs /home/ghost/progects/pathfinding/dfs/dfs /home/ghost/progects/pathfinding/dfs/dfs /home/ghost/progects/pathfinding/dfs/dfs /home/ghost/progects/pathfinding/dfs/dfs/CMakeFiles/qlearn.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/qlearn.dir/depend

