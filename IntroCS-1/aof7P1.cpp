// This project calculates the cost for creating a countertop
// with dimensions and materials specified by the user


/*
 * aof7P1.cpp
 *
 * COSC 051 Spring 2016
 * Project #1
 *
 * Due on: FEB 03, 2016
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

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
using namespace std;

const double COST_MARBLE = 92.99;
const double COST_GRANITE = 78.99;
const double COST_QUARTZ = 56.99;
const double MIN_LENGTH = 5.00;
const double MAX_LENGTH = 25.00;
const int MIN_FINISHED_EDGES = 0;
const int MAX_FINISHED_EDGES = 2;
const double MIN_DEPTH = 5.00;
const double WASTAGE_AREA = .26;
const double MIN_HEIGHT_RATIO = .58;
const double MAX_HEIGHT_RATIO = .80;
const double COST_PER_FOOT = 4.99;   //Finishing cost


int main()
{
    
    string WELCOME_MESSAGE = "Welcome to Claude\'s Custom Counters, Inc. Calculator";
    string PURPOSE = "This application calculates cost and fabrication \ndata based on user entries.";
    
    char material = '?';
    double length =0.0;
    double depth = 0.0;
    double height = 0.0;
    
    int finishedLength = 0;
    int finishedDepth = 0;
    
    cout << WELCOME_MESSAGE << endl;
    cout << PURPOSE << endl;
    cout << "Please enter the material code (m - marble, g- granite, q - quartz)" << endl;
    cin.get(material);
    cin.ignore(80, '\n');
    
    
    //series of statements to test variables
        if (material != 'm' && material != 'M' && material != 'g' &&
        material != 'G' && material != 'q' && material != 'Q')
        {
            cout <<"The material selected is not a valid value" << endl;
            cout << "The program will exit now" << endl;
            return 0;
        }
    
    cout << "Please enter the counter top length (";
    cout << fixed << showpoint << setprecision(2) << MIN_LENGTH << "\' - ";
    cout<< fixed << showpoint << setprecision(2)<< MAX_LENGTH << "\'):" << endl;
    cin >> length;
        if(length < MIN_LENGTH || length > MAX_LENGTH)
        {
            cout <<"The length selected is not a valid value" << endl;
            cout << "The program will exit now" << endl;
            return 0;
        }
    
    
    cout << "Please enter counter top depth (";
    cout<< fixed << showpoint << setprecision(2)<< MIN_DEPTH << "\' - ";
    cout<< fixed << showpoint << setprecision(2) << length << "\'):" << endl;
    cin >> depth;
        if (depth < MIN_DEPTH || depth > length)
        {
            cout <<"The depth selected is not a valid value" << endl;
            cout << "The program will exit now" << endl;
            return 0;
        }
                
                
    double hMin = MIN_HEIGHT_RATIO * depth;
    double hMax = MAX_HEIGHT_RATIO * depth;
    cout << "Please enter counter top height (" << hMin;
    cout << "\' - " << hMax << "\'):" << endl;
    cin >> height;
        if (height < hMin || height > hMax)
        {
            cout <<"The height selected is not a valid value" << endl;
            cout << "The program will exit now" << endl;
            return 0;
        }
    
    
    cout << "\n";
    cout << "How many length edges should be finished and polished ";
    cout << "("<< MIN_FINISHED_EDGES << " - " << MAX_FINISHED_EDGES << ")" << endl;
    cin >> finishedLength;
    cin.ignore(80, '\n');
        if(finishedLength < MIN_FINISHED_EDGES || finishedLength > MAX_FINISHED_EDGES)
        {
            cout <<"The number of length edges selected is not a valid value." << endl;
            cout << "The program will exit now" << endl;
            return 0;
        }
            
            
    cout << "How many depth edges should be finished and polished ";
    cout << "(" << MIN_FINISHED_EDGES << " - " << MAX_FINISHED_EDGES << ")" << endl;
    cin >> finishedDepth;
    cin.ignore(80, '\n');
        if (finishedDepth < MIN_FINISHED_EDGES || finishedDepth > MAX_FINISHED_EDGES)
        {
            cout <<"The number of depth edges selected is not a valid value." << endl;
            cout << "The program will exit now" << endl;
            return 0;
        }
 
 
    

    
    //all variables should be within their correct ranges, program continues
    
    double costFinishedDepth = finishedDepth * depth * COST_PER_FOOT;
    double costFinishedLength = finishedLength * length * COST_PER_FOOT;
    double costFinishing = costFinishedDepth + costFinishedLength;
    
    double totalCost = 0.0;
    double area = length * height;
    
    cout << "\n";
    cout << setw(22) << "Dimensions" << endl;
    
    cout << setw(7) << fixed << showpoint << setprecision(2)<< length;
    cout << " feet - counter top length." << endl;
    
    cout << setw(7) << fixed << showpoint << setprecision(2) << depth;
    cout << " feet - counter top depth." << endl;
    
    cout << setw(7) << fixed << showpoint << setprecision(2) << height;
    cout << " feet - counter top height." << endl;
    
    area = area + WASTAGE_AREA * area;   //adds 26% of the original area and stores in area
    area = ceil(area);         // rounds up
    
    
    //output for material specific costs
    if (material == 'm' || material == 'M')
    {
        cout << setw(7) <<  fixed << showpoint << setprecision(2) << area;
        cout << " square feet - Marble required to begin fabrication." << endl;
        cout << "\n";
        
        cout << setw(19) << "Costs" << endl;
        double costMarble = area * COST_MARBLE;
        cout << setw(9) << fixed << showpoint << setprecision(2) << costMarble;
        cout << " dollars - cost for Marble" << endl;
        totalCost = costFinishing + costMarble;
    }
    
    else if (material == 'g' || material == 'G')
    {
        cout << setw(7) << fixed << showpoint << setprecision(2) << area;
        cout << " square feet - Granite required to begin fabrication." << endl;
        cout << "\n";
        
        cout << setw(19) << "Costs" << endl;
        double costGranite = area * COST_GRANITE;
        cout << setw(9) << fixed << showpoint << setprecision(2) << costGranite;
        cout << " dollars - cost for Granite" << endl;
        totalCost = costFinishing + costGranite;
    }
    
    else if (material == 'q' || material == 'Q')
    {
        cout << setw(7) << fixed << showpoint << setprecision(2) << area;
        cout << " square feet - Quartz required to begin fabrication." << endl;
        cout << "\n";
        
        cout << setw(19) << "Costs" << endl;
        double costQuartz = area * COST_QUARTZ;
        cout << setw(9) << fixed << showpoint << setprecision(2) << costQuartz;
        cout << " dollars - cost for Quartz" << endl;
        totalCost = costFinishing + costQuartz;
    }
    
    cout << setw(9) << fixed << showpoint << setprecision(2) << costFinishing;
    cout << " dollars - cost for edge finishing" << endl;
    
    string line;
    line.assign(56, '-');
    cout << line << endl;
    
    cout << setw(9) << fixed << showpoint << setprecision(2) << totalCost;
    cout << " dollars - total cost" << endl;
    cout << "\n";
    cout << "Thank you for using Claude\'s Custom Counters, Inc. Calculator." << endl;
    
    
    return 0;
}

