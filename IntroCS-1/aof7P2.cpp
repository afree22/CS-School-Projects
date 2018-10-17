// This program calculates the cost for the counter top with dimensions
// specified in an input file. If there is an error, it is printed to the screen
// and the file continues processing

/*
 * aof7P2.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #2
 *
 *  Due on: MAR 3, 2016
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

#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <fstream>
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
const double COST_PER_FOOT = 4.99;

const double MONTHS_PER_YEAR = 12;

int main()

{
    string Terminate = " Program will exit.";
    int orderY = 0;
    char ch;
    int orderM = 0;
    int orderD = 0;
    int deliveryY = 0;
    int deliveryM = 0;
    int deliveryD = 0;
    char stoneCode = '?';
    double length = 0.0;
    double depth = 0.0;
    double height = 0.0;
    int finishedLength = 0;
    int finishedDepth = 0;
    bool canContinue = true;
    
    int totalRecords = 0;
    int recordErrors = 0;
    int noErrors = 0;
    int countMarble = 0;
    int countGranite = 0;
    int countQuartz = 0;
    
    double totalCostMarble = 0.0;
    double totalCostGranite = 0.0;
    double totalCostQuartz = 0.0;
    double totalAreaMarble = 0.0;
    double totalAreaGranite = 0.0;
    double totalAreaQuartz = 0.0;
    
    string columnHeadings = " ";
    string extraData = " ";
    
    string WELCOME_MESSAGE = "Welcome to Claude\'s Custom Counters, Inc. Calculator";
    
    cout << WELCOME_MESSAGE << endl;
    cout << "This application calculates cost and fabrication" << endl;
    cout << "data based on sales data input files." << endl;
    
    ifstream inputFile;
    string salesFileName = " ";
    cout << "Please enter the complete path and name of the input data file:" << endl;
    getline(cin, salesFileName);
    inputFile.open(salesFileName.c_str());
    
    if(!inputFile)
    {
        cout << "Error opening the file." << Terminate << endl;
    }
    
    else
    {
        getline (inputFile, columnHeadings); //read first line (only the headings)
        
        cout << setw(8) << "Order";
        cout << setw(12) << "Delivery";
        cout << setw(5) << "S";
        cout << setw(25) << "L";
        cout << setw(4) << "D";
        cout << setw(10) << "Sq.";
        cout << setw(11) << "Total" << endl;
        
        cout << setw(8) << "Date";
        cout << setw(12) << "Date";
        cout << setw(5) << "C";
        cout << setw(7) << "Len.";
        cout << setw(7) << "Dep.";
        cout << setw(7) << "Hei.";
        cout << setw(4) << "E" << setw(4) << "E";
        cout << setw(10) << "Ft.";
        cout << setw(11) << "Cost" << endl;
        
        string line;
        line.assign(83, '-');   //outputs line ---- across
        cout << line << endl;

        
        while(inputFile >> orderY >> ch >> orderM >> ch >> orderD) //make sure that not at end of file
        {
            canContinue = true;
            //recieve data from row
            inputFile >> deliveryY >> ch >> deliveryM >> ch >> deliveryD;
            inputFile >> stoneCode;
            inputFile >> length;
            inputFile >> depth;
            inputFile >> height;
            inputFile >> finishedLength;
            inputFile >> finishedDepth;
            
        
            cout << orderY << "/";
            cout << setfill('0') << setw(2) << orderM << "/";
            cout << setw(2) << orderD << "  ";
            cout << deliveryY << "/";
            cout << setw(2) << deliveryM << "/";
            cout << setw(2) << deliveryD << "  ";
            cout << setfill(' ');
            
            cout << stoneCode;
            cout << setw(7) << fixed << showpoint << setprecision(2) << length;
            cout << setw(7) << fixed << showpoint << setprecision(2) << depth;
            cout << setw(7) << fixed << showpoint << setprecision(2) << height;
            cout << setw(4) << finishedLength;
            cout << setw(4) << finishedDepth;
            
            //check data from row
            if(deliveryY == orderY && deliveryM == orderM && deliveryD == orderD)
            {
                
                cout << "\n\tERROR:  order date and delivery date are equal.";
                canContinue = false;
            }
            if((((deliveryY-orderY)*MONTHS_PER_YEAR)+deliveryM) - orderM > 4)
            {
                cout << "\n\tERROR:  delivery date is too far from order date.";
                canContinue = false;
            }
            stoneCode = tolower(stoneCode);
            if(stoneCode != 'm'  && stoneCode != 'g' && stoneCode != 'q')
            {
                cout << "\n\tERROR:  stone code is not a valid value.";
                canContinue = false;
            }
            if(length < MIN_LENGTH || length > MAX_LENGTH)
            {
                cout << "\n\tERROR:  Invalid length.";
                canContinue = false;
            }
            if (depth < MIN_DEPTH || depth > length)
            {
                cout << "\n\tERROR:  Invalid depth.";
                canContinue = false;
            }
            double hMin = MIN_HEIGHT_RATIO * depth;
            double hMax = MAX_HEIGHT_RATIO * depth;
            if (height < hMin || height > hMax)
            {
                cout << "\n\tERROR:  Invalid height.";
                canContinue = false;
            }
            if(finishedLength < MIN_FINISHED_EDGES || finishedLength > MAX_FINISHED_EDGES)
            {
                cout << "\n\tERROR:  Invalid number of length edges to be finished.";
                canContinue = false;
            }
            if (finishedDepth < MIN_FINISHED_EDGES || finishedDepth > MAX_FINISHED_EDGES)
            {
                cout << "\n\tERROR:  Invalid number of depth edges to be finished.";
                canContinue = false;
            }
            
            //finish calculations if canContinue = true
            if(canContinue)
            {
                double costFinishedDepth = finishedDepth * depth * COST_PER_FOOT;
                double costFinishedLength = finishedLength * length * COST_PER_FOOT;
                double costFinishing = costFinishedDepth + costFinishedLength;
                double area = length * height;
                
                area = area + WASTAGE_AREA * area;
                area = ceil(area);         // rounds up
                cout << setw(11) << fixed << showpoint << setprecision(2) << area;
                
                
                if(stoneCode == 'm')
                {
                    double costMarble = area * COST_MARBLE;
                    double totalCost = costMarble + costFinishing;
                    cout << setw(11) << fixed << showpoint << setprecision(2) << totalCost;
                    totalAreaMarble = totalAreaMarble + area;
                    totalCostMarble = totalCostMarble + totalCost;
                    countMarble++;
                }
                else if(stoneCode == 'g')
                {
                    double costGranite = area * COST_GRANITE;
                    double totalCost = costGranite + costFinishing;
                    cout << setw(11) << fixed << showpoint << setprecision(2) << totalCost;
                    totalAreaGranite = totalAreaGranite + area;
                    totalCostGranite = totalCostGranite + totalCost;
                    countGranite++;
                }
                else if(stoneCode == 'q')
                {
                    double costQuartz = area * COST_QUARTZ;
                    double totalCost = costQuartz + costFinishing;
                    cout << setw(11) << fixed << showpoint << setprecision(2) << totalCost;
                    totalAreaQuartz = totalAreaQuartz + area;
                    totalCostQuartz = totalCostQuartz + totalCost;
                    countQuartz++;
                }
                
                getline (inputFile, extraData); //eats extra data like name and address
                noErrors++;
            }
            else
            {
                getline (inputFile, extraData);
                recordErrors++;
                cout << "\n";
            }
            totalRecords++;
            cout << "\n";
        }
        inputFile.close();
        cout << "\nCounts: Total Records = " << totalRecords;
        cout << "   Records with Errors = " << recordErrors;
        cout << "   Records without Errors = " << noErrors << endl;
        cout << "\n\t\t  TOTALS (records without errors)" << endl;
        cout << setw(7) << "Stone" << setw(11) << "Count";
        cout << setw(18) << "Square Feet" << setw(16) << "Cost" << endl;
        
        line.assign(70, '-');
        cout << line << endl;
        
        cout <<  " Marble";
        cout << setw(11) << countMarble;
        cout << setw(18) << fixed << showpoint << setprecision(2) << totalAreaMarble;
        cout << setw(20) << fixed << showpoint << setprecision(2) << totalCostMarble << endl;
        
        cout << "Granite";
        cout << setw(11) << countGranite;
        cout << setw(18) << fixed << showpoint << setprecision(2) << totalAreaGranite;
        cout << setw(20) << fixed << showpoint << setprecision(2) << totalCostGranite << endl;
        
        cout << " Quartz";
        cout << setw(11) << countQuartz;
        cout << setw(18) << fixed << showpoint << setprecision(2) << totalAreaQuartz;
        cout << setw(20) << fixed << showpoint << setprecision(2) << totalCostQuartz << endl;
        
        cout << line << endl;
        
        cout << "\nThank you for using Claude\'s Custom Counters, Inc. Calculator." << endl;
    }
    
    return 0;
}
