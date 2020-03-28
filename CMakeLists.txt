cmake_minimum_required(VERSION 3.15)
project(PlayGround)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(SOURCES src/main.cpp include/linux_parser.hpp src/linux_parser.cpp include/util.hpp include/process.hpp include/system.hpp src/process.cpp include/processor.hpp src/processor.cpp src/system.cpp include/ncurses_display.hpp src/ncurses_display.cpp src/util.cpp)

find_package(Curses REQUIRED)

include_directories(${COURSES_INCLUDE_DIR})
include_directories(include/)

add_executable(PlayGround ${SOURCES})
target_link_libraries(PlayGround stdc++fs ${CURSES_LIBRARIES})