#include "ncurses_display.hpp"
#include "linux_parser.hpp"


int main() {
  System system;
  NCursesDisplay::Display(system, 10);
//  system.Cpu().Utilization();
}
