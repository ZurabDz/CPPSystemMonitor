//
// Created by lpenguinl on 3/10/20.
//

#include "util.hpp"

std::string &Util::CustomReplace(std::string &line, const char &old1,
                                 const char &new1, const char &old2,
                                 const char &new2, const char &old3,
                                 const char &new3) {
  for (auto &symbol : line) {
    if (symbol == old1) symbol = new1;
    if (symbol == old2) symbol = new2;
    if (symbol == old3) symbol = new3;
  }

  return line;
}

std::string Util::ElapsedTime(unsigned long seconds) {
  const unsigned int hour = seconds / 3600;
  short minute = (seconds % 3600) / 60;
  short second = (seconds % 3600) % 60;

  char buffer[32];
  snprintf(buffer, sizeof(buffer), "%.2d:%.2d:%.2d", hour, minute, second);
  std::string elapsedTime(buffer);

  return elapsedTime;
}