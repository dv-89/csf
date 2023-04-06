//frequency and print sorted.
#include <iostream>
#include <map>
#include <stdlib.h>
#include <time.h>

using namespace std;

int main() {

  while (true) {
    int no_of_elements, temp = 0;
    cout << endl << "Enter no of elements : (1 - 10000, 0 to quit) = ";
    cin >> no_of_elements;

    if (no_of_elements == 0) {
      break;
    } else if (no_of_elements < 0 || no_of_elements > 10000) {
      cout << "Enter a valid number." << endl << endl;
      continue;
    }

    map<int, int> myMap;
    map<int, int>::iterator it;

    // initialize random seed.
    srand(time(NULL));

    cout << endl << "Elements: ";
    // generate and print random numbers between 1 to 10.
    for (int i = 0; i < no_of_elements; i++) {
      temp = (rand() % 10) + 1;

      it = myMap.begin();
      it = myMap.find(temp);
      if (it != myMap.end()) {
        // element found.
        //  increase the value of the key which iterator points to.
        it->second++;
      } else {
        // map doesn't have this key, so add this to map with value 1.
        // By default, a Map in C++ is sorted in increasing order based on its
        // key.
        myMap.insert(pair<int, int>(temp, 1));
      }
      cout << temp << " ";
    }

    cout << endl << endl;

    cout << "Frequencies: " << endl << endl;
    // print map values.
    for (map<int, int>::iterator itr = myMap.begin(); itr != myMap.end();
         ++itr) {
      std::cout << itr->first << ": " << itr->second << endl << endl;
    }
  }
}