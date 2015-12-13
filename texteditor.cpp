#include <iostream>
#include <fstream>
#include <string>
using namespace std;

int main() {
  string str1; // Left of cursor
  string str2; // Right of cursor
  string input = "";

  while (input != "e") {
    // Print current string
    cout << str1 << str2 << endl;

    // Print cursor
    for (int i = 0; i < str1.length(); i++)
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
	str1 += input.substr(2, string::npos);
      break;
    case 'd':
      if (str1.length() > 0)
	str1.pop_back();
      break;

    // movement
    case 'h':
      if (str1.length() > 0) {
	str2 = str1[str1.length() - 1] + str2;
	str1.pop_back();
      }
      break;
    case 'l':
      if (str2.length() > 0) {
	str1 += str2[0];
	str2.erase(0, 1);
      }
      break;

    //save/open
    case 's':
      if (input.length() > 1)
      {
	ofstream savefile;
	savefile.open(input.substr(2, string::npos));
	savefile << str1 << str2;
	savefile.close();
      }
      break;

    default:
      continue;
      break;
    }
    
  }
}
