## Time-Sharing Laundry System

This program was build for my Object Oriented Programming class and demonstrates the use of diffreent OOP paradigms learned throughout the course. 

## Introduction to the problem 

The Time-Sharing laundry system is a system that helps optimize the use of laundry machines while accounting for the constraints of time and resources. In this project, I aim to design a product that optimizes the use of a set of 5 machines only and a large number of students with tight schedules. Each user will be assigned a machine in a way that would minimize their waiting time.

## Approach 

To solve the problem, I create a system that takes user information and starting time and either starts a cycle or reports a problem depending on the user choice in the menu.

Initially, I designed the program using system time in a way that whenever you run the program we start the cycle using the current real time. However, this posed a problem: we can run the program in real time because then we would need to wait for 30 minutes before the cycle actually finishes. One alternative was to represent each cycle time by a lesser value. For instance, quick mode which takes 30 mins would be represented by a
   
cycle of 30 seconds in the system. Although this solution provided a simple way of testing, it is quite not realistic.
The solution I ended up implementing was taking the starting time as user input and using a function to make sure that user input is valid. The input is valid when it is greater than system time. I use chrono library to find real time, but if run on repl.it it will calculate time in UTC which in advance of 4 hours to GST.

I make the assumption that the program is ran every day, so we do not need to also check if the user is starting the cycle on the same day. Also, I store the history of the system in a data file. Thus, the data file would contain data of each day only.
I made the choice to use two for loops instead of one although it would increase time complexity because I want to make sure that we are using the 5 machines somewhat equally. If we had one for loop, we might end up using 1 or 2 machines only and thus exhaust them. When looping twice, we make sure that the 5 machines are first filled before we assign them to the user.

## Solution 

The aim of this system is to optimize the use of a limited set of washing machines while accounting for a large number of users operating on tight schedules.
The system starts by asking the user to enter their details: name, netID, and building number. The user is then prompted with a menu of two choices: (1) starting a cycle or (2) Reporting a problem.
- Case 1: Starting a cycle

We set the number of machines in our system to 5 which we represent as objects of class Machine. We create a static vector of size 5 of pointers to objects Machine which we initialize to their respective numbers and to a flag of 0. The flag is a boolean variable that helps us track the status of each machine: true means occupied and false means free.
We ask the user for the starting time that they are using and check using a function that the time entered is greater than the real time (with the help of chrono library). We then ask the user for the type of program they want to execute: regular (45 mins), delicate (60 mins), or quick (30 mins). We use the user choice to initialize object cycle.

Class Time calculates the end time of the cycle using the starting time entered by the user added to the duration of the   cycle accessed through class Cycle (class Time is friends with class Cycle). We then print a receipt to the user containing their details, the starting and ending times, and the assigned washing machine number. When we print the receipt to the user, we also write their details in a data file. 

In the main, we construct a for loop that loops through the elements of the vector (the 5 machines) to assign and print appropriate outputs. The 5 first users would be assigned one of the five machines in the system. Once a 6th user enters and all machines are taken, we compare the starting time they provide with the ending time of each of the machines in another loop and assign the first machine that would be free at said time.

- Case 2: Reporting a problem

I know, from experience, that many times the machine would burn clothes or not wash them properly. Often, students want to report the machine so upcoming users do not use it, but cannot. Here, I implement a function where the user can report a problem in their machine by indicating their netID and the starting time.
The system would save the information (provided we do not re-run the program, which we wouldn’t do in a real-life scenario) and print a receipt to the user.

## Target Audience 

I made this program specifically for college students (that’s why I ask for netID :)) because laundry is one of those chores we do not enjoy doing. I believe this system could make doing laundry a little less daunting but it can also be used in the setting of a residential building in the city or the like.
