cmake_minimum_required(VERSION 3.1)
project(qt_video_face_detection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)


QT5_WRAP_UI(UISrcs 
            src/ui_video_face_detection.ui)

QT5_WRAP_CPP( MOCrcs 
              include/mainwindow.hpp
              src/mainwindow.cpp
              include/video_face_detection.hpp
              src/video_face_detection.cpp)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

