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
include src/bundles/CMakeFiles/bundles.dir/depend.make

# Include the progress variables for this target.
include src/bundles/CMakeFiles/bundles.dir/progress.make

# Include the compile flags for this target's objects.
include src/bundles/CMakeFiles/bundles.dir/flags.make

src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o: src/bundles/CMakeFiles/bundles.dir/flags.make
src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o: /home/ed/Coin3D/official/coin/src/bundles/SoBundle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bundles.dir/SoBundle.cpp.o -c /home/ed/Coin3D/official/coin/src/bundles/SoBundle.cpp

src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bundles.dir/SoBundle.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/bundles/SoBundle.cpp > CMakeFiles/bundles.dir/SoBundle.cpp.i

src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bundles.dir/SoBundle.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/bundles/SoBundle.cpp -o CMakeFiles/bundles.dir/SoBundle.cpp.s

src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.requires:
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.requires

src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.provides: src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.requires
	$(MAKE) -f src/bundles/CMakeFiles/bundles.dir/build.make src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.provides.build
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.provides

src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.provides.build: src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o

src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o: src/bundles/CMakeFiles/bundles.dir/flags.make
src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o: /home/ed/Coin3D/official/coin/src/bundles/SoMaterialBundle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o -c /home/ed/Coin3D/official/coin/src/bundles/SoMaterialBundle.cpp

src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bundles.dir/SoMaterialBundle.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/bundles/SoMaterialBundle.cpp > CMakeFiles/bundles.dir/SoMaterialBundle.cpp.i

src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bundles.dir/SoMaterialBundle.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/bundles/SoMaterialBundle.cpp -o CMakeFiles/bundles.dir/SoMaterialBundle.cpp.s

src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.requires:
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.requires

src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.provides: src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.requires
	$(MAKE) -f src/bundles/CMakeFiles/bundles.dir/build.make src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.provides.build
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.provides

src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.provides.build: src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o

src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o: src/bundles/CMakeFiles/bundles.dir/flags.make
src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o: /home/ed/Coin3D/official/coin/src/bundles/SoNormalBundle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bundles.dir/SoNormalBundle.cpp.o -c /home/ed/Coin3D/official/coin/src/bundles/SoNormalBundle.cpp

src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bundles.dir/SoNormalBundle.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/bundles/SoNormalBundle.cpp > CMakeFiles/bundles.dir/SoNormalBundle.cpp.i

src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bundles.dir/SoNormalBundle.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/bundles/SoNormalBundle.cpp -o CMakeFiles/bundles.dir/SoNormalBundle.cpp.s

src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.requires:
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.requires

src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.provides: src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.requires
	$(MAKE) -f src/bundles/CMakeFiles/bundles.dir/build.make src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.provides.build
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.provides

src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.provides.build: src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o

src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o: src/bundles/CMakeFiles/bundles.dir/flags.make
src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o: /home/ed/Coin3D/official/coin/src/bundles/SoVertexAttributeBundle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o -c /home/ed/Coin3D/official/coin/src/bundles/SoVertexAttributeBundle.cpp

src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/bundles/SoVertexAttributeBundle.cpp > CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.i

src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/bundles/SoVertexAttributeBundle.cpp -o CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.s

src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.requires:
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.requires

src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.provides: src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.requires
	$(MAKE) -f src/bundles/CMakeFiles/bundles.dir/build.make src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.provides.build
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.provides

src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.provides.build: src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o

src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o: src/bundles/CMakeFiles/bundles.dir/flags.make
src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o: /home/ed/Coin3D/official/coin/src/bundles/SoTextureCoordinateBundle.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o -c /home/ed/Coin3D/official/coin/src/bundles/SoTextureCoordinateBundle.cpp

src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/bundles/SoTextureCoordinateBundle.cpp > CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.i

src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/bundles && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/bundles/SoTextureCoordinateBundle.cpp -o CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.s

src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.requires:
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.requires

src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.provides: src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.requires
	$(MAKE) -f src/bundles/CMakeFiles/bundles.dir/build.make src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.provides.build
.PHONY : src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.provides

src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.provides.build: src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o

bundles: src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o
bundles: src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o
bundles: src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o
bundles: src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o
bundles: src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o
bundles: src/bundles/CMakeFiles/bundles.dir/build.make
.PHONY : bundles

# Rule to build all files generated by this target.
src/bundles/CMakeFiles/bundles.dir/build: bundles
.PHONY : src/bundles/CMakeFiles/bundles.dir/build

src/bundles/CMakeFiles/bundles.dir/requires: src/bundles/CMakeFiles/bundles.dir/SoBundle.cpp.o.requires
src/bundles/CMakeFiles/bundles.dir/requires: src/bundles/CMakeFiles/bundles.dir/SoMaterialBundle.cpp.o.requires
src/bundles/CMakeFiles/bundles.dir/requires: src/bundles/CMakeFiles/bundles.dir/SoNormalBundle.cpp.o.requires
src/bundles/CMakeFiles/bundles.dir/requires: src/bundles/CMakeFiles/bundles.dir/SoVertexAttributeBundle.cpp.o.requires
src/bundles/CMakeFiles/bundles.dir/requires: src/bundles/CMakeFiles/bundles.dir/SoTextureCoordinateBundle.cpp.o.requires
.PHONY : src/bundles/CMakeFiles/bundles.dir/requires

src/bundles/CMakeFiles/bundles.dir/clean:
	cd /home/ed/Coin3D/official/coin_build/src/bundles && $(CMAKE_COMMAND) -P CMakeFiles/bundles.dir/cmake_clean.cmake
.PHONY : src/bundles/CMakeFiles/bundles.dir/clean

src/bundles/CMakeFiles/bundles.dir/depend:
	cd /home/ed/Coin3D/official/coin_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ed/Coin3D/official/coin /home/ed/Coin3D/official/coin/src/bundles /home/ed/Coin3D/official/coin_build /home/ed/Coin3D/official/coin_build/src/bundles /home/ed/Coin3D/official/coin_build/src/bundles/CMakeFiles/bundles.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/bundles/CMakeFiles/bundles.dir/depend

