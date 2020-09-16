//
// Created by lpenguinl on 3/10/20.
//

#include "util.hpp"

#include <iterator>

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

std::string Util::GetProgressBar(double percent) {
  std::string result{"0%"};
  double size{50};

  double bars{percent * size};
  for (int i{0}; i < size; ++i) result.push_back(i < bars ? '|' : ' ');
  char str[8];
  snprintf(str, sizeof(str), "%.1f", percent * 100);

  return result + std::string(str) + "/100%";
}

std::vector<std::string> Util::GetValues(std::ifstream &ifstream,
                                         const std::string& value) {
  std::string line{};
  while (std::getline(ifstream, line)) {
    if (value.empty() || line.find(value) != std::string::npos) {
      std::stringstream ss(line);
      std::istream_iterator<std::string> beg(ss), end;
      return std::vector<std::string>(beg, end);
    }
  }

  return std::vector<std::string>();
}
std::ifstream Util::GetInputStream(const char *path) {
  std::ifstream ifstream(path);

  if (!ifstream) {
    throw std::runtime_error("None -- existing PID");
  }

  return ifstream;
}
