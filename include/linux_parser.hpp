//
// Created by lpenguinl on 3/5/20.
//

#ifndef PLAYGROUND_LINUX_PARSER_HPP
#define PLAYGROUND_LINUX_PARSER_HPP

#include <fstream>
#include <string>
#include <vector>

using std::string;

namespace LinuxParser {
// System
[[nodiscard]] string GetOSName();
[[nodiscard]] string GetKernelVersion();
//std::vector<int> GetPids();
std::pair<int, int> TotalAndRunningProcesses();
double MemoryUtilization();
[[nodiscard]] double UpTime();
[[nodiscard]] double UpTime(int pid);

short GetNumberOfCores();

enum ProcessCpuStates {
  kUtime = 14,
  kStime = 15,
  kCutime = 16,
  kCstime = 17,
  kStarttime = 22
};

//long Jiffies();
//long IdleJiffies();
//unsigned long ActiveJiffies();
//double ActiveJiffies(int pid);


// Processes
[[nodiscard]] string Command(int pid);
string Ram(int pid);
string Uid(int pid);
string User(int pid);

}  // namespace LinuxParser

#endif  // PLAYGROUND_LINUX_PARSER_HPP
