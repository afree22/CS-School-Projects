

/*
 *  aof7P5.cpp
 *
 *  COSC 052 Fall 2016
 *  Project #5
 *
 *  Due on: DEC 1, 2015
 *  Author: Anne Freeman
 *
 *
 *  In accordance with the class policies and Georgetown's
 *  Honor Code, I certify that, with the exception of the
 *  class resources and those items noted below, I have neither
 *  given nor received any assistance on this project.
 *
 *  References not otherwise commented within the program source code.
 *  Note that you should not mention any help from the TAs, the professor,
 *  or any code taken from the class textbooks.
 */


const int LIST_SIZE_MIN = 126;  //new for P5 (mandatory) (please do not change this)


const int MAX_NUMBER = 126000;  //new for P5 (mandatory) (please do not change this)

const int BASE_YEAR = 1600;             //new for P5 (mandatory) (please do not change this)
const int MAX_YEAR_ADDITION = 415;      //new for P5 (mandatory) (please do not change this)
const double REPEAT_PERCENT = 0.075;    //new for P5 (mandatory) (please do not change this)


#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <ctime>
#include "DateTime.h"
#include "LL.h"


using namespace std;



/****************************************************************************
 *                                                                          *
 *                    Project #5 function main()                            *
 *                                                                          *
 *            This complete function main() is provided to                  *
 *            students in COSC 052 Fall 2016 to use in part                 *
 *            or in total for the final programming project.                *
 *            Students may use this code as their own without               *
 *            any attribution.                                              *
 *                                                                          *
 ****************************************************************************/

