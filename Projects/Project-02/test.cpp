#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>
#include <algorithm>
#include "File.hpp"
#include "Folder.hpp"

using namespace std;

class FileSystem{
    public:
    vector<Folder*> rootFolders;

    vector<string> tokenizePath(string path){
        //store each folder in the path, in path_folders.
        vector<string> path_folders;

        //use stringstream to seperate based on delimiter '\'
        stringstream path_ss(path);
        string path_part;
        
        while (getline(path_ss, path_part, '\\')) {
            path_folders.push_back(path_part);
        }
        return path_folders;
    }
    
    void mkdir(string path){

        Folder* currentFolder = nullptr;
        // convert path to vector of strings(folders).
        vector<string> tokens = tokenizePath(path);
        
        
        for(Folder* folder : rootFolders){
            // check if the first folder is available in list of rootFolders.
            //if found set the current folder to the folder found in root folder.(which is first folder of path.)
            if(folder->name == tokens[0]){
                currentFolder = folder;
                break;
            }
        }
        // if the folder is not present in rootfolders, then create a new one and add it to root folders.
        if(!currentFolder){
            currentFolder = new Folder(tokens[0]);
            cout << "Folder " << tokens[0] << " is not available in root. ";
            rootFolders.push_back(currentFolder);
            cout << tokens[0] << " created successfully." << endl;
        }
        
        //check if the next folder in the path is available, if not create it.
        for (int i = 1; i < tokens.size(); i++) {
            Folder* subFolder = nullptr;
            for (Folder* folder : currentFolder->subFolderList) {
                if (folder->name == tokens[i]) {
                    subFolder = folder;
                    if(i==tokens.size()-1){
                        cout << "Folder already exists" << endl;
                    }
                    break;
                }
            }
            if (!subFolder) {
            
            cout << tokens[i] << " is not available in " << currentFolder->name << ". ";
            
            subFolder = new Folder(tokens[i], currentFolder);
            
            currentFolder->addSubFolder(subFolder);

            cout << tokens[i] << " created successfully in " << currentFolder->name << endl;

            }
            currentFolder = subFolder;
        }

    }

    void rmdir(string path){

        Folder* currentFolder = nullptr;
        
        //split the path into folders.
        vector<string> tokens = tokenizePath(path);

        int no_of_folders = tokens.size();

        // i is to keep track of the position to erase in the rootFolders or subFolderList
        int i=-1;
        for(Folder* folder : rootFolders){
            i++;
            // check if the folder is available in root folders.
            if(folder->name == tokens[0]){
                cout << tokens[0] << " exists" << endl;
                currentFolder = folder;
                if(no_of_folders == 1){
                    //remove folder from root folders.
                    rootFolders.erase(rootFolders.begin()+i);
                }
                break;
            }
        }
        // if the folder is not present in rootfolders, then print folder not available.
        if(!currentFolder){
            cout << "Folder " << tokens[0] << " doesn't exist" << endl;
            return;
        }

        for (int i = 1; i < tokens.size(); i++) {
            Folder* subFolder = nullptr;
            int j=-1;
            for (Folder* folder : currentFolder->subFolderList) {
                j++;
                if (folder->name == tokens[i]) {
                    cout << tokens[i] << " exists" << endl;
                    subFolder = folder;
                    if(i==no_of_folders-1){
                        //remove it from list.
                        currentFolder->subFolderList.erase(currentFolder->subFolderList.begin() + j);
                        cout << "Folder removed" << endl;
                    }
                    break;
                }
            }

            if (!subFolder) {
            cout << tokens[i] << " is not available in " << currentFolder->name << endl;
            return;
            }
            
            currentFolder = subFolder;
        }
       
        
    }

    void mkfile(string path, string filename){
        
        Folder* currentFolder = nullptr;
        
        vector<string> tokens = tokenizePath(path);
          
        for(Folder* folder : rootFolders){
            // check if the folder is available in root folders.
            if(folder->name == tokens[0]){
                currentFolder = folder;
                break;
            }
        }
        // if the folder is not present, then print not available.
        if(!currentFolder){
            cout << "Folder " << tokens[0] << " is not available in root." << endl;
            return;
        }
        
        for (int i = 1; i <= tokens.size(); i++) {
            
            Folder* subFolder = nullptr;
            
            //if currentfolder is last folder, then create a file.
            if(i==tokens.size()){
                cout << "name of currentfolder is = " << currentFolder->name << endl;
                //create new file.
                File* newFile = new File(filename);
                currentFolder->addFile(newFile);
                cout << "File added" << endl;
                return;
            }

            for (Folder* folder : currentFolder->subFolderList) {
                if (folder->name == tokens[i]) {
                    subFolder = folder;
                    break;
                }
            }
            // if subfolder is not available, print not available.
            if (!subFolder) {
            cout << tokens[i] << " is not available in " << currentFolder->name << endl;
            return;
            }
            currentFolder = subFolder;
        }
    }

