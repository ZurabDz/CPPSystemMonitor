//
// Created by lpenguinl on 3/6/20.
//

#ifndef PLAYGROUND_NCURSES_DISPLAY_HPP
#define PLAYGROUND_NCURSES_DISPLAY_HPP

#include <ncurses.h>

#include "system.hpp"

namespace NCursesDisplay {

void Display(System& system, int n);
void DisplaySystem(System& system, WINDOW* window);
void DisplayProcesses(System& system, WINDOW* window);

}  // namespace NCursesDisplay

#endif  // PLAYGROUND_NCURSES_DISPLAY_HPP
