#include <iostream>
#include <fstream>
#include <string>
#include <list>
#include "Line.h"
using namespace std;

int main() {
  list<Line> file_contents;
  file_contents.push_back(Line());
  auto current_Line = file_contents.front();
  string input = "";

  while (input != "e") {
    // Print current string
    cout << current_Line.get_contents() << endl;

    // Print cursor
    for (int i = 0; i < current_Line.get_cursor_position(); i++)
      cout << ' ';
    cout << '^' << endl;

    // Print commands
    cout << "Commands: e for exit, i for insert, d for delete previous character, hjkl navigation, s save to filename "; //, o open filename: ";

    // Get commands
    getline(cin, input);

    // Don't mess up the switch statement
    if (input.length() == 0)
      continue;

    switch (input[0]) {
    case 'i':
      if (input.length() > 1)
	current_Line.insert(input.substr(2, string::npos));
      break;
    case 'd':
      current_Line.pop_back();
      break;

    // movement
    case 'h':
      current_Line.left();
      break;
    case 'l':
      current_Line.right();
      break;

    //save/open
    // case 's':
    //   if (input.length() > 1)
    //   {
    // 	ofstream savefile;
    // 	savefile.open(input.substr(2, string::npos));
    // 	savefile << str1 << str2;
    // 	savefile.close();
    //   }
    //   break;

    default:
      continue;
      break;
    }
    
  }
}
