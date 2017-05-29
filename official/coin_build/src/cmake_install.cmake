# Install script for directory: /home/ed/Coin3D/official/coin/src

# Set the install prefix
if(NOT DEFINED CMAKE_INSTALL_PREFIX)
  set(CMAKE_INSTALL_PREFIX "/usr/local")
endif()
string(REGEX REPLACE "/$" "" CMAKE_INSTALL_PREFIX "${CMAKE_INSTALL_PREFIX}")

# Set the install configuration name.
if(NOT DEFINED CMAKE_INSTALL_CONFIG_NAME)
  if(BUILD_TYPE)
    string(REGEX REPLACE "^[^A-Za-z0-9_]+" ""
           CMAKE_INSTALL_CONFIG_NAME "${BUILD_TYPE}")
  else()
    set(CMAKE_INSTALL_CONFIG_NAME "")
  endif()
  message(STATUS "Install configuration: \"${CMAKE_INSTALL_CONFIG_NAME}\"")
endif()

# Set the component getting installed.
if(NOT CMAKE_INSTALL_COMPONENT)
  if(COMPONENT)
    message(STATUS "Install component: \"${COMPONENT}\"")
    set(CMAKE_INSTALL_COMPONENT "${COMPONENT}")
  else()
    set(CMAKE_INSTALL_COMPONENT)
  endif()
endif()

# Install shared libraries without execute permission?
if(NOT DEFINED CMAKE_INSTALL_SO_NO_EXE)
  set(CMAKE_INSTALL_SO_NO_EXE "1")
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCoin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCoin.so")
    file(RPATH_CHECK
         FILE "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCoin.so"
         RPATH "")
  endif()
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib" TYPE SHARED_LIBRARY FILES "/home/ed/Coin3D/official/coin_build/src/libCoin.so")
  if(EXISTS "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCoin.so" AND
     NOT IS_SYMLINK "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCoin.so")
    if(CMAKE_INSTALL_DO_STRIP)
      execute_process(COMMAND "/usr/bin/strip" "$ENV{DESTDIR}${CMAKE_INSTALL_PREFIX}/lib/libCoin.so")
    endif()
  endif()
endif()

if(NOT CMAKE_INSTALL_COMPONENT OR "${CMAKE_INSTALL_COMPONENT}" STREQUAL "Unspecified")
  file(INSTALL DESTINATION "${CMAKE_INSTALL_PREFIX}/lib/Coin/cmake" TYPE FILE FILES
    "/home/ed/Coin3D/official/coin_build/src/CoinConfig.cmake"
    "/home/ed/Coin3D/official/coin_build/src/CoinConfigVersion.cmake"
    )
endif()

if(NOT CMAKE_INSTALL_LOCAL_ONLY)
  # Include the install script for each subdirectory.
  include("/home/ed/Coin3D/official/coin_build/src/extensions/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/xml/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/actions/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/base/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/bundles/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/caches/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/details/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/draggers/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/elements/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/engines/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/errors/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/events/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/fields/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/fonts/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/glue/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/io/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/manips/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/misc/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/rendering/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/lists/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/nodekits/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/navigation/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/nodes/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/shapenodes/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/projectors/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/sensors/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/upgraders/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/3ds/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/collision/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/hardcopy/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/shadows/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/geo/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/threads/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/shaders/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/profiler/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/vrml97/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/foreignfiles/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/scxml/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/soscxml/cmake_install.cmake")
  include("/home/ed/Coin3D/official/coin_build/src/doc/cmake_install.cmake")

endif()

