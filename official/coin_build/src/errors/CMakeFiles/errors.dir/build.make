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
CMAKE_SOURCE_DIR = /home/ed/Coin3D/official/coin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/ed/Coin3D/official/coin_build

# Include any dependencies generated for this target.
include src/errors/CMakeFiles/errors.dir/depend.make

# Include the progress variables for this target.
include src/errors/CMakeFiles/errors.dir/progress.make

# Include the compile flags for this target's objects.
include src/errors/CMakeFiles/errors.dir/flags.make

src/errors/CMakeFiles/errors.dir/error.cpp.o: src/errors/CMakeFiles/errors.dir/flags.make
src/errors/CMakeFiles/errors.dir/error.cpp.o: /home/ed/Coin3D/official/coin/src/errors/error.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/errors/CMakeFiles/errors.dir/error.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/errors.dir/error.cpp.o -c /home/ed/Coin3D/official/coin/src/errors/error.cpp

src/errors/CMakeFiles/errors.dir/error.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/errors.dir/error.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/errors/error.cpp > CMakeFiles/errors.dir/error.cpp.i

src/errors/CMakeFiles/errors.dir/error.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/errors.dir/error.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/errors/error.cpp -o CMakeFiles/errors.dir/error.cpp.s

src/errors/CMakeFiles/errors.dir/error.cpp.o.requires:
.PHONY : src/errors/CMakeFiles/errors.dir/error.cpp.o.requires

src/errors/CMakeFiles/errors.dir/error.cpp.o.provides: src/errors/CMakeFiles/errors.dir/error.cpp.o.requires
	$(MAKE) -f src/errors/CMakeFiles/errors.dir/build.make src/errors/CMakeFiles/errors.dir/error.cpp.o.provides.build
.PHONY : src/errors/CMakeFiles/errors.dir/error.cpp.o.provides

src/errors/CMakeFiles/errors.dir/error.cpp.o.provides.build: src/errors/CMakeFiles/errors.dir/error.cpp.o

src/errors/CMakeFiles/errors.dir/debugerror.cpp.o: src/errors/CMakeFiles/errors.dir/flags.make
src/errors/CMakeFiles/errors.dir/debugerror.cpp.o: /home/ed/Coin3D/official/coin/src/errors/debugerror.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/errors/CMakeFiles/errors.dir/debugerror.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/errors.dir/debugerror.cpp.o -c /home/ed/Coin3D/official/coin/src/errors/debugerror.cpp

src/errors/CMakeFiles/errors.dir/debugerror.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/errors.dir/debugerror.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/errors/debugerror.cpp > CMakeFiles/errors.dir/debugerror.cpp.i

src/errors/CMakeFiles/errors.dir/debugerror.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/errors.dir/debugerror.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/errors/debugerror.cpp -o CMakeFiles/errors.dir/debugerror.cpp.s

src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.requires:
.PHONY : src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.requires

src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.provides: src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.requires
	$(MAKE) -f src/errors/CMakeFiles/errors.dir/build.make src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.provides.build
.PHONY : src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.provides

src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.provides.build: src/errors/CMakeFiles/errors.dir/debugerror.cpp.o

src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o: src/errors/CMakeFiles/errors.dir/flags.make
src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o: /home/ed/Coin3D/official/coin/src/errors/SoDebugError.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/errors.dir/SoDebugError.cpp.o -c /home/ed/Coin3D/official/coin/src/errors/SoDebugError.cpp

src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/errors.dir/SoDebugError.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/errors/SoDebugError.cpp > CMakeFiles/errors.dir/SoDebugError.cpp.i

src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/errors.dir/SoDebugError.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/errors/SoDebugError.cpp -o CMakeFiles/errors.dir/SoDebugError.cpp.s

src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.requires:
.PHONY : src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.requires

src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.provides: src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.requires
	$(MAKE) -f src/errors/CMakeFiles/errors.dir/build.make src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.provides.build
.PHONY : src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.provides

src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.provides.build: src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o

src/errors/CMakeFiles/errors.dir/SoError.cpp.o: src/errors/CMakeFiles/errors.dir/flags.make
src/errors/CMakeFiles/errors.dir/SoError.cpp.o: /home/ed/Coin3D/official/coin/src/errors/SoError.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/errors/CMakeFiles/errors.dir/SoError.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/errors.dir/SoError.cpp.o -c /home/ed/Coin3D/official/coin/src/errors/SoError.cpp

src/errors/CMakeFiles/errors.dir/SoError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/errors.dir/SoError.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/errors/SoError.cpp > CMakeFiles/errors.dir/SoError.cpp.i

src/errors/CMakeFiles/errors.dir/SoError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/errors.dir/SoError.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/errors/SoError.cpp -o CMakeFiles/errors.dir/SoError.cpp.s

