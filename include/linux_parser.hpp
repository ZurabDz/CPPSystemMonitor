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

struct Constants {
  static string kProcDirectory() { return "/proc/"; };
  static string kCmdlineFilename() { return "/cmdline"; };
  static string kCpuinfoFilename() { return "/cpuinfo"; };
  static string kStatusFilename() { return "/status"; };
  static string kStatFilename() { return "/stat"; };
  static string kUptimeFilename() { return "uptime"; };
  static string kMemInfoFilename() { return "meminfo"; };
  static string kVersionFilename() { return "/version"; };
  static string kOSPath() { return "/etc/os-release"; };
  static string kPasswordPath() { return "/etc/passwd"; };
};

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
