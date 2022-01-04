cmake_minimum_required(VERSION 3.1)
project(qt_video_face_detection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(include)

set(MAIN_APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main_app.cpp)

QT5_WRAP_UI(UISrcs 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/ui_video_face_detection.ui)

QT5_WRAP_CPP(MOCrcs
						  ${MAIN_APP_SRC}
#              ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window.hpp
#              ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.cpp
#              ${CMAKE_CURRENT_SOURCE_DIR}/include/video_face_detection.hpp
#              ${CMAKE_CURRENT_SOURCE_DIR}/src/video_face_detection.cpp
)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_executable(qt_video_app ${MOCrcs} ${MAIN_APP_SRC})

qt5_use_modules(qt_video_app Core Gui Widgets)
