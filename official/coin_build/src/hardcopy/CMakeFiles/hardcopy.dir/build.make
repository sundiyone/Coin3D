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
include src/hardcopy/CMakeFiles/hardcopy.dir/depend.make

# Include the progress variables for this target.
include src/hardcopy/CMakeFiles/hardcopy.dir/progress.make

# Include the compile flags for this target's objects.
include src/hardcopy/CMakeFiles/hardcopy.dir/flags.make

src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o: src/hardcopy/CMakeFiles/hardcopy.dir/flags.make
src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o: /home/ed/Coin3D/official/coin/src/hardcopy/HardCopy.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hardcopy.dir/HardCopy.cpp.o -c /home/ed/Coin3D/official/coin/src/hardcopy/HardCopy.cpp

src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hardcopy.dir/HardCopy.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/hardcopy/HardCopy.cpp > CMakeFiles/hardcopy.dir/HardCopy.cpp.i

src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hardcopy.dir/HardCopy.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/hardcopy/HardCopy.cpp -o CMakeFiles/hardcopy.dir/HardCopy.cpp.s

src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.requires:
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.requires

src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.provides: src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.requires
	$(MAKE) -f src/hardcopy/CMakeFiles/hardcopy.dir/build.make src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.provides.build
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.provides

src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.provides.build: src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o

src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o: src/hardcopy/CMakeFiles/hardcopy.dir/flags.make
src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o: /home/ed/Coin3D/official/coin/src/hardcopy/PSVectorOutput.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o -c /home/ed/Coin3D/official/coin/src/hardcopy/PSVectorOutput.cpp

src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/hardcopy/PSVectorOutput.cpp > CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.i

src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/hardcopy/PSVectorOutput.cpp -o CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.s

src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.requires:
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.requires

src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.provides: src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.requires
	$(MAKE) -f src/hardcopy/CMakeFiles/hardcopy.dir/build.make src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.provides.build
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.provides

src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.provides.build: src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o

src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o: src/hardcopy/CMakeFiles/hardcopy.dir/flags.make
src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o: /home/ed/Coin3D/official/coin/src/hardcopy/VectorOutput.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hardcopy.dir/VectorOutput.cpp.o -c /home/ed/Coin3D/official/coin/src/hardcopy/VectorOutput.cpp

src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hardcopy.dir/VectorOutput.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/hardcopy/VectorOutput.cpp > CMakeFiles/hardcopy.dir/VectorOutput.cpp.i

src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hardcopy.dir/VectorOutput.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/hardcopy/VectorOutput.cpp -o CMakeFiles/hardcopy.dir/VectorOutput.cpp.s

src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.requires:
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.requires

src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.provides: src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.requires
	$(MAKE) -f src/hardcopy/CMakeFiles/hardcopy.dir/build.make src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.provides.build
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.provides

src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.provides.build: src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o: src/hardcopy/CMakeFiles/hardcopy.dir/flags.make
src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o: /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeAction.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o -c /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeAction.cpp

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hardcopy.dir/VectorizeAction.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeAction.cpp > CMakeFiles/hardcopy.dir/VectorizeAction.cpp.i

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hardcopy.dir/VectorizeAction.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeAction.cpp -o CMakeFiles/hardcopy.dir/VectorizeAction.cpp.s

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.requires:
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.requires

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.provides: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.requires
	$(MAKE) -f src/hardcopy/CMakeFiles/hardcopy.dir/build.make src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.provides.build
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.provides

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.provides.build: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o: src/hardcopy/CMakeFiles/hardcopy.dir/flags.make
src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o: /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeActionP.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o -c /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeActionP.cpp

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeActionP.cpp > CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.i

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/hardcopy/VectorizeActionP.cpp -o CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.s

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.requires:
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.requires

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.provides: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.requires
	$(MAKE) -f src/hardcopy/CMakeFiles/hardcopy.dir/build.make src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.provides.build
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.provides

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.provides.build: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o: src/hardcopy/CMakeFiles/hardcopy.dir/flags.make
src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o: /home/ed/Coin3D/official/coin/src/hardcopy/VectorizePSAction.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o -c /home/ed/Coin3D/official/coin/src/hardcopy/VectorizePSAction.cpp

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/hardcopy/VectorizePSAction.cpp > CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.i

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/hardcopy/VectorizePSAction.cpp -o CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.s

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.requires:
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.requires

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.provides: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.requires
	$(MAKE) -f src/hardcopy/CMakeFiles/hardcopy.dir/build.make src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.provides.build
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.provides

src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.provides.build: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o

hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o
hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o
hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o
hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o
hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o
hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o
hardcopy: src/hardcopy/CMakeFiles/hardcopy.dir/build.make
.PHONY : hardcopy

# Rule to build all files generated by this target.
src/hardcopy/CMakeFiles/hardcopy.dir/build: hardcopy
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/build

src/hardcopy/CMakeFiles/hardcopy.dir/requires: src/hardcopy/CMakeFiles/hardcopy.dir/HardCopy.cpp.o.requires
src/hardcopy/CMakeFiles/hardcopy.dir/requires: src/hardcopy/CMakeFiles/hardcopy.dir/PSVectorOutput.cpp.o.requires
src/hardcopy/CMakeFiles/hardcopy.dir/requires: src/hardcopy/CMakeFiles/hardcopy.dir/VectorOutput.cpp.o.requires
src/hardcopy/CMakeFiles/hardcopy.dir/requires: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeAction.cpp.o.requires
src/hardcopy/CMakeFiles/hardcopy.dir/requires: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizeActionP.cpp.o.requires
src/hardcopy/CMakeFiles/hardcopy.dir/requires: src/hardcopy/CMakeFiles/hardcopy.dir/VectorizePSAction.cpp.o.requires
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/requires

src/hardcopy/CMakeFiles/hardcopy.dir/clean:
	cd /home/ed/Coin3D/official/coin_build/src/hardcopy && $(CMAKE_COMMAND) -P CMakeFiles/hardcopy.dir/cmake_clean.cmake
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/clean

src/hardcopy/CMakeFiles/hardcopy.dir/depend:
	cd /home/ed/Coin3D/official/coin_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ed/Coin3D/official/coin /home/ed/Coin3D/official/coin/src/hardcopy /home/ed/Coin3D/official/coin_build /home/ed/Coin3D/official/coin_build/src/hardcopy /home/ed/Coin3D/official/coin_build/src/hardcopy/CMakeFiles/hardcopy.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/hardcopy/CMakeFiles/hardcopy.dir/depend

