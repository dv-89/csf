#include <algorithm>
#include <iostream>
#include <map>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

class Folder;

class File {
public:
  string name;
  string content;

  Folder *parent;
  File(string name) { this->name = name; }
  File(string content, string name) {
    this->content = content;
    this->name = name;
  }
};

class Folder {
public:
  string name;
  Folder *parentFolder;
  Folder(string name, Folder *parentFolder = nullptr) {
    this->parentFolder = parentFolder;
    this->name = name;
  }

  vector<Folder *> subFolderList;
  vector<File *> fileList;

  void addSubFolder(Folder *folder) { subFolderList.push_back(folder); }

  void removeSubFolder(Folder *folder) {
    for (int i = 0; i < subFolderList.size(); i++) {
      if (subFolderList[i] == folder) {
        subFolderList.erase(subFolderList.begin() + i);
        return;
      }
    }
  }

  void addFile(File *file) { fileList.push_back(file); }

  void removeFile(File *file) {
    for (int i = 0; i < fileList.size(); i++) {
      if (fileList[i] == file) {
        fileList.erase(fileList.begin() + i);
        return;
      }
    }
  }

  void display() {
    cout << "Folder: " << name << endl;
    for (Folder *folder : subFolderList) {
      cout << "- " << folder->name << " (folder)" << endl;
    }
    for (File *file : fileList) {
      cout << "- " << file->name << " (file)" << endl;
    }
  }

  void displayGood(int space = 0) {
    for (int i = 0; i < space; i++) {
      cout << "  ";
    }
    cout << "- " << name << " (folder)" << endl;
    for (Folder *folder : subFolderList) {
      folder->displayGood(space + 1);
    }
    for (File *file : fileList) {
      for (int i = 0; i < space + 1; i++) {
        cout << "  ";
      }
      cout << "- " << file->name << " (file)" << endl;
    }
  }
};

class FileSystem {
public:
  vector<Folder *> rootFolders;

  vector<string> tokenizePath(string path) {
    // store each folder in the path, in path_folders.
    vector<string> path_folders;

    // use stringstream to seperate based on delimiter '\'
    stringstream path_ss(path);
    string path_part;

    while (getline(path_ss, path_part, '\\')) {
      path_folders.push_back(path_part);
    }
    return path_folders;
  }

