
// OOP final project
// Time-sharing laundry system
// by Chaimae Abouzahir

#include "ClassUser.h"
#include "MachineSystem.h"
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

// function to check if user input start time is greater than or equal to real
// time
inline bool checkStartTime(int hour, int min, int sec) {

  std::time_t t = std::time(nullptr);
  std::tm *now = std::localtime(&t);

  if (hour < now->tm_hour) {
    return false; // set to free
  }
  if (hour == now->tm_hour) {
    if (min < now->tm_min) {
      return false;
    } else if (min == now->tm_min) {
      if (sec < now->tm_sec) {
        return false;
      }
    }
  }
  return true;
}

int main() {

  // Declaring the variables

  string name, id,
      building; // store user input to initialize object user from user class
  Cycle
      c; // Instance of class Cycle to use in class Time for endTime claculation
  char cycle_choice; // user choice of cycle
  char menu_choice;  // user choice in the diplayed menu
  char userchoice;   // user choice for strating another cycle (do-while loop)
  int hr, m, s;      // store user input for starting time
  int hprob, mprob,
      sprob;     // variables to store hour, minute, and second for report
  string idprob; // variable to store user id who reports a problem

  // Initialize a vector of objects Machine and of size 5

  vector<Machine *> vec;

  // intializing the machines

  Machine Machine1(1, false);
  Machine Machine2(2, false);
  Machine Machine3(3, false);
  Machine Machine4(4, false);
  Machine Machine5(5, false);

  vec.push_back(&Machine1);
  vec.push_back(&Machine2);
  vec.push_back(&Machine3);
  vec.push_back(&Machine4);
  vec.push_back(&Machine5);

  // generate data file where user and machine data will be printed
  fstream File;

  File.open("data.txt", ios::out);

  if (File.fail()) {
    cerr << "Error opening the file" << endl;
    exit(1);
  }

  cout << "**********************************************" << endl;

  cout << "Welcome to the Laundry Management System! " << endl;

  cout << "**********************************************" << endl;

  cout << "**********************************************" << endl;

  cout << "                 USER MENU                  " << endl;

  cout << "**********************************************" << endl;

  // swicth menu

  cout << "    a. Start new cycle " << endl;
  cout << "    b. Report problem" << endl;
  cout << "**********************************************" << endl;
  cout << " Select the letter corresponding to your choice: " << endl;
  cout << "**********************************************" << endl;
  cin >> menu_choice;

  switch (menu_choice) {
  case 'a':
    do {
      cout << "**********************************************" << endl;
      cout << "                USER LOGIN                 " << endl;
      cout << "**********************************************" << endl;

      cout << "Please enter your name, netID, and building in " << endl;
      cout << "the following format: John jg5343 12B" << endl;
      cin >> name;
      cin >> id;
      cin >> building;

      cout << "**********************************************" << endl;
      cout << "Please enter current time in hours, minutes,  " << endl;
      cout << "and seconds in the following format: 10 12 34" << endl;
      cin >> hr;
      cin >> m;
      cin >> s;

      // Check that starting time of the user is greater than real time

      if (checkStartTime(hr, m, s) == 0) {
        cout << "Error, starting time is less than real time!" << endl;
        break;
      }

      // Create instance of class Time for printing starting and ending time

      Time t(hr, m, s);

      // Create instance of class user based on uiser login information

      user const user1(name, id, building);

      cout << "**********************************************" << endl;
      cout << "Please enter the program you wish to select: " << endl;
      cout << "Please type 'r' for a regular 45 minutes cycle  " << endl;
      cout << "Please type 'd' for a delicate 60 minutes cycle" << endl;
      cout << "Please type 'q' for a quick cycle of 30 minutes" << endl;
      cin >> cycle_choice;

      // switch structure where we intialize the cycle object to appropriate
      // cycle time based on user input of cycle type

      switch (cycle_choice) {
      case 'r':
        c.setCycleTime(45);
        break;

      case 'd':
        c.setCycleTime(60);
        break;

      case 'q':
        c.setCycleTime(30);
        break;

      default:
        cout << "Invalud selection!" << endl;
      }

      // For loop where we loop through every machine object and assign it to
      // user if it is free (flag 0)
      for (vector<Machine *>::iterator it = vec.begin(); it != vec.end();
           ++it) {
        if ((*it)->getFlag() == 0) {
          cout << "**********************************************" << endl;
          cout << "                  RECEIPT                     " << endl;
          cout << "**********************************************" << endl;
          user1.print(); // print user info from class user
          cout << "    Program: " << c.getCycleType() << endl;
          cout << "    Starting time: ";
          t.printTime(); // print starting time
          File << user1.getID() << " " << (*it)->getMachineNumber() << " "
               << t.getHour() << " " << t.getMinute() << " " << t.getSecond()
               << " ";
          t.endTime(c); // function to update data members to end time in class
                        // time (not machine yet)
          cout << "    Ending time: ";
          t.printEndTime(); // print end-time
          cout << "**********************************************" << endl;
          // Then, write information in data file
          File << t.getEndHour() << " " << t.getEndMin() << " " << t.getEndSec()
               << endl;
          cout << "    Assigned machine n°: " << (*it)->getMachineNumber()
               << endl;
          // update end-time for machine object pointed to by iterator
          (*it)->setHour(hr);
          (*it)->setMinute(m);
          (*it)->setSecond(s);
          (*it)->endTime(c);
          (*it)->updateStatus();
          break; // break when machine has been found and assigned
        }

        // When we reach last machine element (5), we run a second loop to see
        // if any of the five machines finished its cycle and can be used again

        else if (it == vec.end() - 1) {
          for (vector<Machine *>::iterator ptr = vec.begin(); ptr != vec.end();
               ++ptr) {
            if ((*ptr)->newStatus(hr, m, s) == 0) {
              (*ptr)->updateStatus();
              cout << "**********************************************" << endl;
              cout << "                  RECEIPT                     " << endl;
              cout << "**********************************************" << endl;
              user1.print(); // print user info from class user
              cout << "    Program: " << c.getCycleType() << endl;
              cout << "    Starting time: ";
              t.printTime(); // print starting time
                             // write data into file
              File << user1.getID() << " " << (*it)->getMachineNumber() << " "
                   << t.getHour() << " " << t.getMinute() << " "
                   << t.getSecond() << " ";
              (*ptr)->updateStatus();
              (*ptr)->setHour(hr);
              (*ptr)->setMinute(m);
              (*ptr)->setSecond(s);
              (*ptr)->endTime(c);
              t.endTime(c); // update end time
              cout << "    Ending time: ";
              t.printEndTime(); // print end time
              cout << "    Assigned machine n°: " << (*ptr)->getMachineNumber()
                   << endl;
              File << t.getEndHour() << " " << t.getEndMin() << " "
                   << t.getEndSec() << endl;
              break;
            }
            if (ptr == vec.end() - 1) {
              cout << "No machine is available " << endl;
            }
          }
        }
      }

      // Output for terminating condition of the loop
      cout << "Do you wish to start a cycle? Press 'y' for yes" << endl;
      cin >> userchoice;

    } while (userchoice == 'y');
    break;

  case 'b':
    cout << "**********************************************" << endl;
    cout << "Please enter your netID: " << endl;
    cin >> idprob;
    cout << "Please enter the starting date of the cycle you  " << endl;
    cout << "to report in format: 12 32 54" << endl;
    cin >> hprob >> mprob >> sprob;
    cout << "**********************************************" << endl;
    cout << "                  PROBLEM REPORT                " << endl;
    cout << "**********************************************" << endl;
    cout << "netID: " << idprob << endl;
    cout << "Starting time of machine: ";
    cout << setfill('0');
    cout << setw(2) << hprob // set width to 2 spaces
         << ":" << setw(2) << mprob << ":" << setw(2) << sprob << endl;
    cout << "Your case has been saved, we will get with a  " << endl;
    cout << "report in the upcoming days!" << endl;
    break;

  default:
    cout << "ERROR, INVALID SELECTION!" << endl;
    break;
  }

  File.close();
}