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
include src/manips/CMakeFiles/manips.dir/depend.make

# Include the progress variables for this target.
include src/manips/CMakeFiles/manips.dir/progress.make

# Include the compile flags for this target's objects.
include src/manips/CMakeFiles/manips.dir/flags.make

src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoClipPlaneManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_1)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoClipPlaneManip.cpp

src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoClipPlaneManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoClipPlaneManip.cpp > CMakeFiles/manips.dir/SoClipPlaneManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoClipPlaneManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoClipPlaneManip.cpp -o CMakeFiles/manips.dir/SoClipPlaneManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoDirectionalLightManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_2)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoDirectionalLightManip.cpp

src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoDirectionalLightManip.cpp > CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoDirectionalLightManip.cpp -o CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoPointLightManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_3)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoPointLightManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoPointLightManip.cpp

src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoPointLightManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoPointLightManip.cpp > CMakeFiles/manips.dir/SoPointLightManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoPointLightManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoPointLightManip.cpp -o CMakeFiles/manips.dir/SoPointLightManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoSpotLightManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_4)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoSpotLightManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoSpotLightManip.cpp

src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoSpotLightManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoSpotLightManip.cpp > CMakeFiles/manips.dir/SoSpotLightManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoSpotLightManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoSpotLightManip.cpp -o CMakeFiles/manips.dir/SoSpotLightManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoTransformManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_5)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoTransformManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoTransformManip.cpp

src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoTransformManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoTransformManip.cpp > CMakeFiles/manips.dir/SoTransformManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoTransformManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoTransformManip.cpp -o CMakeFiles/manips.dir/SoTransformManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoCenterballManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_6)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoCenterballManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoCenterballManip.cpp

src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoCenterballManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoCenterballManip.cpp > CMakeFiles/manips.dir/SoCenterballManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoCenterballManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoCenterballManip.cpp -o CMakeFiles/manips.dir/SoCenterballManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoHandleBoxManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_7)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoHandleBoxManip.cpp

src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoHandleBoxManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoHandleBoxManip.cpp > CMakeFiles/manips.dir/SoHandleBoxManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoHandleBoxManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoHandleBoxManip.cpp -o CMakeFiles/manips.dir/SoHandleBoxManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoJackManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_8)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoJackManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoJackManip.cpp

src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoJackManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoJackManip.cpp > CMakeFiles/manips.dir/SoJackManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoJackManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoJackManip.cpp -o CMakeFiles/manips.dir/SoJackManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoTabBoxManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_9)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoTabBoxManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoTabBoxManip.cpp

src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoTabBoxManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoTabBoxManip.cpp > CMakeFiles/manips.dir/SoTabBoxManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoTabBoxManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoTabBoxManip.cpp -o CMakeFiles/manips.dir/SoTabBoxManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoTrackballManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_10)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoTrackballManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoTrackballManip.cpp

src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoTrackballManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoTrackballManip.cpp > CMakeFiles/manips.dir/SoTrackballManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoTrackballManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoTrackballManip.cpp -o CMakeFiles/manips.dir/SoTrackballManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoTransformBoxManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_11)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoTransformBoxManip.cpp

src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoTransformBoxManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoTransformBoxManip.cpp > CMakeFiles/manips.dir/SoTransformBoxManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoTransformBoxManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoTransformBoxManip.cpp -o CMakeFiles/manips.dir/SoTransformBoxManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o

src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o: /home/ed/Coin3D/official/coin/src/manips/SoTransformerManip.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_12)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/SoTransformerManip.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/SoTransformerManip.cpp

src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/SoTransformerManip.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/SoTransformerManip.cpp > CMakeFiles/manips.dir/SoTransformerManip.cpp.i

src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/SoTransformerManip.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/SoTransformerManip.cpp -o CMakeFiles/manips.dir/SoTransformerManip.cpp.s

src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.requires

src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.provides: src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.provides

src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o

src/manips/CMakeFiles/manips.dir/commoncode.cpp.o: src/manips/CMakeFiles/manips.dir/flags.make
src/manips/CMakeFiles/manips.dir/commoncode.cpp.o: /home/ed/Coin3D/official/coin/src/manips/commoncode.cpp
	$(CMAKE_COMMAND) -E cmake_progress_report /home/ed/Coin3D/official/coin_build/CMakeFiles $(CMAKE_PROGRESS_13)
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Building CXX object src/manips/CMakeFiles/manips.dir/commoncode.cpp.o"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++   $(CXX_DEFINES) $(CXX_FLAGS) -o CMakeFiles/manips.dir/commoncode.cpp.o -c /home/ed/Coin3D/official/coin/src/manips/commoncode.cpp

src/manips/CMakeFiles/manips.dir/commoncode.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/manips.dir/commoncode.cpp.i"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -E /home/ed/Coin3D/official/coin/src/manips/commoncode.cpp > CMakeFiles/manips.dir/commoncode.cpp.i

src/manips/CMakeFiles/manips.dir/commoncode.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/manips.dir/commoncode.cpp.s"
	cd /home/ed/Coin3D/official/coin_build/src/manips && /usr/bin/c++  $(CXX_DEFINES) $(CXX_FLAGS) -S /home/ed/Coin3D/official/coin/src/manips/commoncode.cpp -o CMakeFiles/manips.dir/commoncode.cpp.s

src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.requires:
.PHONY : src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.requires

src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.provides: src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.requires
	$(MAKE) -f src/manips/CMakeFiles/manips.dir/build.make src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.provides.build
.PHONY : src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.provides

src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.provides.build: src/manips/CMakeFiles/manips.dir/commoncode.cpp.o

manips: src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o
manips: src/manips/CMakeFiles/manips.dir/commoncode.cpp.o
manips: src/manips/CMakeFiles/manips.dir/build.make
.PHONY : manips

# Rule to build all files generated by this target.
src/manips/CMakeFiles/manips.dir/build: manips
.PHONY : src/manips/CMakeFiles/manips.dir/build

src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoClipPlaneManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoDirectionalLightManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoPointLightManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoSpotLightManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoTransformManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoCenterballManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoHandleBoxManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoJackManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoTabBoxManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoTrackballManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoTransformBoxManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/SoTransformerManip.cpp.o.requires
src/manips/CMakeFiles/manips.dir/requires: src/manips/CMakeFiles/manips.dir/commoncode.cpp.o.requires
.PHONY : src/manips/CMakeFiles/manips.dir/requires

src/manips/CMakeFiles/manips.dir/clean:
	cd /home/ed/Coin3D/official/coin_build/src/manips && $(CMAKE_COMMAND) -P CMakeFiles/manips.dir/cmake_clean.cmake
.PHONY : src/manips/CMakeFiles/manips.dir/clean

src/manips/CMakeFiles/manips.dir/depend:
	cd /home/ed/Coin3D/official/coin_build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/ed/Coin3D/official/coin /home/ed/Coin3D/official/coin/src/manips /home/ed/Coin3D/official/coin_build /home/ed/Coin3D/official/coin_build/src/manips /home/ed/Coin3D/official/coin_build/src/manips/CMakeFiles/manips.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : src/manips/CMakeFiles/manips.dir/depend

