# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.2

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/ed/Coin3D/official/quarter

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ed/Coin3D/official/quarter_build

# Utility rule file for Quarter_automoc.

# Include the progress variables for this target.
include src/Quarter/CMakeFiles/Quarter_automoc.dir/progress.make

src/Quarter/CMakeFiles/Quarter_automoc:
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/quarter_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --blue --bold "Automatic moc for target Quarter"
	cd /home/ed/Coin3D/official/quarter_build/src/Quarter && /usr/local/bin/cmake -E cmake_autogen /home/ed/Coin3D/official/quarter_build/src/Quarter/CMakeFiles/Quarter_automoc.dir/ ""

Quarter_automoc: src/Quarter/CMakeFiles/Quarter_automoc
Quarter_automoc: src/Quarter/CMakeFiles/Quarter_automoc.dir/build.make
.PHONY : Quarter_automoc

# Rule to build all files generated by this target.
src/Quarter/CMakeFiles/Quarter_automoc.dir/build: Quarter_automoc
.PHONY : src/Quarter/CMakeFiles/Quarter_automoc.dir/build

src/Quarter/CMakeFiles/Quarter_automoc.dir/clean:
	cd /home/ed/Coin3D/official/quarter_build/src/Quarter && $(CMAKE_COMMAND) -P CMakeFiles/Quarter_automoc.dir/cmake_clean.cmake
.PHONY : src/Quarter/CMakeFiles/Quarter_automoc.dir/clean

src/Quarter/CMakeFiles/Quarter_automoc.dir/depend:
	cd /home/ed/Coin3D/official/quarter_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ed/Coin3D/official/quarter /home/ed/Coin3D/official/quarter/src/Quarter /home/ed/Coin3D/official/quarter_build /home/ed/Coin3D/official/quarter_build/src/Quarter /home/ed/Coin3D/official/quarter_build/src/Quarter/CMakeFiles/Quarter_automoc.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/Quarter/CMakeFiles/Quarter_automoc.dir/depend

