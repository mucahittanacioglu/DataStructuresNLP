# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /snap/clion/92/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/92/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/mucahit/CLionProjects/DataSturcturesP1v1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/DataSturcturesP1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/DataSturcturesP1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/DataSturcturesP1.dir/flags.make

CMakeFiles/DataSturcturesP1.dir/main.c.o: CMakeFiles/DataSturcturesP1.dir/flags.make
CMakeFiles/DataSturcturesP1.dir/main.c.o: ../main.c
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/DataSturcturesP1.dir/main.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -o CMakeFiles/DataSturcturesP1.dir/main.c.o   -c /home/mucahit/CLionProjects/DataSturcturesP1v1/main.c

CMakeFiles/DataSturcturesP1.dir/main.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing C source to CMakeFiles/DataSturcturesP1.dir/main.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /home/mucahit/CLionProjects/DataSturcturesP1v1/main.c > CMakeFiles/DataSturcturesP1.dir/main.c.i

CMakeFiles/DataSturcturesP1.dir/main.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling C source to assembly CMakeFiles/DataSturcturesP1.dir/main.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /home/mucahit/CLionProjects/DataSturcturesP1v1/main.c -o CMakeFiles/DataSturcturesP1.dir/main.c.s

# Object files for target DataSturcturesP1
DataSturcturesP1_OBJECTS = \
"CMakeFiles/DataSturcturesP1.dir/main.c.o"

# External object files for target DataSturcturesP1
DataSturcturesP1_EXTERNAL_OBJECTS =

DataSturcturesP1: CMakeFiles/DataSturcturesP1.dir/main.c.o
DataSturcturesP1: CMakeFiles/DataSturcturesP1.dir/build.make
DataSturcturesP1: CMakeFiles/DataSturcturesP1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C executable DataSturcturesP1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/DataSturcturesP1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/DataSturcturesP1.dir/build: DataSturcturesP1

.PHONY : CMakeFiles/DataSturcturesP1.dir/build

CMakeFiles/DataSturcturesP1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/DataSturcturesP1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/DataSturcturesP1.dir/clean

CMakeFiles/DataSturcturesP1.dir/depend:
	cd /home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/mucahit/CLionProjects/DataSturcturesP1v1 /home/mucahit/CLionProjects/DataSturcturesP1v1 /home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug /home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug /home/mucahit/CLionProjects/DataSturcturesP1v1/cmake-build-debug/CMakeFiles/DataSturcturesP1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/DataSturcturesP1.dir/depend