    void rmfile(string path){
        Folder* currentFolder = nullptr;
        //File* newFile = nullptr;
        vector<string> tokens = tokenizePath(path);
        string filename = tokens[tokens.size()-1];
        
        for(Folder* folder : rootFolders){
            // check if the folder is available in root folders.
            if(folder->name == tokens[0]){
                currentFolder = folder;
                break;
            }
        }
        // if the folder is not present in rootfolders, then create a new one and add it to root folders.
        if(!currentFolder){
            cout << "Folder " << tokens[0] << " is not available in root." << endl;
            return;
        }
        
        for (int i = 1; i <= tokens.size(); i++) {
            Folder* subFolder = nullptr;
            //if currentfolder is last folder, then create a file.

            if(i==tokens.size()){
                cout << "name of currentfolder is = " << currentFolder->name << endl;
                //check if the file is available.
                int j = -1;
                for(File* file : currentFolder->fileList){
                    j++;
                    if(file->name == filename){
                        //remove file.
                        currentFolder->fileList.erase(currentFolder->fileList.begin() + j);
                        cout << "File removed " << endl;
                    }
                }
                return;
            }

            for (Folder* folder : currentFolder->subFolderList) {
                if (folder->name == tokens[i]) {
                    subFolder = folder;
                    break;
                }
            }
            if (!subFolder) {
            
            cout << tokens[i] << " is not available in " << currentFolder->name << endl;
            return;
            }
            currentFolder = subFolder;
        }
    }

    void edfile(string path, string content){
        
        Folder* currentFolder = nullptr;
    
        vector<string> tokens = tokenizePath(path);
        string filename = tokens[tokens.size()-1];
        
        for(Folder* folder : rootFolders){
            // check if the folder is available in root folders.
            if(folder->name == tokens[0]){
                currentFolder = folder;
                break;
            } 
        }
        
        
        if(!currentFolder){
            cout << "Folder " << tokens[0] << " is not available in root." << endl;
            return;
        }
        
        for (int i = 1; i < tokens.size(); i++) {

            Folder* subFolder = nullptr;
            //if currentfolder is last folder, then create a file.

            if(i==tokens.size()-1){
                cout << "name of currentfolder is = " << currentFolder->name << endl;
                //check if the file is available.
                int j = -1;
                for(File* file : currentFolder->fileList){
                    j++;
                    if(file->name == filename){
                        file->content = content;
                        return;
                    }
                }
                return;
            }

            for (Folder* folder : currentFolder->subFolderList) {
                if (folder->name == tokens[i]) {
                    subFolder = folder;
                    break;
                }
            }
            // if subfolder is not available, then print not available and return.
            if (!subFolder) {
            cout << tokens[i] << " is not available in " << currentFolder->name << endl;
            return;
            }
            currentFolder = subFolder;
        } 
    }

    void dispfile(string path){
        Folder* currentFolder = nullptr;
    
        vector<string> tokens = tokenizePath(path);
        string filename = tokens[tokens.size()-1];
        
        for(Folder* folder : rootFolders){
            // check if the folder is available in root folders.
            if(folder->name == tokens[0]){
                currentFolder = folder;
                break;
            } 
        }
        
        
        if(!currentFolder){
            cout << "Folder " << tokens[0] << " is not available in root." << endl;
            return;
        }
        
        for (int i = 1; i < tokens.size(); i++) {
            Folder* subFolder = nullptr;
            //if currentfolder is last folder, then create a file.

            if(i==tokens.size()-1){
                cout << "name of currentfolder is = " << currentFolder->name << endl;
                //check if the file is available.
               
                for(File* file : currentFolder->fileList){
                    
                    if(file->name == filename){
                        cout << file->name << " contains : " << file->content << endl;
                        return;
                    }
                }
                return;
            }

            for (Folder* folder : currentFolder->subFolderList) {
                if (folder->name == tokens[i]) {
                    subFolder = folder;
                    break;
                }
            }
            if (!subFolder) {
            
            cout << tokens[i] << " is not available in " << currentFolder->name << endl;
            return;
            }
            currentFolder = subFolder;
        }
    }

    
    
};


int main(){

    string myline;

    FileSystem fs;
    while(true){
        cout << "Enter operation: ";
        getline(cin, myline);

        string command, path, filename;
        string check;

        istringstream ss(myline);
        ss >> command;
        if(command == " dispdir"){
            // check if -r exists. and store it if available.
        }

        ss >> path >> filename;

        // cout << "word1 is " << command << endl;
        // cout << "word2 is " << path << endl;
        // cout << "word3 is " << filename << endl;

        if(command == "mkdir"){
            if(filename != ""){
                cout << "invalid command" << endl;
                continue;
            }
        fs.mkdir(path);
        } else if(command == "display"){
            if(filename != "" && path != ""){
                cout << "invalid command" << endl;
                continue;
            }
            vector< Folder*> root = fs.rootFolders;
            for (Folder* folder : fs.rootFolders) {
                    folder->displayRecursive();
            }
           
        } else if(command == "rmdir"){
            if(filename != ""){
                cout << "invalid command" << endl;
                continue;
            }
            fs.rmdir(path);
        } else if (command == "mkfile"){
            if(filename == ""){
                cout << "Need to enter filename" << endl;
                continue;
            }
            fs.mkfile(path, filename);
        } else if (command == "rmfile"){
            if(filename != ""){
                cout << "invalid command" << endl;
                continue;
            }
            fs.rmfile(path);
        } else if (command == "edfile"){
            if(filename != ""){
                cout << "need content" << endl;
                continue;
            }
            fs.edfile(path, filename);
        } else if(command == "dispfile"){
            fs.dispfile(path);
        }
    } 

       return 0; 
    }
 