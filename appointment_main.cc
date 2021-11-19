/**
 *   @file: appointment_main.cc
 * @author: Brody Reynolds
 *   @date: 11/19/2021
 *  @brief: A program that takes an formatted appointment and returns it in its separate categories 
 */

#include "appointment.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

main(int argc, char const *argv[])
{
    string newTime;

    Appointment a(" Meeting with Bob | 2021 |11 |23 |8:30 aM | 15 "); // Sets appointment class to have the string as an input
    
    cout << "Title: " << a.getTitle() << endl; // Returns title
    cout << "Date: " << a.getDate() << endl; // Returns date

    newTime = a.finalizedMilitarytime(a.getTime()); // Formats military time

    cout << "Time: " << newTime << endl; // Returns time in military format
    cout << "Standard Time: " << a.getStandardTime() << endl; // Returns standard time
    cout << "Standard to Military Time: " << newTime << endl; // Returns military time from standard
    cout << "Military to Standard Time: " << a.militaryToStandard(stoi(newTime)) << endl; // Takes military time and returns to standard time
    cout << "Duration: " << a.getDuration() << endl; // Returns duration

    return 0;
} // main

// Things to do:
// remove spaces in title