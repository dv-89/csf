#include <iostream>
#include <stack>

using namespace std;

int x =0,y =0; // current coordinates

void currPos(int x, int y){
  cout << "current position is (" << x << ", " << y << ")"<< endl;
}

int main() {
  while(true){
    x = 0;
    y = 0;
    string input;
    int n;
    
    cout << "Enter n value (q to quit) : " ;
    cin >> input;
    if(input == "q" || input == "Q"){
      break;
    }
    n = stoi(input);
    cout << n <<" x " << n << " playing board is created." <<endl <<endl;

    //create a stack to perform undo function.
    stack<int> myStack;

    currPos(x,y);

    while(true){
      string s;
      int target =0;
      cout << endl << "Enter direction (u,d,l,r) (e to exit board): " ;
      cin >> s;

      if(s == "e"){
        break;
      }else if(s == "u"){
        target = 1;
      } else if (s == "d"){
        target = 2;
      }else if (s == "l"){
        target = 3;
      }else if (s == "r"){
        target = 4;
      }else if (s == "position" || s == "p"){
        target = 5;
      }else if (s == "undo"){
        target = 6;
      }else{
        cout << "invalid input" << endl;
      }

      switch(target){
        case 1:
            y--;
            if(y < 0){
              y++;
              cout << "Already at top cannot go further." << endl;
              continue;
            }
            myStack.push(target);
            currPos(x,y);
            break; 
        case 2:
            y++;
           if(y > n){
              y--;
              cout << "Already at bottom cannot go downwards." << endl;
              continue;
            }
            myStack.push(target);
            currPos(x,y);
            break;
        case 3:
            x--;
            if (x < 0){
              x++;
              cout << "Already at far left cannot go further." << endl;
              continue;
            }
            myStack.push(target);
            currPos(x,y);
            break; 
        case 4:
            x++;
            if(x > n){
              x--;
              cout << "Already at far right cannot go further." << endl;
              continue;
            }
            myStack.push(target);
            currPos(x,y);
            break;            
        case 5:
            currPos(x,y);
        
        case 6:
            //undo operation.
            if(myStack.empty()){
              cout << "No Prev History to undo" << endl;
            }else if(myStack.top() == 1){
              y++;
              currPos(x,y);
              myStack.pop();
              continue;
            } else if(myStack.top() == 2){
              y--;
              currPos(x,y);
              myStack.pop();
              continue;
            }else if(myStack.top() == 3){
              x++;
              currPos(x,y);
              myStack.pop();
              continue;
            } else if(myStack.top() == 4){
              x--;
              currPos(x,y);
              myStack.pop();
              continue;
            } 

      }

          
    }
  }
}