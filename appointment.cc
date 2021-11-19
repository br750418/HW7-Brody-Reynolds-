#include "appointment.h"
/**
 *   @file: appointment.cc
 * @author: Brody Reynolds
 *   @date: 11/19/2021
 *  @brief: Public Classes: A program that takes an formatted appointment and returns it in its separate categories 
 */

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cctype>

using namespace std;

Appointment::Appointment() // Default constructor
{
    title = "None";
    year = 1;
    month = 1;
    day = 1;
    time = 0;
    duration = 1;
}

Appointment::Appointment(string newTitle, int newYear, int newMonth, int newDay, int newTime, int newDuration) // Default values if goes out of parameters
{
    if (!newTitle.empty())
    {
        title = newTitle;
    }
    else
    {
        title = "None";
    }

    if (year < 1)
    {
        year = 1;
    }
    else
    {
        year = newYear;
    }

    if (month < 1)
    {
        month = 1;
    }
    else
    {
        month = newMonth;
    }

    if (day < 1)
    {
        day = 1;
    }
    else
    {
        day = newDay;
    }

    if (time < 0)
    {
        time = 0;
    }
    else
    {
        time = newTime;
    }

    if (duration < 1)
    {
        duration = 1;
    }
    else
    {
        duration = newDuration;
    }
}

Appointment::Appointment(string appData) // Finds parts on inputted string
{
    int first, second, third, fourth, fifth, sixth;
    string newTitle, newYear, newMonth, newDay, newTime, newDuration, temp;

    first = appData.find('|'); // Finds title
    second = appData.find('|', first + 1); // Finds year
    third = appData.find('|', second + 1); // Finds month
    fourth = appData.find('|', third + 1); // Finds day
    fifth = appData.find('|', fourth + 1); // Finds time
    sixth = appData.find('|', fifth + 1); // Finds duration

    // Sets values to strings
    newTitle = appData.substr(0, first); 
    newYear = appData.substr(first + 1, second - first); 
    newMonth = appData.substr(second + 1, third - second);
    newDay = appData.substr(third + 1, fourth - third);
    newTime = appData.substr(fourth + 1, fifth - (fourth + 2));
    newDuration = appData.substr(fifth + 1, sixth - fifth);

    // Ran through setters
    setTitle(newTitle);
    setYear(stoi(newYear));
    setMonth(stoi(newMonth));
    setDay(stoi(newDay));
    setTime(stoi(finalizedMilitarytime(standardToMilitary(newTime))));
    setDuration(stoi(newDuration));
}

string Appointment::getTitle()
{
    return title;
}

int Appointment::getYear()
{
    return year;
}

int Appointment::getMonth()
{
    return month;
}

int Appointment::getDay()
{
    return day;
}

int Appointment::getTime()
{
    return time;
}

int Appointment::getDuration()
{
    return duration;
}

void Appointment::setTitle(string newTitle)
{
    title = newTitle; // Sets new value
}

void Appointment::setYear(int newYear)
{
    year = newYear; // Sets new value
}

void Appointment::setMonth(int newMonth)
{
    month = newMonth; // Sets new value
}

void Appointment::setDay(int newDay)
{
    day = newDay; // Sets new value
}

void Appointment::setTime(int newTime)
{
    time = newTime; // Sets new value
}

void Appointment::setDuration(int newDuration)
{
    duration = newDuration; // Sets new value
}

string Appointment::getDate()
{   
    // Returns the date in ( 1-1-1 ) format
    return to_string(year) + "-" + to_string(month) + "-" + to_string(day);
}

string Appointment::getStandardTime()
{
    return militaryToStandard(getTime()); // Takes getTime to military and returns as standard time
}

int Appointment::standardToMilitary(string time)
{
    int first, second, third, hour1;
    string hour, minute, timeSet, newTime;

    first = time.find(':'); // Finds the hour
    second = time.find(' ', first + 1); // Finds minutes
    third = time.find(' ', second + 1); // Finds meridiem

    hour = time.substr(0, first); // Declares hour
    minute = time.substr(first + 1, second - first); // Declares minutes
    timeSet = time.substr(second + 1, third - second); // Declares meridiem

    // Finds time if given meridiem is "am"
    if (timeSet == "am" || timeSet == "aM" || timeSet == "Am" || timeSet == "AM")
    {
        if (stoi(hour) == 12) // Sets hour to 0
        {
            hour = "00";
            newTime = hour + minute;
            newMTime = stoi(newTime);
        }
        else if (stoi(hour) > 0 && stoi(hour) < 12) // Gives given hour
        {
            newTime = hour + minute;
            newMTime = stoi(newTime);
        }
    }
    // Finds time if given meridiem is "pm"
    else if (timeSet == "pm" || timeSet == "pM" || timeSet == "Pm" || timeSet == "PM")
    {
        if (stoi(hour) > 0 && stoi(hour) < 12) // Adds to hour by 12 to convert into military time
        {
            hour1 = stoi(hour) + 12;
            newTime = to_string(hour1) + minute;
            newMTime = stoi(newTime);
        }
        else if (stoi(hour) == 12) // Keeps 12 as is
        {
            newTime = hour + minute;
            newMTime = stoi(newTime);
        }
    }

    return newMTime;
}

string Appointment::finalizedMilitarytime(int mTime)
{
    string newTime;

    if (to_string(mTime).size() == 1) // If value is 1 in length usually 0, than add 3 zeros to convert to military time
    {
        newTime = "000" + to_string(mTime);
    }
    else if (to_string(mTime).size() < 4) // If length is not equal to 4, add 0's
    {
        if (to_string(mTime).size() == 2) // Adds 2 zeros when length is only 2
        {
            newTime = "00" + to_string(mTime);
        }
        else // Adds 1 zero if length is only 3
        {
            newTime = "0" + to_string(mTime);
        }
    }
    else
    {
        newTime = to_string(mTime); // If value already has 4 in length, than return its value
    }

    return newTime;
}

string Appointment::militaryToStandard(int time)
{
    int hour, minute;
    string time_of_day;
    string newMinute;

    if (time > 1159) // Sets time to "pm"
    {
        time_of_day = "PM";
    }
    else
    {
        time_of_day = "AM";
    }

    if (time_of_day == "PM")
    {
        hour = ((time - 1200) / 100); // Converts time into hour
        minute = ((time - 1200) % 100); // Converts time to remaining minutes
        newMinute = to_string(minute);

        if (hour == 0) // Sets hour to 12 if given 0
        {
            hour = 12;
        }

        if (minute == 0) // Sets minutes to "00" for proper formatting
        {
            newMinute = "00";
        }
        else if (minute != 0 && minute < 10) // Adds a "0" if a single digit is given
        {
            newMinute = "0" + to_string(minute);
        }
    }
    else
    {
        hour = ((time) / 100); // If "am", just return value
        minute = ((time) % 100);
        newMinute = to_string(minute);

        if (hour == 0) // Sets hour to 12 if given 0
        {
            hour = 12;
        }

        if (minute == 0) // Sets minutes to "00" for proper formatting
        {
            newMinute = "00";
        }
        else if (minute != 0 && minute < 10) // Adds a "0" if a single digit is given
        {
            newMinute = "0" + to_string(minute);
        }
    }

    return to_string(hour) + ":" + newMinute + time_of_day;
}

bool operator==(const Appointment &first, const Appointment &second)
{
    // Compares and then returns if statement is true
    return (first.title == second.title && first.year == second.year && first.month == second.month && first.day == second.day && 
    first.time == second.time && first.duration == second.duration);
}