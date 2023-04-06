#include <algorithm>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

bool ispalindrome(string s) {
	//length of string
	int length = s.length();
	// cout << " length is = " << length;
	for (int i = 0; i < length; i++) {
		//  cout << endl
		//       << "s and rs is = " << s[i] << " " << s[length - 1 - i] << endl;
		if ((s[i] == s[length - 1 - i]) && (i == length - 1)) {
			return true;
		} else if (s[i] != s[length - 1 - i]) {
			return false;
		}
	}
}

bool areanagrams(string s1, string s2) {
	// check if both have same number of characters.
	if (s1.length() != s2.length()) {
    return false;
	}
	// if equal sort the words and compare each letter.
	sort(s1.begin(), s1.end());
	sort(s2.begin(), s2.end());

	for (int i = 0; i < s1.length(); i++) {

		if ((s1[i] == s2[i]) && (i == s1.length() - 1)) {

			return true;
		} else if (s1[i] != s2[i]) {

			return false;
		}
	}
}

int main() {
  std::ifstream myfile;
  myfile.open("input_A5.txt");

  // we can also do that using single line using class constructor.
  // ifstream myfile ("input.txt");

  // declare a string variable to hold the content of file.

  string myline;

  if (myfile.is_open()) {
    while (myfile.good()) {
      // get each line of file seperately and store it in myline.
      getline(myfile, myline);

      // split myline into two words using stringstream.
      istringstream ss(myline);
      string word1;
      string word2;
      ss >> word1 >> word2;
		
	  cout <<endl;
      // send the two words to different functions.
      cout << word1 << (ispalindrome(word1) ? " is a " : " is not a ")
           << "palindrome" << endl;

      cout << word1 << "," << word2
           << (areanagrams(word1, word2) ? " are " : " are not ") << "anagrams"
           << endl
           << endl;
    }
	myfile.close();
  }

  // read using >> operator;

  /* if (myfile.is_open()) {
      while (myfile.good()) {
        myfile >> mystring;
        cout << mystring << " ";

      }
    }
  */
  /*
  if (myfile.is_open()) {
    char mychar;
    while (myfile) {
      mychar = myfile.get();
      cout << mychar;
    }
  }
  */
}