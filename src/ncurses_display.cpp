#include "ncurses_display.hpp"

#include <chrono>
#include <thread>

#include "util.hpp"

void NCursesDisplay::Display(System &system, int n) {
  initscr();
  noecho();
  cbreak();
  curs_set(0);
  start_color();

  int xMax{getmaxx(stdscr)};
  WINDOW *systemWindow = newwin(9, xMax, 0, 0);
  WINDOW *processWindow = newwin(3 + n, xMax, systemWindow->_maxy + 1, 0);

  for (int counter{0}; counter < 15; ++counter) {
    init_pair(1, COLOR_BLUE, COLOR_BLACK);
    init_pair(2, COLOR_GREEN, COLOR_BLACK);
    box(systemWindow, 0, 0);
    box(processWindow, 0, 0);

//    DisplaySystem(system, systemWindow);
//    DisplayProcesses(system, processWindow);
    wrefresh(systemWindow);
    wrefresh(processWindow);
    refresh();
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }

  delwin(systemWindow);
  delwin(processWindow);
  endwin();
}

//void NCursesDisplay::DisplaySystem(System &system, WINDOW *window) {
//  int row{0};
//  mvwprintw(window, ++row, 2, ("OS: " + system.OperatingSystem()).c_str());
//  mvwprintw(window, ++row, 2, ("GetKernelVersion: " + system.Kernel()).c_str());
//
//  mvwprintw(window, ++row, 2, "CPU: ");
//  wattron(window, COLOR_PAIR(1));
//  mvwprintw(window, row, 10, "");
////  wprintw(window, ProgressBar(system.ProcessorUtilization()).c_str());
//  wattroff(window, COLOR_PAIR(1));
//
//  mvwprintw(window, ++row, 2, "Memory: ");
//  wattron(window, COLOR_PAIR(1));
//  mvwprintw(window, row, 10, "");
////  wprintw(window, ProgressBar(system.MemoryUtilization()).c_str());
//  wattroff(window, COLOR_PAIR(1));
//
//  std::pair<int, int> ProcessCounter = system.TotalAndRunningProcesses();
//
//  mvwprintw(
//      window, ++row, 2,
//      ("Total Processes: " + std::to_string(ProcessCounter.first)).c_str());
//  mvwprintw(
//      window, ++row, 2,
//      ("Running Processes: " + std::to_string(ProcessCounter.second)).c_str());
//  mvwprintw(window, ++row, 2, ("Up Time: " + system.UpTime()).c_str());
//  wrefresh(window);
//}

//void NCursesDisplay::DisplayProcesses(System& system,
//                                      WINDOW *window) {
//  int row{0};
//  constexpr const int pidColumn{2};
//  constexpr const int userColumn{9};
//  constexpr const int cpuColumn{20};
//  constexpr const int ramColumn{35};
//  constexpr const int timeColumn{50};
//  constexpr const int commandColumn{65};
//
//  wattron(window, COLOR_PAIR(2));
//  mvwprintw(window, ++row, pidColumn, "PID");
//  mvwprintw(window, row, userColumn, "USER");
//  mvwprintw(window, row, cpuColumn, "CPU[%%]");
//  mvwprintw(window, row, ramColumn, "RAM[MB]");
//  mvwprintw(window, row, timeColumn, "TIME+");
//  mvwprintw(window, row, commandColumn, "COMMAND");
//  wattroff(window, COLOR_PAIR(2));
//
//  float cpu{};
//  char buffer[6];
//  std::string command{};
//  auto processes = system.FillProcesses();
//  mvwprintw(window, ++row, pidColumn, "test");
//  for (auto &process : processes){
//    std::this_thread::sleep_for(std::chrono::milliseconds(300));
//    mvwprintw(window, ++row, pidColumn + 5, /*std::to_string(process.Pid()).c_str())*/"ss");
//    mvwprintw(window, row, userColumn, process.User().c_str());
//    cpu = process.CpuUtilization();
//
//    snprintf(buffer, sizeof(buffer), "%.2f", cpu);
//    mvwprintw(window, row, cpuColumn, buffer);
//    mvwprintw(window, row, ramColumn, process.Ram().c_str());
//    mvwprintw(window, row, timeColumn,
//              Util::ElapsedTime(process.UpTime()).c_str());
//    command = process.Command()