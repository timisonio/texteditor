#include <string>
#include "Line.h"

bool Line::insert(std::string input) {
  str1 += input;
  return true;
}

bool Line::pop_back() {
  if (str1.length() > 0) {
    str1.pop_back();
    return true;
  }
  else
    return false;
}

bool Line::left() {
  if (str1.length() > 0) {
    str2 = str1[str1.length() - 1] + str2;
    str1.pop_back();
    return true;
  }
  return false;
}

bool Line::right() {
  if (str2.length() > 0) {
    str1 += str2[0];
    str2.erase(0, 1);
    return true;
  }
  return false;
}
