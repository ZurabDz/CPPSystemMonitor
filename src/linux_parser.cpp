//
// Created by lpenguinl on 3/5/20.
//

#include "linux_parser.hpp"

#include <unistd.h>

#include <algorithm>
#include <filesystem>
#include <iostream>

#include "util.hpp"

using std::ifstream;
using std::string;
using std::to_string;
using std::vector;

namespace fs = std::filesystem;

string LinuxParser::OperatingSystem() {
  string line{};
  string key{};
  string value{};

  ifstream inputStream(Constants::kOSPath);
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

string LinuxParser::Kernel() {
  string line{};
  string os{}, kernel{};
  string placeHolder{};

  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::kProcDirectory,
           Constants::kVersionFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) inputStream >> os >> placeHolder >> kernel;

  return kernel;
}

vector<int> &LinuxParser::Pids(vector<int> &pids) {
  string fileName{};
  int pid{};

  for (const auto &entry : fs::directory_iterator(Constants::kProcDirectory)) {
    if (entry.is_directory()) {
      fileName = entry.path().filename();
      if (std::all_of(fileName.begin(), fileName.end(), isdigit)) {
        pid = std::stoi(fileName);
        pids.push_back(pid);
      }
    }
  }

  return pids;
}

float LinuxParser::MemoryUtilization() {
  string line{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::kProcDirectory,
           Constants::kMemInfoFilename);
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

  return static_cast<float>(totalValue - freeValue) /
         static_cast<float>(totalValue);
}

unsigned long int LinuxParser::UpTime() {
  std::string line{};
  long upTime{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::kProcDirectory,
           Constants::kUptimeFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) {
    std::getline(inputStream, line);
    std::stringstream lineStream(line);
    lineStream >> upTime;
  }
  return upTime;
}
long LinuxParser::Jiffies() {
  string line;
  string key;
  long jiffies = 0;
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::kProcDirectory,
           Constants::kStatFilename);
  std::ifstream filestream(buff);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::stringstream linestream(line);
    int value;
    // sum the values from the first line of the file
    // user + nice + system + idle + iowait + irq + softirq + steal
    for (int i = 0; i < 9; ++i) {
      if (i == 0) {
        linestream >> key;
      } else {
        linestream >> value;
        jiffies += value;
      }
    }
  }
  return jiffies;
}

// long LinuxParser::Jiffies() {
//  string line{};
//  string key{};
//
//  long jiffies{0};
//  int value{0};
//
//  ifstream fileStream(Constants::kProcDirectory() +
//  Constants::kStatFilename()); if (fileStream.is_open()) {
//    std::getline(fileStream, line);
//    std::stringstream stream(line);
//
//    std::string cpu;
//    stream >> cpu;
//
//    while (stream >> value) jiffies += value;
//  }
//
//  return jiffies;
//}

unsigned long LinuxParser::ActiveJiffies(int pid) {
  string line{};
  string placeholder{};

  unsigned long jiffies{};
  unsigned long processJiffies{};

  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d/%s", Constants::kProcDirectory,
           pid, Constants::kStatFilename);
  ifstream inputStream(buff);
  float runTime{1};
  if (inputStream.is_open()) {
    std::getline(inputStream, line);
    std::istringstream lineStream(line);
    float startTime{};

    for (int tokenId = 1; tokenId < 23; ++tokenId) {
      if (tokenId == ProcessCpuStates::kCstime ||
          tokenId == ProcessCpuStates::kCutime ||
          tokenId == ProcessCpuStates::kStime ||
          tokenId == ProcessCpuStates::kUtime) {
        lineStream >> jiffies;
        processJiffies += jiffies;

      } else if (tokenId == 22) {
        lineStream >> tokenId;
      } else
        lineStream >> placeholder;
    }

    runTime = UpTime() - startTime / static_cast<float>(sysconf(_SC_CLK_TCK));
  }

  return (processJiffies / sysconf(_SC_CLK_TCK)) / runTime * 100;
}

std::pair<int, int> LinuxParser::TotalAndRunningProcesses() {
  string line{};
  string key{};
  int totalProcesses{0};
  int runningProcesses{0};
  int found{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::kProcDirectory,
           Constants::kStatFilename);
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
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::kProcDirectory,
           pid, Constants::kCmdlineFilename);
  ifstream inputStream(buff);
  if (inputStream.is_open()) std::getline(inputStream, cmdLine);
  return cmdLine;
}

string LinuxParser::Ram(int pid) {
  string line{};
  string key{};
  unsigned long ram{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::kProcDirectory, pid,
           Constants::kStatFilename);
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

unsigned long int LinuxParser::UpTime(int pid) {
  string line{};
  string placeHolder;
  unsigned long startTime{};
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::kProcDirectory, pid,
           Constants::kStatFilename);
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

// unsigned long LinuxParser::IdleJiffies() {
//  string line{};
//  string key{};
//
//  unsigned long idleJiffies{};
//  ifstream fileStream(Constants::kProcDirectory() + "stat");
//  unsigned long value{};
//
//  if (fileStream.is_open()) {
//    fileStream >> key;
//
//    for (int i = 0; i < 5; ++i) {
//      if (i > 2) {
//        fileStream >> value;
//        idleJiffies += value;
//      } else {
//        fileStream >> value;
//      }
//    }
//  }
//  return idleJiffies;
//}
long LinuxParser::IdleJiffies() {
  string line;
  string key;
  long idleJiffies = 0;
  char buff[32];
  snprintf(buff, sizeof(buff), "%s%s", Constants::kProcDirectory,
           Constants::kStatFilename);
  std::ifstream filestream(buff);
  if (filestream.is_open()) {
    std::getline(filestream, line);
    std::stringstream linestream(line);
    int value;
    // sum the iddle ticks
    // idle + iowait
    for (int i = 0; i < 6; ++i) {
      if (i == 0) {
        linestream >> key;
      } else if (i > 3) {
        linestream >> value;
        idleJiffies += value;
      } else {
        linestream >> value;
      }
    }
  }
  return idleJiffies;
}

unsigned long LinuxParser::ActiveJiffies() { return Jiffies() - IdleJiffies(); }

string LinuxParser::Uid(int pid) {
  string line;
  string key;
  string uid;

  char buff[32];
  snprintf(buff, sizeof(buff), "%s%d%s", Constants::kProcDirectory, pid,
           Constants::kStatusFilename);
  ifstream inputStream(buff);

  if (inputStream.is_open()) {
    while (std::getline(inputStream, line)) {
      std::istringstream lineStream(line);
      while (lineStream >> key) {
        if (key == "Uid:") {
          lineStream >> uid;
          break;
        }
      }
    }
  }
  return uid;
}

string LinuxParser::User(int pid) {
  string line;
  string user;
  string uid;
  string placeHolder;

  ifstream fileStream(Constants::kPasswordPath);
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
