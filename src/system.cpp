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
#include "processor.hpp"
#include "util.hpp"

using std::size_t;
using std::string;
using std::vector;

Processor& System::Cpu() { return cpu_; }

vector<Process>& System::Processes() {
  vector<int> pids;
  pids = LinuxParser::Pids(pids);

  if (!processes_.empty()) processes_.clear();

  for (const auto& pid : pids) {
//    unsigned elapsedTime = LinuxParser::UpTime() - LinuxParser::UpTime(pid);
//        float cpuUtil = (static_cast<float>(LinuxParser::ActiveJiffies(pid)) /
//                         static_cast<float>(sysconf(_SC_CLK_TCK))) /
//                        static_cast<float>(elapsedTime) * 100;

    auto cpuUtil = static_cast<float>(LinuxParser::ActiveJiffies(pid));
    processes_.emplace_back(pid, cpuUtil);
  }
  std::sort(processes_.rbegin(), processes_.rend());
  return processes_;
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