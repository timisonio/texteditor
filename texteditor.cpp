#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Line.h"
#include <cctype>

void clear_screen() {
#ifdef WIN32
  std::system("cls");
#else
  // Assume POSIX
  std::system ("clear");
#endif
}

int main() {
  std::vector<Line> file_contents; // Vector might not be the best datatype...
  file_contents.push_back(Line()); // Initalize with an empty line
  unsigned int current_Line_index = 0;
  std::string input = "";

	// main loop
  while (input != "e") {
		clear_screen();
    Line& current_Line = file_contents.at(current_Line_index);

    // Print file contents
    for (unsigned int i = 0; i < file_contents.size(); i++) {
      if (i != current_Line_index){
        std::cout << i << file_contents.at(i).get_contents() << std::endl;
      }
      else {
        // Print current string
        std::cout << '>' << file_contents.at(i).get_contents() << std::endl;
        // Print cursor
        for (int j = 0; j <= file_contents.at(i).get_cursor_position(); j++)
          std::cout << ' ';
        std::cout << '^' << std::endl;
      }
    }       

    // Print commands
    std::cout
      << "Commands: e for exit, i for insert, d for delete previous character, "
      << "n to place a newline, hjkl navigation, s save to filename, "
			<< "o open filename: ";

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
				if (current_Line.get_length() > 0) {
					current_Line.pop_back();
				}
				else {
					if (file_contents.size() > 1) {
						file_contents.erase(file_contents.begin() + current_Line_index);
						current_Line_index--;
					}
				}
				break;
				
				// movement
			case 'h':
			case 'j':
			case 'k':
			case 'l':
			case 'n': { // make space only exist in these cases
				// get number of spaces to move
				int spaces = 1;
				if (input.length() > 2) {
					// construct a string holding the number of spaces to move
					std::string string_spaces = "";
					for (unsigned int i = 2; i != input.length(); i++) {
						if (std::isdigit(input[i])) {
							string_spaces += input[i];
						}
					}
					spaces = std::stoi(string_spaces);
				}
				switch (input[0]) { // perform the move
				case 'h':
					for (int i = 0; i < spaces; i++)
						current_Line.left(); // the class will check if this is okay
					break;
				case 'l':
					for (int i = 0; i < spaces; i++)
						current_Line.right();
					break;
				case 'j':
					for (int i = 0; i < spaces; i++)
						if (current_Line_index < file_contents.size() - 1)
							current_Line_index++;
					break;
				case 'k':
					for (int i = 0; i < spaces; i++)
						if (current_Line_index > 0)
							current_Line_index--;
					break;
				case 'n':
					for (int i = 0; i < spaces; i++) {
						file_contents.insert(
							file_contents.begin() + current_Line_index + 1, Line()
							);
						current_Line_index++;
					}
					break;
				}
				break;
			}
				
			case 'o':
				if (input.length() > 1) {
					std::ifstream infile;
					infile.open(input.substr(2, std::string::npos));
					file_contents.clear();
					std::string line;
					bool added_a_line = false;
					while (std::getline(infile, line)) {
						// iterate through infile line by line
						file_contents.push_back(Line(line));
						added_a_line = true;
					}
					if (added_a_line == false)
						// make sure we always have at least one line
						file_contents.push_back(Line());
					current_Line_index = 0;
				}
				break;
          
			case 's': 
				if (input.length() > 1) {
					std::ofstream savefile;
					savefile.open(input.substr(2, std::string::npos));
					for (std::vector<Line>::iterator it = file_contents.begin();
							 it != file_contents.end(); it++) {
						// write out each line to the savefile
						savefile << it->get_contents();
						if (it != file_contents.end() - 1)
							savefile << std::endl;
					}
					savefile.close();
				}
				break;
      }
    }
  }
}
