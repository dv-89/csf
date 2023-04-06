#include <iostream>
#include <stack>

using namespace std;

int x = 0, y = 0; // current coordinates

void currPos(int x, int y) {
    cout << "current position is (" << x << ", " << y << ")" << endl;
}

int main() {
    while (true) {
        x = 0;
        y = 0;
        string input;
        int n;

        cout << "Enter n value (q to quit) : ";
        cin >> input;
        if (input == "q" || input == "Q") {
            break;
        }
        n = stoi(input);
        cout << n << " x " << n << " playing board is created." << endl << endl;

        // create a stack to perform undo function.
        stack<int> undoStack;
        stack<int> redoStack;

        currPos(x, y);

        while (true) {
            string s;
            int target = 0;
            cout << endl << "Enter direction (u,d,l,r) (e to exit board): ";
            cin >> s;

            if (s == "e") {
                break;
            }
            else if (s == "u") {
                target = 1;
            }
            else if (s == "d") {
                target = 2;
            }
            else if (s == "l") {
                target = 3;
            }
            else if (s == "r") {
                target = 4;
            }
            else if (s == "position" || s == "p") {
                target = 5;
            }
            else if (s == "undo") {
                target = 6;
            }
            else if (s == "redo") {
                target = 7;
            }
            else {
                cout << "invalid input" << endl;
            }

            switch (target) {
            case 1: // up
                x--;
                if (x < 0) {
                    x++;
                    cout << "Already at top cannot go further." << endl;
                    continue;
                }
                while (!redoStack.empty()) {
                    redoStack.pop();
                }
                undoStack.push(target);
                currPos(x, y);
                break;
            case 2: // down
                x++;
                if (x > n) {
                    x--;
                    cout << "Already at bottom cannot go downwards." << endl;
                    continue;
                }
                while (!redoStack.empty()) {
                    redoStack.pop();
                }
                undoStack.push(target);
                currPos(x, y);
                break;
            case 3: // left
                y--;
                if (y < 0) {
                    y++;
                    cout << "Already at far left cannot go further." << endl;
                    continue;
                }
                while (!redoStack.empty()) {
                    redoStack.pop();
                }
                undoStack.push(target);
                currPos(x, y);
                break;
            case 4: // right
                y++;
                if (y > n) {
                    y--;
                    cout << "Already at far right cannot go further." << endl;
                    continue;
                }
                while (!redoStack.empty()) {
                    redoStack.pop();
                }
                undoStack.push(target);
                currPos(x, y);
                break;
            case 5:
                currPos(x, y);

            case 6:
                // undo operation.
                if (undoStack.empty()) {
                    cout << "No Prev History to undo" << endl;
                    continue;
                }
                else if (undoStack.top() == 1) {
                    x++;
                    currPos(x, y);
                    redoStack.push(undoStack.top());
                    undoStack.pop();
                    continue;
                }
                else if (undoStack.top() == 2) {
                    x--;
                    currPos(x, y);
                    redoStack.push(undoStack.top());
                    undoStack.pop();
                    continue;
                }
                else if (undoStack.top() == 3) {
                    y++;
                    currPos(x, y);
                    redoStack.push(undoStack.top());
                    undoStack.pop();
                    continue;
                }
                else if (undoStack.top() == 4) {
                    y--;
                    currPos(x, y);
                    redoStack.push(undoStack.top());
                    undoStack.pop();
                    continue;
                }

            case 7:
                // redo operation. needs to be done only after undo.
                // check if undo stack is empty or not
                if (redoStack.empty()) {
                    cout << "can't redo" << endl;
                    continue;
                }
                else if (redoStack.top() == 1) {
                    x--;
                    currPos(x, y);
                    undoStack.push(redoStack.top());
                    redoStack.pop();
                    continue;
                }
                else if (redoStack.top() == 2) {
                    x++;
                    currPos(x, y);
                    undoStack.push(redoStack.top());
                    redoStack.pop();
                    continue;
                }
                else if (redoStack.top() == 3) {
                    y--;
                    currPos(x, y);
                    undoStack.push(redoStack.top());
                    redoStack.pop();
                    continue;
                }
                else if (redoStack.top() == 4) {
                    y++;
                    currPos(x, y);
                    undoStack.push(redoStack.top());
                    redoStack.pop();
                    continue;
                }
            }
        }
    }
}