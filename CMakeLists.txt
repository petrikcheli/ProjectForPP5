cmake_minimum_required(VERSION 3.26)
project(OpenCV)

set(CMAKE_CXX_STANDARD 17)
set(ENV{OPENCV_DIR} "C:\\Users\\patem\\Documents\\opencv\\build")
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/")



find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})


include_directories(C:/Users/patem/Downloads/mysql-connector-c++-8.2.0-winx64/mysql-connector-c++-8.2.0-winx64/include/jdbc)
link_directories(C:/Users/patem/Downloads/mysql-connector-c++-8.2.0-winx64/mysql-connector-c++-8.2.0-winx64/lib64/vs14)


set(PROJECT_LINK_LIBS mysqlcppconn.lib)

add_executable(OpenCV main.cpp
        db.cpp
        db.h
        make_photo.cpp
        make_photo.h)
set(OpenCV_LIBS opencv_core opencv_imgproc opencv_highgui opencv_imgcodecs)
target_link_libraries(OpenCV ${OpenCV_LIBS})
target_link_libraries(OpenCV ${PROJECT_LINK_LIBS})
target_link_libraries(OpenCV C:/Users/patem/Downloads/mysql-connector-c++-8.2.0-winx64/mysql-connector-c++-8.2.0-winx64/lib64/vs14/mysqlcppconn.lib)


