#ifndef FILE_HPP
#define FILE_HPP

#include <string>

// Forward declaration of Folder class
class Folder;

class File {
public:
    std::string name;
    std::string content;

    // Constructor declaration
    File(std::string name);
    File(std::string content, std::string name);

};

#endif // FILE_HPP
