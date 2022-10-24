
#include <fstream>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

#ifndef MachineSystem_h
#define MachineSystem_h

// class Cycle to store information about the type of cycle/program the user
// choses
// ------------------------------------//
//             class Cycle
// ------------------------------------//

class Cycle {

private:
  string cycletype; // Type of program that user will chose
  int cycletime;    // Duration of cycle

public:
  // Default constructor

  Cycle() {
    cycletime = 0;
    cycletype = "regular";
  }

  // Setters and getters

  void setCycleTime(int time) { cycletime = time; }

  void setCycleType(string cycle_type) { cycletype = cycle_type; }

  string getCycleType() const { return cycletype; }

  // string getCycleTime() const { return cycletime; }

  friend class Time; // so we access and add cycletime to starting time to get
                     // endtime of cycle
};

// Class Time that deals with storing starting time and calculating endtime of
// the cycles
// ------------------------------------//
//               class Time
// ------------------------------------//

class Time {

protected:
  int hour;   // Starting hour of the cycle
  int minute; // Starting minute of the cycle
  int second; // Starting second of the cycle
  int endh;   // Ending hour of the cycle
  int endm;   // Ending minute of the cycle
  int ends;   // Ending second of the cycle

public:
  // Default constructor

  Time() {
    hour = 0;
    minute = 0;
    second = 0;
    endh = 0;
    endm = 0;
    ends = 0;
  }

  // Non-default constructor

  Time(int hr, int min, int sec) {
    hour = hr;
    minute = min;
    second = sec;
  }

  // Setters

  void setHour(int hr) { hour = hr; }

  void setMinute(int min) { minute = min; }

  void setSecond(int sec) { second = sec; }

  // Getters

  int getHour() { return hour; }

  int getMinute() { return minute; }

  int getSecond() { return second; }

  int getEndHour() { return endh; }

  int getEndMin() { return endm; }

  int getEndSec() { return ends; }

  // Function to calculate endTime of the cycle

  void endTime(Cycle c) {

    endm = minute + c.cycletime;
    endh = hour;
    ends = second;

    if (endm >= 60) {
      endm = endm - 60;
      endh = endh + 1;
    }

    if (endh >= 24) {
      endh = 0;
    }
  }

  void printTime() {
    cout << setfill('0');
    cout << setw(2) << hour // set width to 2 spaces for printing time
         << ":" << setw(2) << minute << ":" << setw(2) << second << endl;
  }

  void printEndTime() {

    cout << setfill('0');
    cout << setw(2) << endh // set width to 2 spaces
         << ":" << setw(2) << endm << ":" << setw(2) << second << endl;
  }
};

// class Machine that inherits from class Time to store machine objects
// ------------------------------------//
//           class Machine
// ------------------------------------//

class Machine : public Time {

private:
  int machine_number; // Number of the machine (1-5)
  bool flag;          // false stands for free and true for occupied machine

public:
  Machine() {}

  // Non-default constructor

  Machine(int num, bool flag_var) {

    machine_number = num;
    flag = flag_var;
  }

  // getters

  bool getFlag() { return flag; }

  int getMachineNumber() { return machine_number; }

  // setters

  void updateStatus() { flag = !flag; }

  bool assignMachine() { // check wether function is free so we can assign it

    if (flag == false) {
      return true;
    } else

      return false;
  }

  void print() {
    cout << "status is: " << flag;
    cout << "number is: " << machine_number;
  }

  // function to check that strating time entered by user is greater than
  // endtime of ending time of each of the machine (via loop) so we can assign
  // machine

  bool newStatus(int h, int m, int s) {

    if (h > endh) {
      return false;
    }

    if (h == endh) {
      if (m > endm) {
        return false;
      } else if (m == endm) {
        if (s > ends) {
          return false;
        }
      }
    }
    return true;
  }
};

#endif /* MachineSystem_h */
