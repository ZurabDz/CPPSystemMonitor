cmake_minimum_required(VERSION 3.15)
project(PlayGround)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused -Werror -Wsign-promo -Wshadow -Wundef -Wstrict-overflow=5")
set(SOURCES src/main.cpp src/linux_parser.cpp src/process.cpp src/processor.cpp src/system.cpp src/ncurses_display.cpp src/util.cpp)

find_package(Curses REQUIRED)

include_directories(${COURSES_INCLUDE_DIR})
include_directories(include/)

add_executable(PlayGround ${SOURCES})
target_link_libraries(PlayGround stdc++fs ${CURSES_LIBRARIES})