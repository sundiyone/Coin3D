CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

SET(CMAKE_C_COMPILER "/mingw64/bin/gcc")
SET(CMAKE_CXX_COMPILER "/mingw64/bin/g++")

SET(Library QuarterWidgetPlugin)
INCLUDE_DIRECTORIES(${CMAKE_CURRENT_SOURCE_DIR})

ADD_DEFINITIONS(-DQUARTER_DLL)

FILE(GLOB_RECURSE Sources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.cpp)
FILE(GLOB_RECURSE Headers RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.h)
FILE(GLOB_RECURSE Resources RELATIVE ${CMAKE_CURRENT_SOURCE_DIR} *.qrc)

#QT5_ADD_RESOURCES(ResourceSources ${Resources})

# Some convenient variables. The inclusion of the headers in the source variable is to force CMake to include the headers in VS project generation.
SET(AllSources ${Sources} ${MocSources} ${ResourceSources} ${Headers})
SET(AllLibs ${Coin_LIBRARY} ${QT_LIBRARIES} ${OPENGL_gl_LIBRARY} Quarter)

ADD_LIBRARY(${Library} SHARED ${AllSources})
TARGET_LINK_LIBRARIES(${Library} ${AllLibs})

#Install the designer plugin
INSTALL(TARGETS ${Library}
  LIBRARY DESTINATION "${QT_PLUGINS_DIR}/designer"
)
