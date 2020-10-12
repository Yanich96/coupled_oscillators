cmake_minimum_required(VERSION 3.17)
project(code)

find_package(Qt5Widgets REQUIRED)
set(CMAKE_BUILD_TYPE Release)
set(CMAKE_CXX_STANDARD 14)

add_executable(code main.cpp system.h visualizer.h)
target_link_libraries(code Qt5::Widgets)