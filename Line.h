#ifndef LINE_H
#define LINE_H

#include <string>

class Line{
 private:
  std::string str1;
  std::string str2;
  
public:
  bool insert(std::string input);
  bool pop_back();
  bool left();
  bool right();
  std::string get_contents() { return str1 + str2; }
  int get_cursor_position() { return str1.length(); }
};

#endif
