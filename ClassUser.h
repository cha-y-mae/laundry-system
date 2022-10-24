
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std; 

#ifndef ClassUser_h
#define ClassUser_h

// Class user to store user information:
// ------------------------------------//
//             Class user 
// ------------------------------------//

class user {    

private:
    string name;             // Student name
    string netid;            // Student Net ID
    string building;         // Student's building

public:

    // Default constructor

    user() {}

    // Non-default constructor

    user(string Name, string id, string build) {
        name = Name;
        netid = id;
        building = build;
  }

    // Getters 

    string getName() const { return name; }

    string getID() const { return netid; }

    string getBuilding() const { return building; }

    void print() const {
        cout << "    Name: " << this->name << endl;
        cout << "    netID: " << this->netid << endl;
        cout << "    Building: " << this->building << endl;
    }

};


#endif /* ClassUser_h */ 
