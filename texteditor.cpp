#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Line.h"

int main() {
  std::vector<Line> file_contents;
  file_contents.push_back(Line());
  int current_Line_index = 0;
  
  std::string input = "";

  while (input != "e") {
    Line& current_Line = file_contents.at(current_Line_index);
    
    // Print current string
    std::cout << current_Line.get_contents() << std::endl;

    // Print cursor
    for (int i = 0; i < current_Line.get_cursor_position(); i++)
      std::cout << ' ';
    std::cout << '^' << std::endl;

    // Print commands
    std::cout
      << "Editing line: "
      << current_Line_index
      << std::endl
      << "Commands: e for exit, i for insert, d for delete previous character, "
      << "n to place a newline, hjkl navigation, s save to filename ";
    //, o open filename: ";

    // Get commands
    std::getline(std::cin, input);

    if (input.length() > 0) { // Don't mess up the switch statement
      switch (input[0]) {
      case 'i':
	if (input.length() > 1)
	  // insert everything from the 3rd character onwards
	  current_Line.insert(input.substr(2, std::string::npos)); 
	break;
      case 'd':
	current_Line.pop_back();
	break;

      case 'n':
	file_contents.push_back(Line());
	break;

      // movement
      case 'h':
	current_Line.left();
	break;
      case 'l':
	current_Line.right();
	break;
      case 'j':
	if(current_Line_index < file_contents.size() - 1)
	  current_Line_index++;
	break;
      case 'k':
	if(current_Line_index > 0)
	  current_Line_index--;
	break;

      //save/open
      case 's':
	if (input.length() > 1) {
	  std::ofstream savefile;
	  savefile.open(input.substr(2, std::string::npos));
	  for (std::vector<Line>::iterator it = file_contents.begin(); it != file_contents.end(); it++) {
	    savefile << it->get_contents();
	    if (it != file_contents.end() - 1)
	      savefile << std::endl;
	  }
	  savefile.close();
	}
	break;
      default:
	continue;
	break;
      }
    }
    
  }
}
