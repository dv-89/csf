#include <string>
#include "Folder.hpp"

using namespace std;

class Folder;

class File{
    public:
    string name;
    string content;

    File(string name){
        this->name = name;
    }

    File(string content , string name){
        this->content = content;
        this->name = name;
    }
    
};
