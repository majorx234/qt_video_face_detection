cmake_minimum_required(VERSION 3.16)
project(qt_video_face_detection)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package( OpenCV REQUIRED )

set(CMAKE_AUTOMOC ON)
find_package(Qt5Widgets REQUIRED)
find_package(Qt5Core REQUIRED)
find_package( OpenCV REQUIRED )

include_directories(${Qt5Widgets_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${PROJECT_INCLUDE_DIR})
include_directories(${CMAKE_CURRENT_BINARY_DIR})
include_directories(${OpenCV_INCLUDE_DIRS})
include_directories(include)

set(MAIN_APP_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_app.cpp
)
Set(MAIN_APP_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.cpp
)

set(VIDEO_FACE_DETECTION_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/qclicklabel.cpp
)

set(VIDEO_FACE_DETECTION_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/video_face_detection.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/video_face_detection.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/qclicklabel.hpp
)

set(IMAGE_LIST_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image_item.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image_list_model.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image_list_delegate.cpp
)
set(IMAGE_LIST_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/image_item.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/image_list_model.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/image_list_delegate.hpp
)

set(IMAGE_FILTER_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/image_filter.cpp
)

set(IMAGE_FILTER_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/image_filter.hpp
)

set(CV_UTILS_SRC
    ${CMAKE_CURRENT_SOURCE_DIR}/src/cv_utils.cpp
)

set(CV_UTILS_HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/include/cv_utils.hpp
)

QT5_WRAP_UI(VIDEO_FACE_DETECTION_UISrcs 
    ${CMAKE_CURRENT_SOURCE_DIR}/src/video_face_detection.ui
)

QT5_WRAP_CPP(MAIN_MOCrcs
    ${MAIN_APP_HEADERS}
)

QT5_WRAP_CPP(VIDEO_FACE_DETECTION_MOCrcs
    ${VIDEO_FACE_DETECTION_HEADERS}
)

QT5_WRAP_CPP(IMAGE_LIST_MOCrcs
    ${IMAGE_LIST_HEADERS}
)

set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_library(image_list)
target_sources(image_list
    PRIVATE
    ${IMAGE_LIST_SRC}
    ${IMAGE_LIST_MOCrcs}
)
target_link_libraries(image_list
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

add_library(cv_utils)
target_sources(cv_utils
    PRIVATE
    ${CV_UTILS_SRC}
    ${CV_UTILS_HEADERS}
)

add_library(video_face_detection)
target_sources(video_face_detection
    PRIVATE
    ${VIDEO_FACE_DETECTION_MOCrcs}
    ${VIDEO_FACE_DETECTION_HEADERS}
    ${VIDEO_FACE_DETECTION_SRC}
    ${VIDEO_FACE_DETECTION_UISrcs}
)
target_link_libraries(video_face_detection
    ${OpenCV_LIBS}
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    image_list
    cv_utils
    image_filter
)

add_library(image_filter)
target_sources(image_filter
    PRIVATE
    ${IMAGE_FILTER_SRC}
    ${IMAGE_FILTER_HEADERS}
)
target_link_libraries(image_filter
    ${OpenCV_LIBS}
)

add_executable(qt_video_app)
target_sources(qt_video_app
    PRIVATE
    ${MAIN_MOCrcs}
    ${MAIN_APP_SRC}
    ${MAIN_APP_HEADERS}
)
target_link_libraries(qt_video_app
    video_face_detection
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)
