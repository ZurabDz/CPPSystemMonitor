set(sources
        validate_parser.cpp)
set(CMAKE_CXX_STANDARD 17)

add_executable(unittests ${sources})
target_link_libraries(unittests stdc++ system-monitor)