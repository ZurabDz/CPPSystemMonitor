//
// Created by lpenguinl on 3/5/20.
//

#include "linux_parser.hpp"

#include <unistd.h>
#include <iostream>

#include <algorithm>
#include <filesystem>
#include <iostream>
#include <limits>

#include "constants.h"
#include "util.hpp"

using std::ifstream;
using std::string;
using std::to_string;
using std::vector;

namespace fs = std::filesystem;

short LinuxParser::GetNumberOfCores() {
  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%s%s", Constants::ProcDirectory,
           Constants::CpuinfoFilename);
  std::ifstream cpuFile = Util::GetInputStream(buffer);
  std::vector<std::string> values = Util::GetValues(cpuFile, "cpu cores");
  int result = std::stoi(values[3]);

  return result;
}

string LinuxParser::GetOSName() {
  string line{};
  string key{};
  string value{};

  ifstream inputStream(Constants::OSRealesePath);
    if (inputStream.is_open()) {
      while (std::getline(inputStream, line)) {
        line = Util::CustomReplace(line);

        std::istringstream lineStream(line);
        while (lineStream >> key >> value) {
          if (key == "PRETTY_NAME") {
            std::replace(value.begin(), value.end(), '_', ' ');
            return value;
          }
        }
      }
    }

  return value;
}

string LinuxParser::GetKernelVersion() {
  string line{};
  string os{}, kernel{};
  string placeHolder{};

  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::ProcDirectory,
           Constants::VersionFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) inputStream >> os >> placeHolder >> kernel;

  return kernel;
}

double LinuxParser::MemoryUtilization() {
  string line{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::ProcDirectory,
           Constants::MemInfoFilename);
  ifstream inputStream(buff);
  int totalValue{}, freeValue{}, value{};
  string key{};
  short counter{0};

  if (inputStream.is_open()) {
    while (std::getline(inputStream, line)) {
      std::istringstream lineStream{line};

      lineStream >> key >> value;
      if (key == "MemTotal:") {
        totalValue = value;
        ++counter;
      }
      if (key == "MemAvailable:") {
        freeValue = value;
        ++counter;
      }
      if (counter == 2) break;
    }
  }

  return static_cast<double>(totalValue - freeValue) /
         static_cast<double>(totalValue);
}

double LinuxParser::UpTime() {
  std::string line{};
  double upTime{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::ProcDirectory,
           Constants::UptimeFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) {
    std::getline(inputStream, line);
    std::stringstream lineStream(line);
    lineStream >> upTime;
  }
  return upTime;
}

// long LinuxParser::Jiffies() {
//  string line;
//  string key;
//  long jiffies = 0;
//  char buff[32];
//  snprintf(buff, sizeof(buff), "%s%s", Constants::ProcDirectory,
//           Constants::StatFilename);
//  std::ifstream filestream(buff);
//  if (filestream.is_open()) {
//    std::getline(filestream, line);
//    std::stringstream linestream(line);
//    int value;
//    // sum the values from the first line of the file
//    // user + nice + system + idle + iowait + irq + softirq + steal
//    for (int i = 0; i < 9; ++i) {
//      if (i == 0) {
//        linestream >> key;
//      } else {
//        linestream >> value;
//        jiffies += value;
//      }
//    }
//  }
//  return jiffies;
//}

// double LinuxParser::ActiveJiffies(int pid) {
//  string line{};
//  string placeholder{};
//
//  double jiffies{};
//  double processJiffies{};
//
//  char buff[32];
//  snprintf(buff, sizeof(buff), "%s%d/%s", Constants::ProcDirectory, pid,
//           Constants::StatFilename);
//  ifstream inputStream(buff);
//  float runTime{1};
//  if (inputStream.is_open()) {
//    std::getline(inputStream, line);
//    std::istringstream lineStream(line);
//    double startTime{};
//
//    for (int tokenId = 1; tokenId < 23; ++tokenId) {
//      if (tokenId == ProcessCpuStates::kCstime ||
//          tokenId == ProcessCpuStates::kCutime ||
//          tokenId == ProcessCpuStates::kStime ||
//          tokenId == ProcessCpuStates::kUtime) {
//        lineStream >> jiffies;
//        processJiffies += jiffies;
//
//      } else if (tokenId == 22) {
//        lineStream >> tokenId;
//      } else {
//        lineStream >> placeholder;
//        lineStream.clear();
//        lineStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
//      }
//
//      runTime =
//          (UpTime() - startTime) / static_cast<double>(sysconf(_SC_CLK_TCK));
//    }
//  }

