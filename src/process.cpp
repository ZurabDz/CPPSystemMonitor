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

Process::Process(const int& pid_, double& cpuUtil_)
    : pid{pid_}, cpuUtilization{cpuUtil_} {}
int Process::Pid() const { return pid; }
float Process::CpuUtilization() const { return cpuUtilization; }
string Process::Command() const { return LinuxParser::Command(pid); }
string Process::Ram() { return LinuxParser::Ram(pid);}
string Process::User() { return LinuxParser::User(pid); }
unsigned long Process::UpTime() { return LinuxParser::UpTime(pid); }
bool Process::operator<(Process& otherProcess) {
  return this->CpuUtilization() < otherProcess.CpuUtilization();
}