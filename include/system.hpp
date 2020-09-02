//
// Created by lpenguinl on 3/6/20.
//

#ifndef PLAYGROUND_SYSTEM_HPP
#define PLAYGROUND_SYSTEM_HPP

#include <string>
#include <vector>

#include "process.hpp"
using std::string;

class System {
 public:
  [[nodiscard]] std::vector<Process>& FillProcesses();

  [[nodiscard]] double ProcessorUtilization() const;
  [[nodiscard]] std::string OperatingSystem() const;
  [[nodiscard]] std::string Kernel() const;

  [[nodiscard]] float MemoryUtilization() const;
  [[nodiscard]] string UpTime() const;
  [[nodiscard]] std::pair<int, int> TotalAndRunningProcesses() const;


 private:
  std::vector<Process> processes;
};

#endif  // PLAYGROUND_SYSTEM_HPP