src/errors/CMakeFiles/errors.dir/SoError.cpp.o.requires:
.PHONY : src/errors/CMakeFiles/errors.dir/SoError.cpp.o.requires

src/errors/CMakeFiles/errors.dir/SoError.cpp.o.provides: src/errors/CMakeFiles/errors.dir/SoError.cpp.o.requires
	$(MAKE) -f src/errors/CMakeFiles/errors.dir/build.make src/errors/CMakeFiles/errors.dir/SoError.cpp.o.provides.build
.PHONY : src/errors/CMakeFiles/errors.dir/SoError.cpp.o.provides

src/errors/CMakeFiles/errors.dir/SoError.cpp.o.provides.build: src/errors/CMakeFiles/errors.dir/SoError.cpp.o

src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o: src/errors/CMakeFiles/errors.dir/flags.make
src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o: /home/ed/Coin3D/official/coin/src/errors/SoMemoryError.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/errors.dir/SoMemoryError.cpp.o -c /home/ed/Coin3D/official/coin/src/errors/SoMemoryError.cpp

src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/errors.dir/SoMemoryError.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/errors/SoMemoryError.cpp > CMakeFiles/errors.dir/SoMemoryError.cpp.i

src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/errors.dir/SoMemoryError.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/errors/SoMemoryError.cpp -o CMakeFiles/errors.dir/SoMemoryError.cpp.s

src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.requires:
.PHONY : src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.requires

src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.provides: src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.requires
	$(MAKE) -f src/errors/CMakeFiles/errors.dir/build.make src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.provides.build
.PHONY : src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.provides

src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.provides.build: src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o

src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o: src/errors/CMakeFiles/errors.dir/flags.make
src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o: /home/ed/Coin3D/official/coin/src/errors/SoReadError.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/errors.dir/SoReadError.cpp.o -c /home/ed/Coin3D/official/coin/src/errors/SoReadError.cpp

src/errors/CMakeFiles/errors.dir/SoReadError.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/errors.dir/SoReadError.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/errors/SoReadError.cpp > CMakeFiles/errors.dir/SoReadError.cpp.i

src/errors/CMakeFiles/errors.dir/SoReadError.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/errors.dir/SoReadError.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/errors && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/errors/SoReadError.cpp -o CMakeFiles/errors.dir/SoReadError.cpp.s

src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.requires:
.PHONY : src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.requires

src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.provides: src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.requires
	$(MAKE) -f src/errors/CMakeFiles/errors.dir/build.make src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.provides.build
.PHONY : src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.provides

src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.provides.build: src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o

errors: src/errors/CMakeFiles/errors.dir/error.cpp.o
errors: src/errors/CMakeFiles/errors.dir/debugerror.cpp.o
errors: src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o
errors: src/errors/CMakeFiles/errors.dir/SoError.cpp.o
errors: src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o
errors: src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o
errors: src/errors/CMakeFiles/errors.dir/build.make
.PHONY : errors

# Rule to build all files generated by this target.
src/errors/CMakeFiles/errors.dir/build: errors
.PHONY : src/errors/CMakeFiles/errors.dir/build

src/errors/CMakeFiles/errors.dir/requires: src/errors/CMakeFiles/errors.dir/error.cpp.o.requires
src/errors/CMakeFiles/errors.dir/requires: src/errors/CMakeFiles/errors.dir/debugerror.cpp.o.requires
src/errors/CMakeFiles/errors.dir/requires: src/errors/CMakeFiles/errors.dir/SoDebugError.cpp.o.requires
src/errors/CMakeFiles/errors.dir/requires: src/errors/CMakeFiles/errors.dir/SoError.cpp.o.requires
src/errors/CMakeFiles/errors.dir/requires: src/errors/CMakeFiles/errors.dir/SoMemoryError.cpp.o.requires
src/errors/CMakeFiles/errors.dir/requires: src/errors/CMakeFiles/errors.dir/SoReadError.cpp.o.requires
.PHONY : src/errors/CMakeFiles/errors.dir/requires

src/errors/CMakeFiles/errors.dir/clean:
	cd /home/ed/Coin3D/official/coin_build/src/errors && $(CMAKE_COMMAND) -P CMakeFiles/errors.dir/cmake_clean.cmake
.PHONY : src/errors/CMakeFiles/errors.dir/clean

src/errors/CMakeFiles/errors.dir/depend:
	cd /home/ed/Coin3D/official/coin_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ed/Coin3D/official/coin /home/ed/Coin3D/official/coin/src/errors /home/ed/Coin3D/official/coin_build /home/ed/Coin3D/official/coin_build/src/errors /home/ed/Coin3D/official/coin_build/src/errors/CMakeFiles/errors.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/errors/CMakeFiles/errors.dir/depend

