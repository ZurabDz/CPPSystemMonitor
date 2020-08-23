//
// Created by lpenguinl on 3/6/20.
//

#include "process.hpp"

#include <string>
#include <vector>

#include "linux_parser.hpp"

using std::string;
// using std::to_string;
using std::vector;

Process::Process(const int& pid, float& cpuUtil)
    : pid_{pid}, cpuUtilization_{cpuUtil} {}
int Process::Pid() const { return pid_; }
float Process::CpuUtilization() const { return cpuUtilization_; }
string Process::Command() const { return LinuxParser::Command(pid_); }
string Process::Ram() { return LinuxParser::Ram(pid_);}
string Process::User() { return LinuxParser::User(pid_); }
unsigned long Process::UpTime() { return LinuxParser::UpTime(pid_); }
bool Process::operator<(Process& otherProcess) {
  return this->CpuUtilization() < otherProcess.CpuUtilization();
}