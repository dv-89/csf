#include <iostream>

using namespace std;

class Node{
    public:
    int value;
    Node* left;
    Node* right;
    Node(int val){
        value = val;
        left = nullptr;
        right = nullptr;
    }
};

class BST{
    Node* root;

    void insert(int value){
        Node* newNode = new Node(value);

        Node* currentNode = root;
        while(true){
            if(value <= currentNode->value ){
                if(currentNode->left == nullptr){
                    currentNode->left = newNode;
                    return;
                }
                currentNode = currentNode->left;
            }else{
                if(currentNode->right = nullptr){
                    currentNode->right = newNode;
                    return;
                }
                currentNode = currentNode->right;
            }
        }
    }

    bool contains(int value){
        Node* currentNode = root;
       while(currentNode != nullptr){
        if(currentNode->value == value){
            return true;
        } else if(value <= currentNode-> value){                
                currentNode = currentNode->left;
        } else{               
                currentNode = currentNode->right;
        }           
        }
        return false;
    }
    
};