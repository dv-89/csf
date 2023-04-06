#include <iostream>
#include <stack>
#include <time.h>
using namespace std;

int main(){
    int n;
    cout << "Enter value (max = 25) = ";
    cin >> n;

    //generate n random numbers and placeit in stack
    stack<int> myStack;

    //initialize random seed
    srand(time(NULL));

    for(int i=0; i<n; i++){
        myStack.push((rand()%n) + 1);
    }

    cout << "Elements in reverse order are = ";
    while(!myStack.empty()){
       cout << myStack.top() << " ";
       myStack.pop();
    }
    
}