#include <iostream>
#include <sstream>
#include <string>

using namespace std;

void printVector();
/*
Implement a vector data structure using an array.
Feel free to add any global variables as needed.
*/
int capacity = 3; // capacity of original array
int count = 0;    // no of elements in array

// Main array pointer.
int *vectorArray = new int[capacity];

/*
Add an element to the vector.
*/
void add(int item) {
  // if (vectorArray == nullptr) {
  //   capacity = 3;
  //   count = 0;
  //   int *vectorArray = new int[capacity];
  // }

  if (count < capacity) {
    // add the element
    // cout << "count is = " << count << endl;
    *(vectorArray + count) = item;
    count++;
    cout << "Item " << item << " is added" << endl;
    // cout << "count is = " << count << endl;

  } else if (count == capacity) {
    cout << "vector full" << endl;
    cout << "capacity and count are = " << capacity << " and " << count << endl;

    int newsize = 2 * capacity;

    int *newVectorArray = new int[newsize];

    // copy the prev elements first and add the new element next.
    int i = 0;
    while (i < count) {
      // cout << endl << "i is = " << i << endl;
      cout << "element is = " << *(vectorArray + i)
           << " is copied to new array." << endl;
      newVectorArray[i] = vectorArray[i];
      if (i == capacity - 1) {
        newVectorArray[i + 1] = item;
        count++;
        cout << "Item " << item << " is added to index " << i + 1 << endl;
        //  cout << "count is = " << count << endl;
        break;
      }
      i++;
    }

    delete[] vectorArray; // free memory for old array
    vectorArray = newVectorArray;

    capacity = newsize;

    cout << "new vector with capacity " << capacity << " is created" << endl;
  }

  cout << "elements are = ";
  printVector();
}

/*
Access element at position index.
Return -1 if index is out of bounds.
*/
int get(int index) {
  // cout << "get called" << endl;

  int value = -1;
  int size = 0;

  while (size < count) {
    if (size == index) {
      value = *(vectorArray + size);
      break;
    }
    size++;
  }
  // what is value is really -1.
  if (value == -1) {
    cout << "Index out of bounds" << endl;
  } else {
    cout << "element of index " << index << " is " << value << endl;
  }
  // Implement me
  // If index out of bounds
  // print Index out of bounds.
  // else return the element.
  return value;
}

/*
Search the vector for item.
Return the index of first match.
*/
int find(int item) {
  // cout << "find called" << endl;
  if (vectorArray != nullptr) {
    int index = -1;
    int size = 0;

    while (*(vectorArray + size)) {
      if (*(vectorArray + size) == item) {
        index = size;
        break;
      }
      size++;
    }
    if (index == -1) {
      cout << item << " is not available" << endl;
    } else {
      cout << "Index of element " << item << " is " << index << endl;
    }

    return index;
  } else {
    cout << "There are no elements in vector" << endl;
    return -1;
  }
}

/*
Remove the item from the vector.
*/
void remove(int item) {
  cout << "remove called" << endl;

  int index = -1;
  int size = 0;

  while (*(vectorArray + size)) {
    if (*(vectorArray + size) == item) {

      index = size;
      break;
    }
    size++;
  }
  size = index;
  while (*(vectorArray + size)) {
    *(vectorArray + size) = *(vectorArray + size + 1);
    size++;
  }

  if (index == -1) {
    cout << "Item not available" << endl;
  } else {
    count--;
    cout << "element " << item << " is removed." << endl;
  }
}

/*
Return the size of the vector.
*/
int size() {

  // int length = 0;
  // // works for null terminated arrays.
  // while (*(vectorArray + length)) {
  //   length++;
  // }
  // cout << "length = " << length << endl;
  // // Implement me
  // return length;
  cout << "length of vector is = " << count << endl;
  return count;
}

/*
Clear the vector.
*/
void clear() {

  delete[] vectorArray;

  vectorArray = nullptr;
  capacity = 3;
  count = 0;
  int *vectorArray = new int[capacity];

  cout << "vector cleared" << endl;
}

/*
Print the contents of the vector.
*/
void printVector() {
  // cout << "printVector called" << endl;

  if (vectorArray != nullptr) {

    for (int i = 0; i < count; i++) {
      cout << *(vectorArray + i) << " ";
    }
  } else {
    cout << "There are no elements in the vector" << endl;
  }
}

/*
Main program driver.
*/
int main() {

  while (true) {
    cin.clear();
    string command;
    int number;
    int target = 0;
    cout << endl << endl << "Enter command (q to quit) : ";
    getline(cin, command);

    istringstream ss(command);
    string word1, word2;
    ss >> word1 >> word2;
    // cout << "word1 is = " << word1 << endl;
    // cout << "word2 is = " << word2 << endl;
    if (word1 == "q") {
      // clear number
      break;
    } else if (word2 == "") {
      if (word1 == "add" || word1 == "get" || word1 == "find" ||
          word1 == "remove") {
        cout << "invalid input. input number" << endl;
        continue;
      }
    } else {
      // convert it into number.
      number = stoi(word2);
    }

    if (word1 == "add") {
      target = 1;

    } else if (word1 == "get") {
      target = 2;
    } else if (word1 == "find") {
      target = 3;
    } else if (word1 == "remove") {
      target = 4;
    } else if (word1 == "size") {
      target = 5;
    } else if (word1 == "clear") {
      target = 6;
    } else if (word1 == "printVector") {
      target = 7;
    } else {
      cout << "Invalid command" << endl;
    }

    // switch.
    switch (target) {
    case 1:
      add(number);
      break;
    case 2:
      get(number);
      break;
    case 3:
      find(number);
      break;
    case 4:
      remove(number);
      break;
    case 5:
      size();
      break;
    case 6:
      clear();
      break;
    case 7:
      printVector();
      break;
    }
  }
}