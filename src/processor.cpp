//
// Created by lpenguinl on 3/6/20.
//
#include "processor.hpp"

#include <unistd.h>
#include <iostream>

#include "linux_parser.hpp"

float Processor::Utilization() const {
//  std::cout << static_cast<float>(LinuxParser::ActiveJiffies()) /
//      static_cast<float>(LinuxParser::Jiffies()) << '\n';
  return static_cast<float>(LinuxParser::ActiveJiffies()) /
         static_cast<float>(LinuxParser::Jiffies());
}