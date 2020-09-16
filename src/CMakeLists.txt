set(sources linux_parser.cpp
        process.cpp
        system.cpp
        ncurses_display.cpp
        util.cpp)

add_library(system-monitor ${sources})
target_link_libraries(system-monitor stdc++fs ${CURSES_LIBRARIES} stdc++)
