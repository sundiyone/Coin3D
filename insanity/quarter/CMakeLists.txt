CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(Quarter LANGUAGES C CXX)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/SIMCMakeMacros/")

#SET(CMAKE_C_COMPILER "/mingw64/bin/gcc")
#SET(CMAKE_CXX_COMPILER "/mingw64/bin/g++")

# Add an option to enable static builds
OPTION(Quarter_BUILD_STATIC_LIBRARY "Build static library instead of shared library (DLL, so etc..)" OFF)
OPTION(Quarter_BUILD_PLUGIN "Build Quarter plugin for QT Designer" OFF)
OPTION(Quarter_BUILD_EXAMPLES "Build Quarter example applications" OFF)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Coin REQUIRED) # FIXME: The results of this macro is not cached.
SET(QT_USE_QTOPENGL true)
SET(QT_USE_QTUITOOLS true)
FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core 3DCore Gui Widgets)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)
MESSAGE("Qt5Core_LIBRARIES    = ${Qt5Core_LIBRARIES}")
MESSAGE("Qt53DCore_LIBRARIES  = ${Qt53DCore_LIBRARIES}")
MESSAGE("Qt5Gui_LIBRARIES     = ${Qt5Gui_LIBRARIES}")
MESSAGE("Qt5Widgets_LIBRARIES = ${Qt5Widgets_LIBRARIES}")
SET(QT_INCLUDE_DIR ${Qt5Core_INCLUDES} ${Qt53DCore_INCLUDES} ${Qt5Gui_INCLUDES} ${Qt5Widgets_INCLUDES})
LINK_DIRECTORIES(${QT_LIB_DIR} ${Coin_LIB_DIR} ${OPENGL_gl_DIRECTORY})
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR} ${Coin_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})

ADD_DEFINITIONS(${Coin_DEFINES})
ADD_DEFINITIONS(${QT_DEFINITIONS})

# config.h
SET(QUARTER_MAJOR_VERSION "1")
SET(QUARTER_MINOR_VERSION "1")
SET(QUARTER_MICRO_VERSION "0")
CONFIGURE_FILE(config.h.cmake.in "${PROJECT_BINARY_DIR}/config.h")

INCLUDE_DIRECTORIES(${PROJECT_BINARY_DIR})
# You need this or Quarter will walk through the standard include locations for Coin.
include_directories("/home/ed/Coin3D/coin4_install/include")

# What to build
ADD_SUBDIRECTORY(src)

SET(CMAKE_INSTALL_PREFIX /home/ed/Coin3D/coin4_install)

#Install the public headers
INSTALL(DIRECTORY include/Quarter/ DESTINATION include/Quarter
        FILES_MATCHING PATTERN "*.h"
        PATTERN ".hg" EXCLUDE)

