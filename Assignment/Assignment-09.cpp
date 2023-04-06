#include <iostream>
#include <queue>
#include <sstream>
#include <string>
using namespace std;

class Node {
public:
  int val;
  Node *left;
  Node *right;

  Node(int value) {
    val = value;
    left = nullptr;
    right = nullptr;
  }
};

class BinarySearchTree {
public:
  Node *root;

  BinarySearchTree() { root = nullptr; }

  void insert(int value) {
    Node *newNode = new Node(value);
    if (root == nullptr) {
      root = newNode;
      return;
    }

    Node *currentNode = root;
    while (true) {
      if (value <= currentNode->val) {
        if (currentNode->left == nullptr) {
          currentNode->left = newNode;
          return;
        }
        currentNode = currentNode->left;
      } else {
        if (currentNode->right == nullptr) {
          currentNode->right = newNode;
          return;
        }
        currentNode = currentNode->right;
      }
    }
  }

  int contains(int value) {
    Node *currentNode = root;
    if (root == nullptr) {
      cout << "Node not inserted" << endl;
      return 2;
    }
    while (currentNode != nullptr) {
      if (value == currentNode->val) {
        return 1;
      } else if (value < currentNode->val) {
        currentNode = currentNode->left;
      } else {
        currentNode = currentNode->right;
      }
    }
    return 0;
  }

  // can't send root  as argument from main
  void remove(int value) { root = removeNode(root, value); }

  Node *removeNode(Node *node, int value) {
    if (node == nullptr) {
      return nullptr;
    }
    if (value == node->val) {
      // if left and right child are not available, just delete it.
      if (node->left == nullptr && node->right == nullptr) {
        delete node;
        return nullptr;
      }
      if (node->left == nullptr) {
        // if right child is available, delete node and return pointer to right.
        Node *temp = node->right;
        delete node;
        return temp;
      }
      if (node->right == nullptr) {
        // if left child is available, delete node and return pointer to left.
        Node *temp = node->left;
        delete node;
        return temp;
      }
      // if both left and right child are available.
      //  we can also find predecessor, which is in left subtree.
      //  but here we consider successor, which is in right subtree.
      Node *successor = findSuccessor(node->right);
      node->val = successor->val;
      node->right = removeNode(node->right, successor->val);
    } else if (value < node->val) {
      // if value is less than node value, go to left node and check.
      node->left = removeNode(node->left, value);
    } else {
      // if value is greter than node value, go to right node and check.
      node->right = removeNode(node->right, value);
    }
    return node;
  }

  Node *findSuccessor(Node *node) {
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  void printBFS() {
    // level order traversal
    if (root == nullptr) {
      cout << "Node not inserted" << endl;
      return;
    }
    cout << "Level order : ";
    queue<Node *> myq;
    myq.push(root);
    while (!myq.empty()) {
      cout << myq.front()->val << " ";
      if (myq.front()->left != nullptr) {
        myq.push(myq.front()->left);
      }
      if (myq.front()->right != nullptr) {
        myq.push(myq.front()->right);
      }

      myq.pop();
    }
    cout << endl;
    return;
  }

  // can't send root from main.
  void printIO() {
    if (root == nullptr) {
      cout << "Empty Tree, insert nodes" << endl;
      return;
    }
    cout << "Inorder : ";

    printInOrder(root);
    cout << endl;
  }

  void printInOrder(Node *node) {
    // left root right
    if (node != nullptr) {
      printInOrder(node->left);
      cout << node->val << " ";
      printInOrder(node->right);
    }
  }
};

int main() {
  BinarySearchTree bst;

  cout << "commands available are insert, remove, print(inorder), "
          "printbfs(level order), find, q (quit)"
       << endl;

  while (true) {
    string s;
    cout << "Enter command (q to quit) : ";
    cin.clear();
    getline(cin, s);

    istringstream ss(s);
    string word1, word2;
    ss >> word1 >> word2;

    int target = 0;

    if (word1 == "q" || word1 == "Q") {
      if (word2 != "") {
        cout << "invalid command" << endl;
        continue;
      }
      break;
    } else if (word1 == "insert") {
      // insert
      if (word2 == "") {
        cout << "invalid command" << endl;
        continue;
      }
      bst.insert(stoi(word2));
      bst.printIO();
      continue;
    } else if (word1 == "remove") {
      // remove
      if (word2 == "") {
        cout << "invalid command" << endl;
        continue;
      }
      int c = bst.contains(stoi(word2));
      if (c == 1) {
        bst.remove(stoi(word2));
        bst.printIO();
        continue;
      } else if (c == 0) {
        cout << "not found" << endl;
        continue;
      }

    } else if (word1 == "print") {
      if (word2 != "") {
        cout << "invalid command" << endl;
        continue;
      }
      // print
      bst.printIO();
      continue;
    } else if (word1 == "find") {
      // find
      if (word2 == "") {
        cout << "invalid command" << endl;
        continue;
      }
      int b = bst.contains(stoi(word2));
      if (b == 2) {

        continue;
      }
      if (b == 1) {
        cout << "found" << endl;
      } else if (b == 0) {
        cout << "not found" << endl;
      }
      continue;
    } else if (word1 == "printbfs") {
      if (word2 != "") {
        cout << "invalid command" << endl;
        continue;
      }
      // printbfs
      bst.printBFS();
      continue;
    } else {
      cout << "invalid command" << endl;
      continue;
    }
  }
}
