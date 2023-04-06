#ifndef folder_h
#define folder_h

#include <string>
#include <vector>
#include "File.hpp"

class File;

class Folder{
    public:
        std::string name;
        Folder* parentFolder;

        Folder(std::string name, Folder* parentFolder = nullptr);

        std::vector<Folder*> subFolderList;
        std::vector<File*> fileList;

        void addSubFolder(Folder* folder);
        void removeSubFolder(Folder* folder);
        void addFile(File* file);
        void removeFile(File* file);
        void display();
        void displayRecursive(int depth=0);

};

#endif // folder_h
