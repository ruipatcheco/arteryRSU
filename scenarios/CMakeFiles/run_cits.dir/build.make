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

# Utility rule file for run_cits.

# Include the progress variables for this target.
include scenarios/CMakeFiles/run_cits.dir/progress.make

scenarios/CMakeFiles/run_cits:
	cd /home/veins/src/artery/scenarios/c-its && /home/veins/src/omnetpp/bin/opp_run_release -n /home/veins/src/artery/src/artery:/home/veins/src/artery/src/traci:/home/veins/src/artery/extern/veins/examples/veins:/home/veins/src/artery/extern/veins/src/veins:/home/veins/src/artery/extern/inet/src:/home/veins/src/artery/extern/inet/examples:/home/veins/src/artery/extern/inet/tutorials:/home/veins/src/artery/extern/inet/showcases -l /home/veins/src/artery/src/artery/envmod/libartery_envmod.so -l /home/veins/src/artery/scenarios/highway-police/libartery_police.so -l /home/veins/src/artery/src/artery/envmod/libartery_envmod.so -l /home/veins/src/artery/src/artery/storyboard/libartery_storyboard.so -l /home/veins/src/artery/extern/inet/out/clang-release/src/libINET.so -l /home/veins/src/artery/extern/veins/out/clang-release/src/libveins.so -l /home/veins/src/artery/src/artery/libartery_core.so omnetpp.ini

run_cits: scenarios/CMakeFiles/run_cits
run_cits: scenarios/CMakeFiles/run_cits.dir/build.make

.PHONY : run_cits

# Rule to build all files generated by this target.
scenarios/CMakeFiles/run_cits.dir/build: run_cits

.PHONY : scenarios/CMakeFiles/run_cits.dir/build

scenarios/CMakeFiles/run_cits.dir/clean:
	cd /home/veins/src/artery/scenarios && $(CMAKE_COMMAND) -P CMakeFiles/run_cits.dir/cmake_clean.cmake
.PHONY : scenarios/CMakeFiles/run_cits.dir/clean

scenarios/CMakeFiles/run_cits.dir/depend:
	cd /home/veins/src/artery && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/veins/src/artery /home/veins/src/artery/scenarios /home/veins/src/artery /home/veins/src/artery/scenarios /home/veins/src/artery/scenarios/CMakeFiles/run_cits.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : scenarios/CMakeFiles/run_cits.dir/depend

