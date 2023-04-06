#include <iostream>
#include <string>
#include <sstream>
using namespace std;

class Node{
    public:
    int value;
    Node* next;

    Node(int val){
        value = val;
        next = nullptr;
    }
};

class LinkedList{
    Node* root;
    public:
    LinkedList(){
        root = nullptr;
    }
    void insert(int value){
        Node* newNode = new Node(value);
        if(root == nullptr){
            root = newNode;
            cout << "inserted" << endl;
            return;
        }

        
        Node* temp = root;
        while(temp-> next != nullptr){
            temp = temp->next;
        }
        temp->next = newNode;
        cout << "inserted" << endl;
        return;
    
        
    }

    void remove(int value){
        if(root == nullptr){
            cout << "Node not available" << endl;
            return;
        }
        if(root->value == value){
            root = root->next;
            return;
        }
    
        Node* temp = root;
        Node* prev = nullptr;
        while(temp->value != value && temp != nullptr){
            prev = temp;
            temp = temp->next;
        }
        if(temp == nullptr){
            cout << "Node not available" << endl;
            return;
        }
        prev->next = temp->next;
        delete(temp);
        return;
    
    }
    
    void print(){
        if(root == NULL){
            cout << "Insert nodes before printing list" << endl;
            return;
        }
        
        Node* temp = root;
        cout << "Elements are = " ;
        while(temp != nullptr){
            cout << temp->value << " ";
            temp = temp->next;
        }
        cout << endl;
        return;
    }
};

int main(){
    LinkedList ll;
    string s;
    int num;
    while(true){
        cout << "Enter command (q to quit): ";
        
        getline(cin,s);
         
        istringstream ss(s);
        string word1, word2;
        ss >> word1 >> word2;
        if(word2 != ""){
            num = stoi(word2);
        }
        
        
        if(word1 == "insert"){
            ll.insert(num);
            ll.print();
            continue;
        } else if(word1 == "remove"){
            ll.remove(num);
            continue;
        } else if (word1 == "print"){
            ll.print();
            continue;
        } else if(word1 == "q"){
            break;
        }
    }
}