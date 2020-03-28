//
// Created by lpenguinl on 3/6/20.
//

#ifndef PLAYGROUND_SYSTEM_HPP
#define PLAYGROUND_SYSTEM_HPP

#include <string>
#include <vector>

#include "process.hpp"
#include "processor.hpp"

using std::string;

class System {
 public:
  Processor& Cpu();
  std::vector<Process>& Processes();

  [[nodiscard]] std::string OperatingSystem() const;
  [[nodiscard]] std::string Kernel() const;

  [[nodiscard]] float MemoryUtilization() const;
  [[nodiscard]] string UpTime() const;
  [[nodiscard]] std::pair<int, int> TotalAndRunningProcesses() const;


 private:
  Processor cpu_{};
  std::vector<Process> processes_{};
};

#endif  // PLAYGROUND_SYSTEM_HPP