int main(int argc, const char * argv[])
{
    try
    {
        if ( LIST_SIZE < LIST_SIZE_MIN )
        {
            ostringstream listSizeErr;
            listSizeErr << "Minimum list size is " << LIST_SIZE_MIN << ".\n";
            listSizeErr << "Please update the constant LIST_SIZE and run the program again.";
            
            throw ( listSizeErr.str() );
        }
        
        //srand(time(0));  //put this back in to get a different list of dates each time
        ProcessTimer stopWatch;
        
        LL<Date> randomList;
        Date searchTarget = Date(1492, 8, 2);
        Date searchMissing = Date(1492, 8, 2);
        Date repeatDate = Date(1865, 6, 22);
        
        int foundAt = -1;
        int year = 0;
        int month = 0;
        int day = 0;
        double repeatNow = 0.0;
        
        for ( int i = 0; i < ( LIST_SIZE ); i++ )
        {
            year = BASE_YEAR + ( rand() % MAX_YEAR_ADDITION );
            month = (rand() % 12) + 1;
            day = (rand() % 28) + 1;
            repeatNow = rand() / static_cast<double>(RAND_MAX);
            Date randDate(year, month, day);
            
            if ( repeatNow < REPEAT_PERCENT )
                randomList.push_back( repeatDate );
            else
                randomList.push_back( randDate );
        }
        
        cout << "list contents:\n";
        //for ( int i = 0; i < randomList.size(); i++ )
        //{
        //    cout << "myList.at(" << i << ") = " << randomList.at(i) << endl;
        //}
        
        //make a copy of the random list so we will always have an unsorted version
        LL<Date> unsortedList(randomList);
        
        
        cout << "invoking function to bubble sort list with " << LIST_SIZE << " elements" << endl;
        stopWatch.setTimeStart(clock());
        randomList.bubbleSort();
        stopWatch.setTimeEnd(clock());
        cout << "sorted list contents:\n";
        //for ( int i = 0; i < randomList.size(); i++ )
        //{
        //    cout << "myList.at(" << i << ") = " << randomList.at(i) << endl;
        //}
        cout << "bubbleSort results:\n";
        cout << stopWatch << endl;
        
        
        //copy unsorted list contents back into list to sort
        randomList = unsortedList;
        cout << "invoking function to bubble sort (iterator version) list with ";
        cout << LIST_SIZE << " elements";
        cout << endl;
        stopWatch.setTimeStart(clock());
        randomList.bubbleSortI();
        stopWatch.setTimeEnd(clock());
        cout << "sorted list contents:\n";
        //for ( int i = 0; i < randomList.size(); i++ )
        //{
        //   cout << "myList.at(" << i << ") = " << randomList.at(i) << endl;
        //}
        cout << "bubbleSortI results:\n";
        cout << stopWatch << endl;
        
        
        //copy unsorted list contents back into list to sort
        randomList = unsortedList;
        cout << "invoking function to selection sort list with " << LIST_SIZE << " elements";
        cout << endl;
        stopWatch.setTimeStart(clock());
        randomList.selectionSort();
        stopWatch.setTimeEnd(clock());
        cout << "sorted list contents:\n";
        //for ( int i = 0; i < randomList.size(); i++ )
        //{
        //    cout << "myList.at(" << i << ") = " << randomList.at(i) << endl;
        //}
        cout << "selectionSort results:\n";
        cout << stopWatch << endl;
        
        //use binary search to find index of known value near end of list
        //Note: There could be a duplicate match on the list prior to the
        //      index used to find the search target
        searchTarget = randomList.at(LIST_SIZE - (LIST_SIZE/100));
        cout << "invoking function to binarySearch sorted list for the value " << searchTarget;
        cout << endl;
        stopWatch.setTimeStart(clock());
        foundAt = randomList.binarySearch(searchTarget);
        stopWatch.setTimeEnd(clock());
        if (foundAt > 0)
        {
            cout << "Found value " << randomList.at(foundAt) << " at index " << foundAt << endl;
        }
        else
        {
            cout << searchTarget << " not found in the list.\n";
        }
        cout << stopWatch << endl;
        
        //use binary search to find value known not to be in the list
        Date knownMissing(searchMissing); //test copy constructor of Date class
        cout << "invoking function to binarySearch sorted list for the value " << knownMissing;
        cout << endl;
        stopWatch.setTimeStart(clock());
        foundAt = randomList.binarySearch(knownMissing);
        stopWatch.setTimeEnd(clock());
        if (foundAt > 0)
        {
            cout << "Found value " << knownMissing << " at index " << foundAt << endl;
        }
        else
        {
            cout << knownMissing << " not found in the list.\n";
        }
        cout << stopWatch << endl;
        
        //copy unsorted list contents back into list prior to testing linear search
        randomList = unsortedList;
        //use linear search to find index of known value near end of list
        //Note: There could be a duplicate match on the list prior to the
        //      index used to find the search target
        searchTarget = randomList.at(LIST_SIZE - (LIST_SIZE/100));
        cout << "invoking function to linearSearch un-sorted list for the value " << searchTarget;
        cout << endl;
        stopWatch.setTimeStart(clock());
        foundAt = randomList.linearSearch(searchTarget);
        stopWatch.setTimeEnd(clock());
        if (foundAt > 0)
        {
            cout << "Found value " << randomList.at(foundAt) << " at index " << foundAt << endl;
        }
        else
        {
            cout << searchTarget << " not found in the list.\n";
        }
        cout << stopWatch << endl;
        
        //use linear search to find value known not to be in the list
        cout << "invoking function to linearSearch un-sorted list for the value " << knownMissing;
        cout << endl;
        stopWatch.setTimeStart(clock());
        foundAt = randomList.linearSearch(knownMissing);
        stopWatch.setTimeEnd(clock());
        if (foundAt > 0)
        {
            cout << "Found value " << knownMissing << " at index " << foundAt << endl;
        }
        else
        {
            cout << knownMissing << " not found in the list.\n";
        }
        cout << stopWatch << endl;
        
           
    } //END try block
    
    catch (string stringErrorMsg)
    {
        cout << "ERROR in function main()\n";
        cout << stringErrorMsg << endl;
    }
    catch( ... )
    {
        
    } //END catch all block
    
    return 0;
    
} //END function main()