#include <iostream>

using namespace std;

// creating a struct of mailing address

//structtag is optional while creating struct, 
//but needs to be initialized at the same time while creating it.

// each element in an array of structures in called record.

// defining structures as strcture members.

// a union is similar to a structure, but unlike a structure,
//only one member of union can be used at any one time.
//this is because a union reserves the same area of memory for each data member.

struct mailingaddress{
    string name;
    string streetAddress;
    string city;
    string state;
    int zipcode;
};

void printstruct(mailingaddress ma){
    cout << endl << "name : " << ma.name << endl;
    cout << "street address : " << ma.streetAddress << endl;
    cout << "city : " << ma.city << endl;
    cout << "state : " << ma.state << endl;
    cout << "zipcode : " << ma.zipcode << endl;
}

void ptrprintstruct(mailingaddress *mas){
    //when you send a pointer to structure, 
    //you must use a pointer to member operator (->) to access struct members.
    cout << endl << "name : " << mas->name << endl;
    cout << "street address : " << mas->streetAddress << endl;
    cout << "city : " << mas->city << endl;
    cout << "state : " << mas->state << endl;
    cout << "zipcode : " << mas->zipcode << endl;
}
int main(){
    
    mailingaddress dinesh_address, keshav_address;

    //dinesh
    dinesh_address.city = "Rajahmundry";
    dinesh_address.zipcode = 533106;
    dinesh_address.name = "Dinesh";
    dinesh_address.state = "Andhra Pradesh";
    dinesh_address.streetAddress = "72-02-18/23, g1, parimala heights";

    //keshav
    keshav_address = {"Keshav", "Happy Homes",
     "Vishakapatnam","Andhra Pradesh", 12345
    };
    // keshav_address.city = "Vishakapatnam";
    // keshav_address.zipcode = 12345;
    // keshav_address.name = "Keshav";
    // keshav_address.state = "Andhra Pradesh";
    // keshav_address.streetAddress = "Happy Homes";
    printstruct(dinesh_address);
   // printstruct(keshav_address);
   ptrprintstruct(&keshav_address); // doesnt create a copy.
}

//here if the mailing address contains an array of whatever data it is.
//to send the record as argument to function, dirsctly is follish
//as it takes a lot of data to create a copy.
//so wwe nood to use pointers.
