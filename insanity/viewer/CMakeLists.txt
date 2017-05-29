CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

PROJECT(viewer LANGUAGES CXX)
SET(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/../quarter4/SIMCMakeMacros")

SET(CMAKE_PREFIX_PATH "/usr/lib/x86_64-linux-gnu/qt5/lib/cmake")

FIND_PACKAGE(OpenGL REQUIRED)

# This is fucked somewhow!
#FIND_PACKAGE(Coin REQUIRED) # FIXME: The results of this macro is not cached.
#MESSAGE("Coin_LIBRARIES       = ${Coin_LIBRARIES}")
#MESSAGE("Coin_LIB_DIR         = ${Coin_LIB_DIR}")
#MESSAGE("Coin_INCLUDE_DIR     = ${Coin_INCLUDE_DIR}")
#MESSAGE("Coin_DEFINES         = ${Coin_DEFINES}")
set(Coin_LIBRARIES, "Coin;GL;Xext;SM;ICE;X11;dl;pthread")
set(Coin_LIB_DIR, "/home/ed/Coin3D/coin4_install/lib")
set(Coin_INCLUDE_DIR, "/home/ed/Coin3D/coin4_install/include")
set(Coin_LINK_FLAGS "-L${Coin_LIB_DIR}" )

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
MESSAGE("QT_INCLUDE_DIR       = ${QT_INCLUDE_DIR}")
SET(QT_LIBRARIES ${Qt5Core_LIBRARIES} ${Qt53DCore_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})
MESSAGE("QT_LIBRARIES         = ${QT_LIBRARIES}")
SET(AllLibs ${Coin_LIBRARIES} ${QT_LIBRARIES} ${OPENGL_LIBRARY} ${Extra_libraries})
MESSAGE("AllLibs              = ${AllLibs}")

LINK_DIRECTORIES(${QT_LIB_DIR} ${Coin_LIB_DIR} ${OPENGL_gl_DIRECTORY})
#INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR}/include/)
INCLUDE_DIRECTORIES(${QT_INCLUDE_DIR} ${Coin_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})


# What to build
add_executable(viewer viewer.cpp)
target_link_libraries(viewer ${AllLibs})
