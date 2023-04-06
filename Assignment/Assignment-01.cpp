// Right angled Triangle - Hollow

// Print a right angled triangle which takes user input height of triangle, and it should be hollow inside. i.e only border should be present.

#include <iostream>
#include <string>
using namespace std;
// first time

// int main() {

//   while (true) {
//     string input;

//     cout << "Enter height: ";
//     cin >> input;
//     if (input == "x") {
//       break;
//     }

//     int height = stoi(input);

//     if (height < 1) {
//       cout << "invalid input" << endl;
//     }
//     for (int row = 1; row <= height; row++) {
//       for (int e = 1; e <= row; e++) {
//         // 1. working with each element of a row seperately.
//         // 2. first and last element should be printed for all rows except
//         last
//         // row
//         // 3. last row print all elements as *
//         if (e == 1) {
//           cout << "*";
//           if (row == 1) {
//             cout << endl;
//           }
//         } else if (row == height) {
//           // print * height or row times
//           for (int i = 1; i < height; i++) {
//             cout << "*";
//           }
//           cout << endl;
//           break;
//         } else if (e == row) {
//           cout << "*" << endl;
//         } else {
//           cout << " ";
//         }
//       }
//     }
//   }
// }
bool custom_isdigit(char ch) { return ch >= '0' && ch <= '9'; }

int custom_stoi(string s) {
  int final_num = 0, sign = 1;
  for (int i = 0; i < s.length(); i++) {
    if (i == 0 && (s[i] == '-' || s[i] == '+')) {
      sign = (s[i] == '+') ? 1 : -1;
    } else if (!custom_isdigit(s[i])) {
      break;
    } else {
      // value of 0 is 48
      // if s[i] is character '3' then 51-48 = 3
      final_num = final_num * 10 + (s[i] - '0');
    }
  }
  return final_num * sign;
}

int main() {

  while (true) {
    string input;
    cout << "Enter Height: ";
    cin >> input;
    if (input == "x")
      break;
    int height = custom_stoi(input);

    if (height < 1) {
      cout << "Invalid input" << endl;
    }

    for (int row = 1; row <= height; row++) {
      for (int element = 1; element <= row; element++) {
        if (element == 1 || element == row || row == height) {
          cout << "*";
        } else {
          cout << " ";
        }
      }
      cout << endl;
    }
  }
}