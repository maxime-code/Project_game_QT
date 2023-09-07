cmake_minimum_required(VERSION 3.10)
project(CPP_QT_TPminiprojet)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_AUTOMOC ON)

find_package(Qt5Widgets CONFIG REQUIRED)

file (GLOB_RECURSE sourceCode src/*.cpp src/*.h)

add_executable(CPP_QT_TPminiprojet ${sourceCode} src/map_items.cpp src/map_items.hpp src/MenuWindows.cpp src/MenuWindows.h src/MySecondScene.cpp src/MySecondScene.hpp src/MyThirdScene.cpp src/MyThirdScene.hpp)

target_link_libraries(CPP_QT_TPminiprojet Qt5::Widgets)