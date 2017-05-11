CMAKE_MINIMUM_REQUIRED(VERSION 3.2)

SET(CMAKE_C_COMPILER "/mingw64/bin/gcc")
SET(CMAKE_CXX_COMPILER "/mingw64/bin/g++")

ADD_DEFINITIONS(-DQUARTER_DLL)

FIND_PACKAGE(OpenGL REQUIRED)
FIND_PACKAGE(Coin REQUIRED) # FIXME: The results of this macro is not cached.
SET(QT_USE_QTOPENGL true)
SET(QT_USE_QTUITOOLS true)
FIND_PACKAGE(Qt5 REQUIRED COMPONENTS Core 3DCore Gui Widgets UiTools)
SET(CMAKE_AUTOMOC ON)
SET(CMAKE_AUTOUIC ON)

QT5_ADD_RESOURCES(QuarterViewerResources "${CMAKE_CURRENT_SOURCE_DIR}/QuarterViewer.qrc")

#Minimal example
ADD_EXECUTABLE(Example "${CMAKE_CURRENT_SOURCE_DIR}/minimal.cpp")
TARGET_LINK_LIBRARIES(Example Quarter ${Qt5Core_LIBRARIES} ${Qt53DCore_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})

#Dynamic UI Loader example
ADD_EXECUTABLE(DynamicUILoaderExample "${CMAKE_CURRENT_SOURCE_DIR}/dynamicui.cpp" ${QuarterViewerResources})
TARGET_LINK_LIBRARIES(DynamicUILoaderExample Quarter ${Qt5Core_LIBRARIES} ${Qt53DCore_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})

#Direct UI loader example
ADD_EXECUTABLE(DirectUILoaderExample "${CMAKE_CURRENT_SOURCE_DIR}/directui.cpp" ui_QuarterViewer.h)
TARGET_LINK_LIBRARIES(DirectUILoaderExample Quarter ${Qt5Core_LIBRARIES} ${Qt53DCore_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES})

#Examiner example
ADD_EXECUTABLE(ExaminerExample "${CMAKE_CURRENT_SOURCE_DIR}/examiner.cpp" ${QuarterViewerResources})
TARGET_LINK_LIBRARIES(ExaminerExample Quarter ${Qt5Core_LIBRARIES} ${Qt53DCore_LIBRARIES} ${Qt5Gui_LIBRARIES} ${Qt5Widgets_LIBRARIES} ${Qt5UiTools_LIBRARIES})

#Inherit UI example
ADD_EXECUTABLE(InheritUIExample "${CMAKE_CURRENT_SOURCE_DIR}/inheritui.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/QuarterViewer.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/QuarterViewer.h"
  ui_QuarterViewer.h)
TARGET_LINK_LIBRARIES(InheritUIExample Quarter)

#Multiple document interface example
#SIM_QT5_AUTO_WRAP_CPP(MocSources "${CMAKE_CURRENT_SOURCE_DIR}/MdiMainWindow.h")
ADD_EXECUTABLE(MDIExample "${CMAKE_CURRENT_SOURCE_DIR}/mdi.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MdiMainWindow.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MdiMainWindow.h"
  "${CMAKE_CURRENT_SOURCE_DIR}/MdiQuarterWidget.cpp"
  "${CMAKE_CURRENT_SOURCE_DIR}/MdiQuarterWidget.h"
  ${MocSources}
)
TARGET_LINK_LIBRARIES(MDIExample Quarter)

#Superimposition example
#Examiner example
ADD_EXECUTABLE(SuperImpositionExample "${CMAKE_CURRENT_SOURCE_DIR}/superimposition.cpp")
TARGET_LINK_LIBRARIES(SuperImpositionExample Quarter)

INSTALL(TARGETS Example
  RUNTIME DESTINATION examples
)
INSTALL(TARGETS DynamicUILoaderExample
  RUNTIME DESTINATION examples
)
INSTALL(TARGETS DirectUILoaderExample
  RUNTIME DESTINATION examples
)
INSTALL(TARGETS ExaminerExample
  RUNTIME DESTINATION examples
)
INSTALL(TARGETS InheritUIExample
  RUNTIME DESTINATION examples
)
INSTALL(TARGETS MDIExample
  RUNTIME DESTINATION examples
)
INSTALL(TARGETS SuperImpositionExample
  RUNTIME DESTINATION examples
)
