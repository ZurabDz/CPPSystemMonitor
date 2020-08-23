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

namespace Constants{
  constexpr const char* const kProcDirectory = "/proc/";
  constexpr const char* const kCmdlineFilename = "/cmdline";
  constexpr const char* const kCpuinfoFilename = "/cpuinfo";
  constexpr const char* const kStatusFilename = "/status";
  constexpr const char* const kStatFilename = "/stat";
  constexpr const char* const kUptimeFilename = "uptime";
  constexpr const char* const kMemInfoFilename = "meminfo";
  constexpr const char* const kVersionFilename = "/version";
  constexpr const char* const kOSPath = "/etc/os-release";
  constexpr const char* const kPasswordPath = "/etc/passwd";

}

// System
[[nodiscard]] string OperatingSystem();
[[nodiscard]] string Kernel();
std::vector<int>& Pids(std::vector<int>&);
std::pair<int, int> TotalAndRunningProcesses();
float MemoryUtilization();
[[nodiscard]] unsigned long int UpTime();
[[nodiscard]] unsigned long int UpTime(int pid);

enum ProcessCpuStates {
  kUtime = 14,
  kStime = 15,
  kCutime = 16,
  kCstime = 17,
  kStarttime = 22
};

long Jiffies();
long IdleJiffies();
unsigned long ActiveJiffies();
unsigned long ActiveJiffies(int pid);


// Processes
[[nodiscard]] string Command(int pid);
string Ram(int pid);
string Uid(int pid);
string User(int pid);

}  // namespace LinuxParser

#endif  // PLAYGROUND_LINUX_PARSER_HPP
