# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.30

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
CMAKE_COMMAND = /snap/clion/305/bin/cmake/linux/x64/bin/cmake

# The command to remove a file.
RM = /snap/clion/305/bin/cmake/linux/x64/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/nicola/Desktop/AoC2024

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/nicola/Desktop/AoC2024/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/AoC2024.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/AoC2024.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/AoC2024.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AoC2024.dir/flags.make

CMakeFiles/AoC2024.dir/utils.cpp.o: CMakeFiles/AoC2024.dir/flags.make
CMakeFiles/AoC2024.dir/utils.cpp.o: /home/nicola/Desktop/AoC2024/utils.cpp
CMakeFiles/AoC2024.dir/utils.cpp.o: CMakeFiles/AoC2024.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/nicola/Desktop/AoC2024/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AoC2024.dir/utils.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AoC2024.dir/utils.cpp.o -MF CMakeFiles/AoC2024.dir/utils.cpp.o.d -o CMakeFiles/AoC2024.dir/utils.cpp.o -c /home/nicola/Desktop/AoC2024/utils.cpp

CMakeFiles/AoC2024.dir/utils.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AoC2024.dir/utils.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/Desktop/AoC2024/utils.cpp > CMakeFiles/AoC2024.dir/utils.cpp.i

CMakeFiles/AoC2024.dir/utils.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AoC2024.dir/utils.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/Desktop/AoC2024/utils.cpp -o CMakeFiles/AoC2024.dir/utils.cpp.s

CMakeFiles/AoC2024.dir/day6.cpp.o: CMakeFiles/AoC2024.dir/flags.make
CMakeFiles/AoC2024.dir/day6.cpp.o: /home/nicola/Desktop/AoC2024/day6.cpp
CMakeFiles/AoC2024.dir/day6.cpp.o: CMakeFiles/AoC2024.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/home/nicola/Desktop/AoC2024/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/AoC2024.dir/day6.cpp.o"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/AoC2024.dir/day6.cpp.o -MF CMakeFiles/AoC2024.dir/day6.cpp.o.d -o CMakeFiles/AoC2024.dir/day6.cpp.o -c /home/nicola/Desktop/AoC2024/day6.cpp

CMakeFiles/AoC2024.dir/day6.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/AoC2024.dir/day6.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/nicola/Desktop/AoC2024/day6.cpp > CMakeFiles/AoC2024.dir/day6.cpp.i

CMakeFiles/AoC2024.dir/day6.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/AoC2024.dir/day6.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/nicola/Desktop/AoC2024/day6.cpp -o CMakeFiles/AoC2024.dir/day6.cpp.s

# Object files for target AoC2024
AoC2024_OBJECTS = \
"CMakeFiles/AoC2024.dir/utils.cpp.o" \
"CMakeFiles/AoC2024.dir/day6.cpp.o"

# External object files for target AoC2024
AoC2024_EXTERNAL_OBJECTS =

AoC2024: CMakeFiles/AoC2024.dir/utils.cpp.o
AoC2024: CMakeFiles/AoC2024.dir/day6.cpp.o
AoC2024: CMakeFiles/AoC2024.dir/build.make
AoC2024: CMakeFiles/AoC2024.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/home/nicola/Desktop/AoC2024/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable AoC2024"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AoC2024.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AoC2024.dir/build: AoC2024
.PHONY : CMakeFiles/AoC2024.dir/build

CMakeFiles/AoC2024.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AoC2024.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AoC2024.dir/clean

CMakeFiles/AoC2024.dir/depend:
	cd /home/nicola/Desktop/AoC2024/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/nicola/Desktop/AoC2024 /home/nicola/Desktop/AoC2024 /home/nicola/Desktop/AoC2024/cmake-build-debug /home/nicola/Desktop/AoC2024/cmake-build-debug /home/nicola/Desktop/AoC2024/cmake-build-debug/CMakeFiles/AoC2024.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/AoC2024.dir/depend

