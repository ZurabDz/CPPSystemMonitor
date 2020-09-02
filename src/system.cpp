//
// Created by lpenguinl on 3/6/20.
//

#include "system.hpp"

#include <unistd.h>

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <chrono>
#include <thread>

#include "linux_parser.hpp"
#include "process.hpp"
#include "util.hpp"

using std::size_t;
using std::vector;

vector<Process>& System::FillProcesses() {
  vector<int> pids{LinuxParser::Pids()};
  if (!processes.empty()) processes.clear();
  for (auto const pid : pids) {
    auto cpuUtil = static_cast<double>(LinuxParser::ActiveJiffies(pid));
//    processes.emplace_back(pid, cpuUtil);
  }

  std::sort(processes.rbegin(), processes.rend());
  return processes;
}

std::string System::OperatingSystem() const {
  return LinuxParser::OperatingSystem();
}

std::string System::Kernel() const { return LinuxParser::Kernel(); }

float System::MemoryUtilization() const {
  return LinuxParser::MemoryUtilization();
}

std::pair<int, int> System::TotalAndRunningProcesses() const {
  return LinuxParser::TotalAndRunningProcesses();
}

string System::UpTime() const {
  return Util::ElapsedTime(LinuxParser::UpTime());
}
double System::ProcessorUtilization() const {
  return static_cast<double>(LinuxParser::ActiveJiffies()) /
         static_cast<double>(LinuxParser::Jiffies());
}
