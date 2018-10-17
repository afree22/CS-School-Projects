

/*
 * DateTime.cpp
 *
 * COSC 052 Fall 2016
 * Project #5
 *
 * Due on: DEC 1, 2015
 * Author: Anne Freeman
 *
 *
 * In accordance with the class policies and Georgetown's
 * Honor Code, I certify that, with the exception of the
 * class resources and those items noted below, I have neither
 * given nor received any assistance on this project.
 *
 * References not otherwise commented within the program source code.
 * Note that you should not mention any help from the TAs, the professor,
 * or any code taken from the class textbooks.
 */

#include "DateTime.h"
#include <iostream>
#include <iomanip>


using std::cout;
using std::endl;


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Date implementation code                         **
 **                                                                        **
 **                 You will write all of the Date class                   **
 **                 implementation code.  Do not make another              **
 **                 file, put your code for the Date class                 **
 **                 in this file along with the provided                   **
 **                 Time class implementation code.                        **
 **                                                                        **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/


Date::Date (int year, int month, int date)
{
    setDate(year, month, date);
}

//copy constructor
Date::Date (const Date &otherDate)
{
    setDate(otherDate);
}

void Date::setDate (int year, int month, int date)
{
    yyyy = year;
    mm = month;
    dd = date;
}

void Date::setDate (const Date &otherDate)
{
    this->yyyy = otherDate.yyyy;
    this->mm = otherDate.mm;
    this->dd = otherDate.dd;
}


