#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main(){
	std::ifstream myfile;
	myfile.open("input.txt");
	
	// we can also do that using single line using class constructor.
	//ifstream myfile ("input.txt");
	
	//declare a string variable to hold the content of file.
	
	string mystring;
	
	//read using >> operator;
	
	if(myfile.is_open()){
		myfile >> mystring;
		cout << mystring;
	}
}