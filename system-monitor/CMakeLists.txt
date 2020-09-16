include_directories(${PROJECT_SOURCE_DIR}/include)

add_executable(prog main.cpp) 
target_link_libraries(prog system-monitor)