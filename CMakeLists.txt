cmake_minimum_required(VERSION 3.15)
project(PlayGround)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -pedantic -Wno-unused -Wsign-promo -Wshadow -Wundef -Wstrict-overflow=5")
find_package(Curses REQUIRED)

include_directories(${COURSES_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/include)

add_subdirectory(src)
add_subdirectory(system-monitor)
add_subdirectory(test)
