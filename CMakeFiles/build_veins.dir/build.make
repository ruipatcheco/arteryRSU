# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/veins/src/artery

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/veins/src/artery

# Utility rule file for build_veins.

# Include the progress variables for this target.
include CMakeFiles/build_veins.dir/progress.make

CMakeFiles/build_veins:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold --progress-dir=/home/veins/src/artery/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building Veins (external dependency)"
	$(MAKE) veins MODE=release

build_veins: CMakeFiles/build_veins
build_veins: CMakeFiles/build_veins.dir/build.make

.PHONY : build_veins

# Rule to build all files generated by this target.
CMakeFiles/build_veins.dir/build: build_veins

.PHONY : CMakeFiles/build_veins.dir/build

CMakeFiles/build_veins.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/build_veins.dir/cmake_clean.cmake
.PHONY : CMakeFiles/build_veins.dir/clean

CMakeFiles/build_veins.dir/depend:
	cd /home/veins/src/artery && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/veins/src/artery /home/veins/src/artery /home/veins/src/artery /home/veins/src/artery /home/veins/src/artery/CMakeFiles/build_veins.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/build_veins.dir/depend

