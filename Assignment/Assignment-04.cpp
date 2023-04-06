#include <iostream>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

/*
Sort the given array and print.
*/
void sortElements(int *elements, int size) {
  // Implement me.
  for (int i = 0; i < size - 1; i++) {
    for (int j = 0; j < size - i - 1; j++) {
      if (elements[j] > elements[j + 1]) {
        int temp = elements[j];
        elements[j] = elements[j + 1];
        elements[j + 1] = temp;
      }
    }
  }
}

/*
Prompt the user for the number of elements (between 1 and 10,000, 0 to quit).
Generate an array of random integers between 1 and 100.
Call sortElements() to sort and print.
*/
int main() {

  while (true) {

    int no_of_elements;
    cout << endl << "Enter no of elements : (1 - 10000, 0 to quit) = ";
    cin >> no_of_elements;

    if (no_of_elements == 0) {
      break;
    } else if (no_of_elements < 0 || no_of_elements > 10000) {
      cout << "Enter a valid number." << endl << endl;
      continue;
    }

    int elements[no_of_elements];

    // initialize random seed.
    srand(time(NULL));

    // generate random numbers between 1 and 100.
    for (int i = 0; i < no_of_elements; i++) {
      elements[i] = (rand() % 100) + 1;
    }

    // printing unsorted elements.
    cout << endl << "Unsorted elements are : ";
    for (int i = 0; i < no_of_elements; i++) {
      cout << elements[i] << " ";
    }
    cout << endl << endl;

    // function call
    sortElements(elements, no_of_elements);

    // printing sorted elements
    cout << "Sorted elements are : ";
    for (int i = 0; i < no_of_elements; i++) {
      cout << elements[i] << " ";
    }

    cout << endl;
  }
}