  void mkdir(string path) {

    Folder *currentFolder = nullptr;
    // convert path to vector of strings(folders).
    vector<string> tokens = tokenizePath(path);

    for (Folder *folder : rootFolders) {
      // check if the first folder is available in list of rootFolders.
      // if found set the current folder to the folder found in root
      // folder.(which is first folder of path.)
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }
    // if the folder is not present in rootfolders, then create a new one and
    // add it to root folders.
    if (!currentFolder) {
      currentFolder = new Folder(tokens[0]);
      cout << "Folder " << tokens[0] << " is not available in root. ";
      rootFolders.push_back(currentFolder);
      cout << tokens[0] << " created successfully." << endl;
    }

    // check if the next folder in the path is available, if not create it.
    for (int i = 1; i < tokens.size(); i++) {
      Folder *subFolder = nullptr;
      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          if (i == tokens.size() - 1) {
            cout << "Folder already exists" << endl;
          }
          break;
        }
      }
      if (!subFolder) {

        cout << tokens[i] << " is not available in " << currentFolder->name
             << ". ";

        subFolder = new Folder(tokens[i], currentFolder);

        currentFolder->addSubFolder(subFolder);

        cout << tokens[i] << " created successfully in " << currentFolder->name
             << endl;
      }
      currentFolder = subFolder;
    }
  }

  void rmdir(string path) {

    Folder *currentFolder = nullptr;

    // split the path into folders.
    vector<string> tokens = tokenizePath(path);

    int no_of_folders = tokens.size();

    // i is to keep track of the position to erase in the rootFolders or
    // subFolderList
    int i = -1;
    for (Folder *folder : rootFolders) {
      i++;
      // check if the folder is available in root folders.
      if (folder->name == tokens[0]) {
        cout << tokens[0] << " exists" << endl;
        currentFolder = folder;
        if (no_of_folders == 1) {
          // remove folder from root folders.
          rootFolders.erase(rootFolders.begin() + i);
        }
        break;
      }
    }
    // if the folder is not present in rootfolders, then print folder not
    // available.
    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " doesn't exist" << endl;
      return;
    }

    for (int i = 1; i < tokens.size(); i++) {
      Folder *subFolder = nullptr;
      int j = -1;
      for (Folder *folder : currentFolder->subFolderList) {
        j++;
        if (folder->name == tokens[i]) {
          cout << tokens[i] << " exists" << endl;
          subFolder = folder;
          if (i == no_of_folders - 1) {
            // remove it from list.
            currentFolder->subFolderList.erase(
                currentFolder->subFolderList.begin() + j);
            cout << "Folder removed" << endl;
          }
          break;
        }
      }

      if (!subFolder) {
        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }

      currentFolder = subFolder;
    }
  }

  void mkfile(string path, string filename) {

    Folder *currentFolder = nullptr;

    vector<string> tokens = tokenizePath(path);

    for (Folder *folder : rootFolders) {
      // check if the folder is available in root folders.
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }
    // if the folder is not present, then print not available.
    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " is not available in root." << endl;
      return;
    }

    for (int i = 1; i <= tokens.size(); i++) {

      Folder *subFolder = nullptr;

      // if currentfolder is last folder, then create a file.
      if (i == tokens.size()) {
        //  cout << "name of currentfolder is = " << currentFolder->name <<
        //  endl;
        // create new file.
        for (File *file : currentFolder->fileList) {
          if (file->name == filename) {
            cout << "File already exists" << endl;
            return;
          }
        }
        File *newFile = new File(filename);
        currentFolder->addFile(newFile);
        cout << "File added" << endl;
        return;
      }

      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          break;
        }
      }

      // if subfolder is not available, print not available.
      if (!subFolder) {
        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }
      currentFolder = subFolder;
    }
  }

  void rmfile(string path) {
    Folder *currentFolder = nullptr;
    // File* newFile = nullptr;
    vector<string> tokens = tokenizePath(path);
    string filename = tokens[tokens.size() - 1];

    for (Folder *folder : rootFolders) {
      // check if the folder is available in root folders.
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }
    // if the folder is not present in rootfolders, then create a new one and
    // add it to root folders.
    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " is not available in root." << endl;
      return;
    }

    for (int i = 1; i < tokens.size(); i++) {
      Folder *subFolder = nullptr;
      // if currentfolder is last folder, then create a file.

      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          break;
        }
      }

      if (i + 1 == tokens.size()) {
        cout << "name of currentfolder is = " << currentFolder->name << endl;
        // check if the file is available.
        int j = -1;
        for (File *file : currentFolder->fileList) {
          j++;
          if (file->name == filename) {
            // remove file.
            currentFolder->fileList.erase(currentFolder->fileList.begin() + j);
            cout << "File removed " << endl;
          }
        }
        return;
      }

      if (!subFolder) {

        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }
      currentFolder = subFolder;
    }
  }

  void edfile(string path, string content) {

    Folder *currentFolder = nullptr;

    vector<string> tokens = tokenizePath(path);
    string filename = tokens[tokens.size() - 1];

    for (Folder *folder : rootFolders) {
      // check if the folder is available in root folders.
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }

    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " is not available in root." << endl;
      return;
    }

    for (int i = 1; i < tokens.size(); i++) {

      Folder *subFolder = nullptr;
      // if currentfolder is last folder, then create a file.

      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          break;
        }
      }

      if (i == tokens.size() - 1) {
        // cout << "name of currentfolder is = " << currentFolder->name << endl;
        //  check if the file is available.
        int j = -1;
        for (File *file : currentFolder->fileList) {
          j++;
          if (file->name == filename) {
            file->content = content;
            return;
          }
        }
        return;
      }

      // if subfolder is not available, then print not available and return.
      if (!subFolder) {
        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }
      currentFolder = subFolder;
    }
  }

  void dispfile(string path) {
    Folder *currentFolder = nullptr;

    vector<string> tokens = tokenizePath(path);
    string filename = tokens[tokens.size() - 1];

    for (Folder *folder : rootFolders) {
      // check if the folder is available in root folders.
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }

    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " is not available in root." << endl;
      return;
    }

    for (int i = 1; i < tokens.size(); i++) {
      Folder *subFolder = nullptr;
      // if currentfolder is last folder, then create a file.

      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          break;
        }
      }

      if (i == tokens.size() - 1) {
        cout << "name of currentfolder is = " << currentFolder->name << endl;
        // check if the file is available.

        for (File *file : currentFolder->fileList) {

          if (file->name == filename) {
            cout << file->name << " contains : " << file->content << endl;
            return;
          }
        }
        return;
      }

      if (!subFolder) {

        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }
      currentFolder = subFolder;
    }
  }

  void dispdir(string path) {
    // 1st level of content.
    // just print what  is available in this folder.
    Folder *currentFolder = nullptr;

    vector<string> tokens = tokenizePath(path);

    if (tokens.size() == 1) {
      for (Folder *folder : rootFolders) {
        if (folder->name == tokens[0]) {
          currentFolder = folder;
          break;
        }
      }
      if (!currentFolder) {
        cout << "Folder " << tokens[0] << " is not availanle in root." << endl;
        return;
      }
      // print this folder's list.
      cout << "Folders : ";
      for (Folder *folder : currentFolder->subFolderList) {
        cout << folder->name << " ";
      }
      cout << endl << "Files : ";
      for (File *file : currentFolder->fileList) {
        cout << file->name << " ";
      }
      cout << endl;
      return;
    }

    for (Folder *folder : rootFolders) {
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }

    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " is not availanle in root." << endl;
      return;
    }

    for (int i = 1; i < tokens.size(); i++) {
      Folder *subFolder = nullptr;

      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          break;
        }
      }

      if (i + 1 == tokens.size()) {
        // print this folder's list.
        cout << "Folders : ";
        for (Folder *folder : subFolder->subFolderList) {
          cout << folder->name << " ";
        }
        cout << endl << "Files : ";
        for (File *file : subFolder->fileList) {
          cout << file->name << " ";
        }
        cout << endl;
        return;
      }

      if (!subFolder) {
        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }
      currentFolder = subFolder;
    }
  }

  void dispdir_r(string path) {
    // Split the path into its component parts.
    vector<string> tokens = tokenizePath(path);

    // Find the root folder object.
    Folder *currentFolder = nullptr;
    for (Folder *folder : rootFolders) {
      if (folder->name == tokens[0]) {
        currentFolder = folder;
        break;
      }
    }

    // If the root folder doesn't exist, print an error message and return.
    if (!currentFolder) {
      cout << "Folder " << tokens[0] << " is not available in root." << endl;
      return;
    }

    // Navigate down the folder hierarchy to the specified subfolder.
    for (int i = 1; i < tokens.size(); i++) {
      Folder *subFolder = nullptr;
      for (Folder *folder : currentFolder->subFolderList) {
        if (folder->name == tokens[i]) {
          subFolder = folder;
          break;
        }
      }
      if (!subFolder) {
        cout << tokens[i] << " is not available in " << currentFolder->name
             << endl;
        return;
      }
      currentFolder = subFolder;
    }

    // Print out the contents of the specified folder.
    print(currentFolder);
  }
  void print(Folder *folder) {
    // Print out the files in the current folder.
    for (File *file : folder->fileList) {
      cout << file->name << " (file)" << endl;
    }
    for (Folder *nfolder : folder->subFolderList) {
      cout << nfolder->name << " (folder)" << endl;
    }

    // Recursively print out the contents of all subfolders.
    for (Folder *subFolder : folder->subFolderList) {
      print(subFolder);
    }
  }
};

