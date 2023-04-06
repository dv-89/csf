#include <iostream>
#include <vector>
#include <queue>

using namespace std;

// class Node{
//     public:
//     int value;
//     vector<Node*> NodePointers;
// };

int main(){
    //graph adjaceny list
    const int v = 10;
    vector<int> adj[v];
    
    adj[1].push_back(2);
    adj[1].push_back(5);
    adj[2].push_back(1);
    adj[2].push_back(5);
    adj[2].push_back(4);
    adj[2].push_back(3);
    adj[3].push_back(2);
    adj[3].push_back(4);
    adj[4].push_back(2);
    adj[4].push_back(3);
    adj[4].push_back(5);
    adj[5].push_back(1);
    adj[5].push_back(2);
    adj[5].push_back(4);

    //breadth first search.

    queue<int> q;
    q.push(1);
    while(!q.empty()){
        cout << q.front() << " ";
        q
    }
}