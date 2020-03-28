//
// Created by lpenguinl on 3/5/20.
//

#ifndef PLAYGROUND_UTIL_HPP
#define PLAYGROUND_UTIL_HPP

#include <string>

namespace Util {
std::string& CustomReplace(std::string& line, const char& old1 = ' ',
                           const char& new1 = '_', const char& old2 = '=',
                           const char& new2 = ' ', const char& old3 = '"',
                           const char& new3 = ' ');

std::string ElapsedTime(unsigned long int seconds);

}  // namespace Util
#endif  // PLAYGROUND_UTIL_HPP
