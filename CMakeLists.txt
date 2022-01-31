cmake_minimum_required(VERSION 3.1)
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
INCLUDE_DIRECTORIES(${OpenCV_INCLUDE_DIRS})
include_directories(include)

set(MAIN_APP_SRC ${CMAKE_CURRENT_SOURCE_DIR}/src/main_app.cpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/include/main_window.hpp
                 ${CMAKE_CURRENT_SOURCE_DIR}/src/main_window.cpp
)

set(VIDEO_FACE_DETECTION_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/include/video_face_detection.hpp
        ${CMAKE_CURRENT_SOURCE_DIR}/src/video_face_detection.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/qclicklabel.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/qclicklabel.cpp)

set(IMAGE_LIST_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/include/image_item.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/image_item.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/image_list_model.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/image_list_model.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/include/image_list_delegate.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/image_list_delegate.cpp
	)

set(IMAGE_FILTER_SRC
	${CMAKE_CURRENT_SOURCE_DIR}/include/image_filter.hpp
	${CMAKE_CURRENT_SOURCE_DIR}/src/image_filter.cpp
)

QT5_WRAP_UI(VIDEO_FACE_DETECTION_UISrcs 
            ${CMAKE_CURRENT_SOURCE_DIR}/src/video_face_detection.ui)

QT5_WRAP_CPP(MAIN_MOCrcs
						  ${MAIN_APP_SRC}
)

QT5_WRAP_CPP(VIDEO_FACE_DETECTION_MOCrcs
						  ${VIDEO_FACE_DETECTION_SRC}
							)

QT5_WRAP_CPP(IMAGE_LIST_MOCrcs
						  ${IMAGE_LIST_SRC}
)
						
set(CMAKE_BINARY_DIR ${CMAKE_SOURCE_DIR}/build)

add_library(image_list
	${IMAGE_LIST_SRC}
	${IMAGE_LIST_MOCrcs}
)

add_library(video_face_detection
	           ${VIDEO_FACE_DETECTION_MOCrcs}
                   ${VIDEO_FACE_DETECTION_SRC}
                   ${VIDEO_FACE_DETECTION_UISrcs}
)

target_link_libraries(video_face_detection
	${OpenCV_LIBS}
	image_list
)

add_library(image_filter
	${IMAGE_FILTER_SRC}
)

target_link_libraries(image_filter
	${OpenCV_LIBS}
)

add_executable(qt_video_app ${MAIN_MOCrcs} ${MAIN_APP_SRC})

target_link_libraries(qt_video_app
	video_face_detection
	)

qt5_use_modules(image_list Core Gui Widgets)
qt5_use_modules(qt_video_app Core Gui Widgets)
qt5_use_modules(video_face_detection Core Gui Widgets)