int main() {

  string myline;

  FileSystem fs;
  while (true) {
    cout << "Enter command (type help for list of commands) :";
    getline(cin, myline);

    string command, path, filename;
    string check;

    istringstream ss(myline);
    ss >> command;
    if (command == "dispdir") {
      // check if -r exists. and store it if available.
      ss >> check;
      if (check == "-r") {
        ss >> path >> filename;
        fs.dispdir_r(path);
        continue;
      } else {
        path = check;
        ss >> filename;
      }
      // cout << "path = " << path << endl;
      // cout << "check = " << check << endl;
      // cout << "filename " << filename <<endl;
      fs.dispdir(path);
      continue;
    }
    if (command != "dispdir") {
      ss >> path >> filename;
    }

    // cout << "word1 is " << command << endl;
    // cout << "word2 is " << path << endl;
    // cout << "word3 is " << filename << endl;

    if (command == "mkdir") {
      if (filename != "") {
        cout << "invalid command" << endl;
        continue;
      }
      fs.mkdir(path);
    } else if (command == "display") {
      if (filename != "" && path != "") {
        cout << "invalid command" << endl;
        continue;
      }
      vector<Folder *> root = fs.rootFolders;
      for (Folder *folder : fs.rootFolders) {
        folder->displayGood();
      }

    } else if (command == "rmdir") {
      if (filename != "") {
        cout << "invalid command" << endl;
        continue;
      }
      fs.rmdir(path);
    } else if (command == "mkfile") {
      if (filename == "") {
        cout << "Need to enter filename" << endl;
        continue;
      }
      fs.mkfile(path, filename);
    } else if (command == "rmfile") {
      if (filename != "") {
        cout << "invalid command" << endl;
        continue;
      }
      fs.rmfile(path);
    } else if (command == "edfile") {
      if (filename == "") {
        cout << "need content" << endl;
        continue;
      }
      fs.edfile(path, filename);
    } else if (command == "dispfile") {
      fs.dispfile(path);
    } else if (command == "help") {
      cout << "command list available are : " << endl;
      cout << "mkdir" << endl;
      cout << "rmdir" << endl;
      cout << "mkfile" << endl;
      cout << "rmfile" << endl;
      cout << "edfile" << endl;
      cout << "dispdir" << endl;
      cout << "dispdir -r" << endl;
      cout << "q to quit" << endl;
      cout << "display (for good view )" << endl;
      continue;
    } else if (command == "q") {
      break;
    } else {
      cout << "invalid command" << endl;
      continue;
    }
  }

  return 0;
}
