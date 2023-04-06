#include <string>
#include <iostream>
#include <vector>
#include "File.hpp"
using namespace std;

class File;

class Folder{
    public:
    string name;
    Folder* parentFolder;
     
    Folder(string name, Folder* parentFolder = nullptr){
        this->parentFolder = parentFolder;
        this->name = name;
    }
    

    vector<Folder*> subFolderList;
    vector<File*> fileList;

    void addSubFolder(Folder* folder){
        subFolderList.push_back(folder);
    }
    
    void removeSubFolder(Folder* folder){
        for(int i=0; i< subFolderList.size(); i++){
            if(subFolderList[i] == folder){
                subFolderList.erase(subFolderList.begin()+i);
                return;
            }
        }
    }

    void addFile(File* file){
        fileList.push_back(file);
    }

    void removeFile(File* file){
        for(int i=0; i<fileList.size(); i++){
            if(fileList[i] == file){
                fileList.erase(fileList.begin() + i);
                return;
            }
        }
    }

    void display() {
        cout << "Folder: " << name << endl;
        for (Folder* folder : subFolderList) {
            cout << "- " << folder->name << " (folder)" << endl;
        }
        for (File* file : fileList) {
            cout << "- " << file->name << " (file)" << endl;
        }
    }

    void displayRecursive(int depth = 0) {
        for (int i = 0; i < depth; i++) {
            cout << "  ";
        }
        cout << "- " << name << " (folder)" << endl;
        for (Folder* folder : subFolderList) {
            folder->displayRecursive(depth + 1);
        }
        for (File* file : fileList) {
            for (int i = 0; i < depth + 1; i++) {
                cout << "  ";
            }
            cout << "- " << file->name << " (file)" << endl;
        }
    }

};