//  return (processJiffies / static_cast<double>(sysconf(_SC_CLK_TCK))) /
//         runTime * 100;
//}

std::pair<int, int> LinuxParser::TotalAndRunningProcesses() {
  string line{};
  string key{};
  int totalProcesses{0};
  int runningProcesses{0};
  int found{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::ProcDirectory,
           Constants::StatFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) {
    while (std::getline(inputStream, line)) {
      std::istringstream lineStream(line);
      lineStream >> key;
      if (found == 2) break;
      if (key == "processes") {
        lineStream >> totalProcesses;
        ++found;
      } else if (key == "procs_running") {
        lineStream >> runningProcesses;
        ++found;
      }
    }
  }

  return std::make_pair(totalProcesses, runningProcesses);
}

string LinuxParser::Command(int pid) {
  std::string cmdLine{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::ProcDirectory, pid,
           Constants::CmdlineFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) std::getline(inputStream, cmdLine);
  return cmdLine;
}

string LinuxParser::Ram(int pid) {
  string line{};
  string key{};
  unsigned long ram{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::ProcDirectory, pid,
           Constants::StatFilename);
  ifstream inputStream(buff);

  if (inputStream.is_open()) {
    while (std::getline(inputStream, line)) {
      std::istringstream lineStream(line);
      lineStream >> key;
      if (key == "VmSize:") {
        lineStream >> ram;
        break;
      }
    }
  }

  return std::to_string(ram / 1000);
}

double LinuxParser::UpTime(int pid) {
  string line{};
  string placeHolder;
  unsigned long startTime{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::ProcDirectory, pid,
           Constants::StatFilename);
  ifstream inputStream(buff);

  if (inputStream.is_open()) {
    std::getline(inputStream, line);
    std::istringstream lineStream(line);
    for (int tokenId = 1; tokenId < 23; ++tokenId) {
      if (tokenId == ProcessCpuStates::kStarttime) {
        lineStream >> startTime;
        break;
      } else
        lineStream >> placeHolder;
    }
  }

  return startTime / sysconf(_SC_CLK_TCK);
}

// long LinuxParser::IdleJiffies() {
//  string line;
//  string key;
//  long idleJiffies = 0;
//  char buff[32];
//  snprintf(buff, sizeof(buff), "%s%s", Constants::ProcDirectory,
//           Constants::StatFilename);
//  std::ifstream filestream(buff);
//  if (filestream.is_open()) {
//    std::getline(filestream, line);
//    std::stringstream linestream(line);
//    int value;
//    // sum the iddle ticks
//    // idle + iowait
//    for (int i = 0; i < 6; ++i) {
//      if (i == 0) {
//        linestream >> key;
//      } else if (i > 3) {
//        linestream >> value;
//        idleJiffies += value;
//      } else {
//        linestream >> value;
//      }
//    }
//  }
//  return idleJiffies;
//}

// unsigned long LinuxParser::ActiveJiffies() { return Jiffies() -
// IdleJiffies(); }

string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string uid;

  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::ProcDirectory, pid,
           Constants::StatusFilename);
  ifstream inputStream(buff);

  if (inputStream.is_open()) {
    for (int i{0}; i < 9; ++i) {
      inputStream.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    }

    getline(inputStream, line);
    std::istringstream ss{line};

    ss >> key;
    ss >> uid;
  }
  return uid;
}

string LinuxParser::User(int pid) {
  string line;
  string user;
  string uid;
  string placeHolder;

  ifstream fileStream(Constants::PasswordPath);
  if (fileStream.is_open()) {
    while (std::getline(fileStream, line)) {
      std::replace(line.begin(), line.end(), ':', ' ');
      std::istringstream lineStream(line);
      lineStream >> user >> placeHolder >> uid;
      if (uid == Uid(pid)) break;
    }
  }
  return user;
}
