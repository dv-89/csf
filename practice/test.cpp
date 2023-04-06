#include <iostream>
#include <time.h>
#include <stdlib.h>

using namespace std;

int main() {

  /*
  Start at the beginning of the array, maintain a sorted sub-array at the
  beginning. Compare e1 with e2, if e1 > e2, swap. Now e1 is the sorted
  sub-array (containing only a single element).

  Continue to the next element e2. If e2 > e3, swap. Now our sorted sub-array
  contains 2 elements (e1 and e2) and we need to ensure they're sorted. So if e1
  > e2, we swap e1 with e2.

  Keep going until the sorted sub-array consists of every element of the
  original array.
  */

  srand(time(NULL));
  int array[10];
  for (int i = 0; i < 10; i++) {
    array[i] = rand() % 100;
    // array[i] = 10 - i;
  }

  cout << "Before sort:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << array[i] << " ";
  }
  
  
  cout << endl  << endl;
  

  int numIterations = 0;

  // Implement insertion sort here

  // Sequential comparison
  
  for (int i = 0; i < 9; i++) {
    cout << "i: " << i << endl;
    numIterations++;
    if (array[i] > array[i + 1]) {
      int temp = array[i];
      array[i] = array[i + 1];
      array[i + 1] = temp;
    }
//cout << "arr[i-1] : " << array[i-1] << endl;
    cout << "After sequential comparison:" << endl;
    for (int i = 0; i < 10; i++) {
      cout << array[i] << " ";
    }
    cout << endl;

    // Insertion (into sorted sub-array)
    for (int j = i+1; j >= 0; j--) {
      numIterations++;
	  
      if (array[j] < array[j - 1]) {
        int temp = array[j];
        array[j] = array[j - 1];
        array[j - 1] = temp;
      }
    }

    cout << "After insertion:" << endl;
    for (int i = 0; i < 10; i++) {
      cout << array[i] << " ";
    }
    cout << endl << endl;
  }

  cout << "After sort:" << endl;
  for (int i = 0; i < 10; i++) {
    cout << array[i] << " ";
  }
  cout << endl;

  cout << "Number of iterations: " << numIterations << endl;
}