//
// Created by penguin on 9/15/20.
//


#define CATCH_CONFIG_MAIN
#include "catch2.h"
#include "../include/linux_parser.hpp"


TEST_CASE("CPU CORE AMOUNT IS PARSED", "[GetCpuCores]") {
  REQUIRE(LinuxParser::GetNumberOfCores() == 2);
}