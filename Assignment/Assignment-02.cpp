//Rolling Dicce.

//Write a program that will prompt the user for the number of dice to roll. Valid values are 1 to 10,000. Using an array, store the values of the rolled dice. Once all the values of the rolled dice are collected. Print out the value of each dice roll then the percentage of times each number is rolled.

// also all the values of dice should be printed in same character space.


#include <iomanip>
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {
  while (true) {
    int no_of_dice;
    cout << "Enter number of dice(1 - 10000, 0 to quit) : ";
    cin >> no_of_dice;

    if (no_of_dice == 0) {
      break;
    } else if (no_of_dice < 0 || no_of_dice > 10000) {
      cout << "Enter a valid number" << endl;
      continue;
    }

    int value[no_of_dice];
    int count[7] = {0, 0, 0, 0, 0, 0, 0};

    // initialize random seed
    srand(time(NULL));

    // generate number from 1 to 6 and increase the count of 1 if 1 is
    // generated. here count[0] will always be 0.
    for (int i = 0; i < no_of_dice; i++) {
      value[i] = rand() % 6 + 1;
      count[value[i]]++;
    }

    // print out the each dice vaalue.
    for (int i = 0; i < no_of_dice; i++) {

      string test = "#" + to_string(i + 1) + ": ";

      // string test = "#";
      // test += to_string(i + 1);
      // test += ": ";
      cout << setw(9) << left << test << value[i] << endl << endl;
    }

    // print percentages, use type casting to double if precision needed.
    cout << "Percentages: " << endl << endl;
    for (int i = 1; i < 7; i++) {
      cout << i << ": " << (double)(count[i] * 100) / no_of_dice << "%" << endl
           << endl;
    }
  }
}