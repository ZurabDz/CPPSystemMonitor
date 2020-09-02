//
// Created by lpenguinl on 3/6/20.
//

#ifndef PLAYGROUND_PROCESS_HPP
#define PLAYGROUND_PROCESS_HPP

#include <string>

class Process {
 public:
  Process(const int& pid_, double& cpuUtil_);

  [[nodiscard]] int Pid() const;
  [[nodiscard]] float CpuUtilization () const;
  [[nodiscard]] std::string Command() const;
  std::string User();
  std::string Ram();
  unsigned long UpTime();
  bool operator<(Process& otherProcess);

 private:
  int pid{};
  double cpuUtilization{};
};

#endif  // PLAYGROUND_PROCESS_HPP