bool Date:: operator==(const Date &otherDate) const
{
    if (this->yyyy==otherDate.yyyy && this->mm == otherDate.mm
        && this->dd == otherDate.dd)
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

bool Date:: operator!=(const Date &otherDate) const
{
    if (this->yyyy==otherDate.yyyy && this->mm == otherDate.mm
        && this->dd == otherDate.dd)
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Date:: operator <=(const Date &otherDate) const
{
    if(this->yyyy > otherDate.yyyy)
    {
        return false;
    }
    if((this->yyyy >= otherDate.yyyy) && (this->mm > otherDate.mm))
    {
        return false;
    }
    if((this->dd > otherDate.dd) && (this->mm >= otherDate.mm) && (this->yyyy >= otherDate.yyyy))
    {
        return false;
    }
    else
    {
        return true;
    }
    
}


bool Date:: operator <(const Date &otherDate) const
{
    if(this->yyyy < otherDate.yyyy)
    {
        return true;
    }
    if((this->yyyy <= otherDate.yyyy) && this->mm < otherDate.mm)
    {
        return true;
    }
    if((this->dd < otherDate.dd) && (this->mm <= otherDate.mm) && (this->yyyy <= otherDate.yyyy))
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool Date:: operator >=(const Date &otherDate) const
{
    if(this->yyyy < otherDate.yyyy)
    {
        return false;
    }
    if((this->yyyy <= otherDate.yyyy) && (this->mm < otherDate.mm))
    {
        return false;
    }
    if((this->dd < otherDate.dd) && (this->mm <= otherDate.mm) && (this->yyyy <= otherDate.yyyy))
    {
        return false;
    }
    else
    {
        return true;
    }
}

bool Date:: operator >(const Date &otherDate) const
{
    if(this->yyyy > otherDate.yyyy)
    {
        return true;
    }
    if((this->yyyy >= otherDate.yyyy) && this->mm > otherDate.mm)
    {
        return true;
    }
    if((this->dd > otherDate.dd) && (this->mm >= otherDate.mm) && (this->yyyy >= otherDate.yyyy))
    {
        return true;
    }
    else
    {
        return false;
    }
    
}

Date Date::operator=(const Date &rhsObj)
{
    
    if(this != &rhsObj)
    {
        this->yyyy = rhsObj.yyyy;
        this->mm = rhsObj.mm;
        this->dd = rhsObj.dd;
    }
    
    return *this;
    
    /* This is what I originally turned in but I'm not sure that it's right
    if(this != &rhsObj)
    {
        yyyy = rhsObj.yyyy;
        mm = rhsObj.mm;
        dd = rhsObj.dd;
    }
    return rhsObj;
     
     */
}


std::ostream& operator<< (std::ostream &os, const Date &d)
{
    os << std::setfill('0');
    os << std::setw(4) << d.yyyy << "/";
    os << std::setw(2) << d.mm << "/";
    os << std::setw(2) << d.dd;
    
    return os;
}

std::istream& operator>>(std::istream &in, Date &d)
{
    char ch;
    
    in >> d.yyyy;
    
    in >> ch;
    
    in >> d.mm;
    
    in >> ch;
    
    in >> d.dd;
    
    return in;
}


/****************************************************************************
 ****************************************************************************
 **                                                                        **
 **                 class Time implementation code                         **
 **                                                                        **
 **                 This code is provided to students                      **
 **                 in COSC 052 Fall 2016 to use in                        **
 **                 part or in total for class projects.                   **
 **                 Students may use this code as their                    **
 **                 own, without any attribution.                          **
 **                                                                        **
 ****************************************************************************
 ****************************************************************************/



/****************************************************************************
 *                    Time class default constructor                        *
 ****************************************************************************/

Time::Time(int hour, int minute)
{
#ifdef DEBUG_DATE
    std::cout << "Entered constructor Time::Time(int, int, int)" << std::endl;
#endif
    
    setTime(hour, minute);
    
#ifdef DEBUG_DATE
    std::cout << "Exiting constructor Time::Time(int, int)" << std::endl;
#endif
    
} //END constructor with parameters for Time class



/****************************************************************************
 *                  Time class member function setTime                      *
 ****************************************************************************/

void Time::setTime(int hour, int minute)
{
    hh = hour;
    mm = minute;
    
} //END member function Time::setTime



/****************************************************************************
 *                 Time class stream extraction operator                    *
 ****************************************************************************/

std::istream& operator>>(std::istream &in, Time &t)
{
    // input format is expected to be hh:mm
    // examples:
    // 2:45
    // 02:45
    // 15:30
    // 18:05
    
    char ch;
    
    in >> t.hh; //extract the hours and store them in data member hh
    
    in >> ch; //extract and discard the dilimiting character
    
    in >> t.mm; //extract the minutes and store them in data member mm
    
    return in;
    
} //END overloaded stream extraction operator for Time class



/****************************************************************************
 *                 Time class stream insertion operator                     *
 ****************************************************************************/

std::ostream& operator<<(std::ostream &os, const Time &t)
{
    os << std::setfill('0');
    
    os << std::setw(2) << t.hh << ":";
    os << std::setw(2) << t.mm;
    
    os << std::setfill(' ');
    
    return os;
    
} //END overloaded stream insertion operator for Time class



/****************************************************************************
 *                     Time class assignment operator                       *
 ****************************************************************************/

Time Time::operator=(const Time &rhsObj)
{
    
    if (this != &rhsObj)
    {
        //not a self assignment, OK to proceed
        hh = rhsObj.hh;
        mm = rhsObj.mm;
    }
    
    return rhsObj;
    
    
} //END overloaded assignment operator for Time class


/****************************************************************************
 **                                                                        **
 **                class ProcessTimer implementation code                  **
 **                                                                        **
 **                  This code is provided to students                     **
 **                  in COSC 052 Fall 2016 to use in part                  **
 **                  or in total for class projects.                       **
 **                  Students may use this code as their                   **
 **                  own, without any attribution.                         **
 **                                                                        **
 ****************************************************************************/

ProcessTimer::ProcessTimer()
{
    timeStart = 0;
    timeEnd = 0;
}

ProcessTimer::ProcessTimer(clock_t tmSt)
{
    timeStart = tmSt;
    timeEnd = 0;
}

ProcessTimer::~ProcessTimer()
{
    std::cout << "Inside destructor for ProcessTimer object" << std::endl;
}

std::ostream& operator<<(std::ostream &os, const ProcessTimer &tmStmp)
{
    std::cout << "Start time:\t" << tmStmp.timeStart << "\n";
    std::cout << "End time:\t" << tmStmp.timeEnd << "\n";
    std::cout << "Elapsed time:\t"
    << (tmStmp.timeEnd - static_cast<double>(tmStmp.timeStart))/CLOCKS_PER_SEC;
    std::cout << "\n";
    std::cout << std::endl;
    
    return os;
}

void ProcessTimer::setTimeStart(clock_t tmStart)
{
    timeStart = tmStart;
}

void ProcessTimer::setTimeEnd(clock_t tmEnd)
{
    timeEnd = tmEnd;
}


clock_t ProcessTimer::getTimeStart()
{
    return timeStart;
}

clock_t ProcessTimer::getTimeEnd()
{
    return timeEnd;
}


clock_t ProcessTimer::getTimeElapsed()
{
    return (timeEnd - static_cast<double>(timeStart))/CLOCKS_PER_SEC;
}



