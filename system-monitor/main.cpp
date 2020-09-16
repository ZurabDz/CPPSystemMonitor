#include "ncurses_display.hpp"
#include "linux_parser.hpp"
#include <iostream>


int main() {
  System system;
//  NCursesDisplay::Display(system, 10);
//  system.Cpu().Utilization();

  std::cout << LinuxParser::GetNumberOfCores() << '\n';
  std::cout << LinuxParser::GetOSName() << '\n';
}
