/*
 * aof7P3.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #3
 *
 *  Due on: MAR 30, 2016
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
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;

//*******global constants*******
const double MIN_LENGTH = 5.00;
const double MAX_LENGTH = 25.00;
const int MIN_FINISHED_EDGES = 0;
const int MAX_FINISHED_EDGES = 2;
const double MIN_DEPTH = 5.00;
const double MIN_HEIGHT_RATIO = .58;
const double MAX_HEIGHT_RATIO = .80;
const double MONTHS_PER_YEAR = 12;

const double COST_MARBLE = 92.99;
const double COST_GRANITE = 78.99;
const double COST_QUARTZ = 56.99;
const double WASTAGE_AREA = .26;
const double COST_PER_FOOT = 4.99;


// ******* function prototypes *******
char displayMenu();

void uploadFile(string fName, bool &loadSuccess, vector<char> &sCode, vector<double> &len,
                vector<double> &dep, vector<double> &hei,vector<int> &lenF,
                vector<int> &depF, vector<string> &oNum, vector<string> &reg);

void allDetails(const vector<char> &sCode, const vector<double> &len,
                const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF,
                const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

void orderDetails(const vector<char> &sCode, const vector<double> &len,
                const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF,
                const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

void summaryByRegion(const vector<char> &sCode, const vector<double> &len,
                    const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF,
                    const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

void summaryByStone(const vector<char> &sCode, const vector<double> &len,
                  const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF,
                  const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg);

bool clearAllVectors(vector<char> &sCode, vector<double> &len,
                     vector<double> &dep, vector<double> &hei,vector<int> &lenF,
                     vector<int> &depF, vector<string> &oNum, vector<string> &reg);




//******* ENTERING MAIN *******
int main()
{
    const string exit = "Thank you for using Claude\'s Custom Counters, Inc. Calculator";
    char selection = '?';
    
    vector<char>stoneC;
    vector<double>leng;
    vector<double> dept;
    vector<double> heig;
    vector<int>lengthEF;
    vector<int>depthEF;
    vector<string>ordNumber;
    vector<string>regn;
    
    cout << "Welcome to Claude\'s Custom Counters, Inc. Calculator." << endl;
    cout << "This application calculates cost and fabrication" << endl;
    cout << "data based on sales dat input files.\n" << endl;
    
    while(selection != 'q')
    {

        
        selection = displayMenu();
        
        if (selection == 'u')
            {
                
                string fileName = " ";
                cout << "Please enter the path and name of the file to load: " << endl;
                getline(cin, fileName);
                
                bool fileLoaded;

                uploadFile(fileName, fileLoaded,  stoneC, leng, dept, heig,
                           lengthEF, depthEF, ordNumber, regn);
            }
        else if (selection == 'a')
            {
                if(stoneC.empty())
                {
                    cout << "Error. Must upload a file.\n" << endl;
                }
                else
                {
                    allDetails(stoneC, leng, dept, heig, lengthEF, depthEF, ordNumber, regn);
                }
            }
         else if (selection == 'o')
            {
                if(stoneC.empty())
                {
                    cout << "Error. Must upload a file.\n" << endl;
                }
                else
                {
                    orderDetails(stoneC, leng, dept, heig, lengthEF, depthEF, ordNumber, regn);
                }
                
            }
         else if(selection == 'r')
            {
                if(stoneC.empty())
                {
                    cout << "Error. Must upload a file.\n" << endl;
                }
                else
                {
                    summaryByRegion(stoneC, leng, dept, heig, lengthEF, depthEF, ordNumber, regn);
                }
   
            }
          else if(selection == 's')
            {
                if(stoneC.empty())
                {
                    cout << "Error. Must upload a file.\n" << endl;
                }
                else
                {
                    summaryByStone(stoneC, leng, dept, heig, lengthEF, depthEF, ordNumber, regn);
                }
     
            }
        else if (selection == 'c')
            {
                
                clearAllVectors(stoneC, leng, dept, heig,
                                lengthEF, depthEF, ordNumber, regn);

            }
        
        else if (selection =='q')
            {
                cout << exit << endl;
            }
    
        
    }
    
    return 0;
}






//********** function definitions **********
char displayMenu( )
{
    const string optionU = "Upoload a regional sales data file";
    const string optionA = "display details (All loaded data)";
    const string optionO = "list details for specific Order number";
    const string optionR = "display summary by Region";
    const string optionS = "display summary by Stone code";
    const string optionC = "Clear all vectors";
    const string optionQ = "Quit";
    
    char menuChoice = '?';
    bool validValue = true;
    do
    {
    cout << setw(45) << optionU << setw(5) << "U" << endl;
    cout << setw(45) << optionA << setw(5) << "A" << endl;
    cout << setw(45) << optionO << setw(5) << "O" << endl;
    cout << setw(45) << optionR << setw(5) << "R" << endl;
    cout << setw(45) << optionS << setw(5) << "S" << endl;
    cout << setw(45) << optionC << setw(5) << "C" << endl;
    cout << setw(45) << optionQ << setw(5) << "Q" << endl;
    cout << "\n";
    cout << "Please enter your choice: ";
    cin.get(menuChoice);
    cin.ignore(80, '\n');
    menuChoice = tolower(menuChoice);
        if (menuChoice != 'u' && menuChoice != 'a' && menuChoice != 'o' &&
             menuChoice != 'r' && menuChoice != 's'&&
            menuChoice != 'c' && menuChoice != 'q')
        {
            cout << "Your selection is not a valid option\n" << endl;
            validValue = false;
        }
        else
        {
            validValue = true;
        }
    } while(!validValue);
    
    return menuChoice;
} ;





void uploadFile(string fName, bool &loadSuccess, vector<char> &sCode,
                vector<double> &len, vector<double> &dep, vector<double> &hei,
                vector<int> &lenF, vector<int> &depF,
                vector<string> &oNum, vector<string> &reg)
{
    
    ifstream inputFile;
    inputFile.open(fName.c_str());
    
    if(inputFile)
    {
        string continueProccess = "File processing will continue.";
        string columnHeadings = " ";
        string extraData = " ";
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
        string orderNumber = " ";
        string region = " ";
        int totalRecords = 0;
        int recordErrors = 0;
        int noErrors = 0;
        
        int errSameDate = 0;
        int errDateFar = 0;
        int errStone = 0;
        int errDepth = 0;
        int errHeight = 0;
        int errLength = 0;
        int errLenEF = 0;
        int errDepEF = 0;
        int multipleErrors = 0;
        int numberErrors = 0;
        int totalErrors;
        bool canContinue = true;
        
        
        getline (inputFile, columnHeadings);
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
        line.assign(83, '-');
        cout << line << endl;
        
        while(inputFile >> orderY >> ch >> orderM >> ch >> orderD)
        {
            numberErrors = 0;
            canContinue = true;
            
            inputFile >> deliveryY >> ch >> deliveryM >> ch >> deliveryD;
            inputFile >> stoneCode;
            inputFile >> length;
            inputFile >> depth;
            inputFile >> height;
            inputFile >> finishedLength;
            inputFile >> finishedDepth;
            inputFile >> orderNumber;
            inputFile >> region;
            getline(inputFile, extraData);
            
            cout << orderY << "/";
            cout << setfill('0') << setw(2) << orderM << "/";
            cout << setw(2) << orderD << "  ";
            cout << deliveryY << "/";
            cout << setw(2) << deliveryM << "/";
            cout << setw(2) << deliveryD << "  ";
            cout << setfill(' ');
            
            cout << stoneCode;
            cout << setw(7) << fixed << showpoint << setprecision(2) << length;
            cout << setw(7)  << depth << setw(7) << height;
            cout << setw(4) << finishedLength << setw(4) << finishedDepth;
            
            
            //check data for errors
            if(deliveryY == orderY && deliveryM == orderM && deliveryD == orderD)
            {
                
                cout << "\n\tERROR:  order date and delivery date are equal.";
                errSameDate++;
                numberErrors++;
                canContinue = false;
            }
            if((((deliveryY-orderY)*MONTHS_PER_YEAR)+deliveryM) - orderM > 4)
            {
                cout << "\n\tERROR:  delivery date is too far from order date.";
                errDateFar++;
                numberErrors++;
                canContinue = false;
            }
            stoneCode = tolower(stoneCode);
            if(stoneCode != 'm'  && stoneCode != 'g' && stoneCode != 'q')
            {
                cout << "\n\tERROR:  stone code is not a valid value.";
                errStone++;
                numberErrors++;
                canContinue = false;
            }
            if(length < MIN_LENGTH || length > MAX_LENGTH)
            {
                cout << "\n\tERROR:  Invalid length.";
                errLength++;
                numberErrors++;
                canContinue = false;
            }
            if (depth < MIN_DEPTH || depth > length || depth > MAX_LENGTH)
            {
                cout << "\n\tERROR:  Invalid depth.";
                errDepth++;
                numberErrors++;
                canContinue = false;
            }
            double hMin = MIN_HEIGHT_RATIO * depth;
            double hMax = MAX_HEIGHT_RATIO * depth;
            if (height < hMin || height > hMax)
            {
                cout << "\n\tERROR:  Invalid height.";
                errHeight++;
                numberErrors++;
                canContinue = false;
            }
            if(finishedLength < MIN_FINISHED_EDGES || finishedLength > MAX_FINISHED_EDGES)
            {
                cout << "\n\tERROR:  Invalid number of length edges to be finished.";
                errLenEF++;
                numberErrors++;
                canContinue = false;
            }
            if (finishedDepth < MIN_FINISHED_EDGES || finishedDepth > MAX_FINISHED_EDGES)
            {
                cout << "\n\tERROR:  Invalid number of depth edges to be finished.";
                errDepEF++;
                numberErrors++;
                canContinue = false;
            }
            
            
            if(canContinue)
            {
                sCode.push_back(stoneCode);
                len.push_back(length);
                dep.push_back(depth);
                hei.push_back(height);
                lenF.push_back(finishedLength);
                depF.push_back(finishedDepth);
                oNum.push_back(orderNumber);
                reg.push_back(region);
                
                loadSuccess = true; //succesfully loaded data and stored in vectors
                noErrors++;
            }
            else
            {
                cout << "\n" << continueProccess;
                recordErrors++;
                if(numberErrors > 1)
                {
                    multipleErrors++;
                }
                cout << "\n";
            }
            
            totalRecords++;
            cout << "\n";
            
        }
        inputFile.close();
        
        totalErrors = (errSameDate + errDateFar + errStone + errLength
                       + errDepth + errHeight + errLenEF + errDepEF);
        
        //  ***output the counts
        cout << "\n\n" << line.assign(50, '*') << endl;
        cout << setw(30) << "Count of overall errors:" << endl;
        cout << line.assign(50, '*') << "\n" << endl;
        cout << setw(6) << recordErrors << " - records with errors." << endl;
        cout << setw(6) << noErrors << " - records without errors." << endl;
        cout << line.assign(50,'-') << endl;
        cout << setw(6) << totalRecords << " - total records." << endl;
        
        cout << "\n\n" << line.assign(50, '*') << endl;
        cout << setw(30) << "Count of individual errors:" << endl;
        cout << line.assign(50, '*') << "\n" << endl;
        cout << setw(6) << errSameDate << " - order date and delivery date same." << endl;
        cout << setw(6) << errDateFar << " - delivery date too far in future." << endl;
        cout << setw(6) << errStone << " - stone code not valid." << endl;
        cout << setw(6) << errLength << " - length not valid." << endl;
        cout << setw(6) << errDepth << " - depth not valid." << endl;
        cout << setw(6) << errHeight << " - height not valid." << endl;
        cout << setw(6) << errLenEF << " - length edges to finish not valid." << endl;
        cout << setw(6) << errDepEF << " - depth edges to finish not valid." << endl;
        cout << line.assign(50,'-') << endl;
        cout << setw(6) << totalErrors << " - total count of all errors in all records." << endl;
        cout << setw(6) << multipleErrors << " - count of records with multiple errors.\n" << endl;
        
        cout << noErrors << " added to vectors, ";
        cout << sCode.size() << " total records now loaded.\n" << endl;
        

    }
    else
    {
        cout << "Error opening file\n" << endl;
        loadSuccess = false;
    }
    
} ;





void allDetails(const vector<char> &sCode, const vector<double> &len,
                const vector<double> &dep, const vector<double> &hei, const vector<int> &lenF,
                const vector<int> &depF, const vector<string> &oNum, const vector<string> &reg)
{
    cout << setw(13) << "Order" << setw(11) << "S";
    cout << setw(24) << "L" << setw(3) << "D";
    cout << setw(8) << "Sq."<< setw(10) << "Total" << endl;
    
    cout << setw(13) << "Number" << setw(8) << "Region" << setw(3) << "C";
    cout << setw(7) << "Len."<< setw(7) << "Dep." << setw(7) << "Hei.";
    cout << setw(3) << "E" << setw(3) << "E";
    cout << setw(8) << "Ft."<< setw(10) << "Cost" << endl;
    string line;
    line.assign(83, '-');
    cout << line << "\n" << endl;
    
   for(int i = 0; i < sCode.size(); i++)
    {
        cout << setw(13) << oNum.at(i);
        cout << setw(8) << reg.at(i);
        cout << setw(3) << sCode.at(i);
        cout << setw(7) << fixed << showpoint << setprecision(2) << len.at(i);
        cout << setw(7) << dep.at(i);
        cout << setw(7) << hei.at(i);
        cout << setw(3) << lenF.at(i) << setw(3) << depF.at(i);
        
        
        double costFinishedDepth = depF.at(i) * dep.at(i) * COST_PER_FOOT;
        double costFinishedLength = lenF.at(i) * len.at(i) * COST_PER_FOOT;
        double costFinishing = costFinishedDepth + costFinishedLength;
        double area = len.at(i) * hei.at(i);
        
        area = area + WASTAGE_AREA * area;
        area = ceil(area);         // rounds up
        cout << setw(8) << area;
        
        
        if(sCode.at(i) == 'm')
        {
            double totalCost = area * COST_MARBLE + costFinishing;
            cout << setw(10) << totalCost << endl;
        }
        
        else if(sCode.at(i) == 'g')
        {
            double totalCost = area * COST_GRANITE + costFinishing;
            cout << setw(10) << totalCost << endl;
        }
        else if(sCode.at(i) == 'q')
        {
            double totalCost = area * COST_QUARTZ + costFinishing;
            cout << setw(10) << totalCost << endl;
            
        }
    }
    cout << "\n\n";
} ;





void orderDetails(const vector<char> &sCode, const vector<double> &len,
                  const vector<double> &dep, const vector<double> &hei,
                  const vector<int> &lenF, const vector<int> &depF,
                  const vector<string> &oNum, const vector<string> &reg)
{
    string findOrder;
    bool found = false;
    
    cout << "Please enter an order number to find: " << endl;
    getline(cin, findOrder);
    
    cout << setw(13) << "Order" << setw(11) << "S";
    cout << setw(24) << "L" << setw(3) << "D";
    cout << setw(8) << "Sq."<< setw(10) << "Total" << endl;
    
    cout << setw(13) << "Number" << setw(8) << "Region" << setw(3) << "C";
    cout << setw(7) << "Len."<< setw(7) << "Dep." << setw(7) << "Hei.";
    cout << setw(3) << "E" << setw(3) << "E";
    cout << setw(8) << "Ft."<< setw(10) << "Cost" << endl;
    string line;
    line.assign(83, '-');
    cout << line << endl;
    
    for(int i = 0; i < sCode.size(); i++)
    {
        if(oNum.at(i) == findOrder)
        {
            found = true;
            cout << setw(13) << oNum.at(i);
            cout << setw(8) << reg.at(i);
            cout << setw(3) << sCode.at(i);
            cout << setw(7) << fixed << showpoint << setprecision(2) << len.at(i);
            cout << setw(7) << dep.at(i);
            cout << setw(7) << hei.at(i);
            cout << setw(3) << lenF.at(i) << setw(3) << depF.at(i);
            
            double costFinishedDepth = depF.at(i) * dep.at(i) * COST_PER_FOOT;
            double costFinishedLength = lenF.at(i) * len.at(i) * COST_PER_FOOT;
            double costFinishing = costFinishedDepth + costFinishedLength;
            double area = len.at(i) * hei.at(i);
            area = area + WASTAGE_AREA * area;
            area = ceil(area);         // rounds up
            cout << setw(8) << area;
            
            if(sCode.at(i) == 'm')
            {
                double totalCost = area * COST_MARBLE + costFinishing;
                cout << setw(10) << totalCost << endl;
            }
            
            else if(sCode.at(i) == 'g')
            {
                double totalCost = area * COST_GRANITE + costFinishing;
                cout << setw(10) << totalCost << endl;
            }
            else if(sCode.at(i) == 'q')
            {
                double totalCost = area * COST_QUARTZ + costFinishing;
                cout << setw(10) << totalCost << endl;
                
            }
        }
    }
    if(!found)
    {
        cout << "Sorry, order number, " << findOrder << " not found..." << endl;
    }
    
    cout << "\n\n";
    
} ;






void summaryByRegion(const vector<char> &sCode, const vector<double> &len,
                    const vector<double> &dep, const vector<double> &hei,
                    const vector<int> &lenF, const vector<int> &depF,
                    const vector<string> &oNum, const vector<string> &reg)
{
    cout << "\n";
    cout << setw(35) << "TOTALS (all loaded files)" << endl;
    cout << setw(8) << "Region" << setw(8) << "Count";
    cout << setw(15) << "Square Feet" << setw(13) << "Cost\n";
    string line;
    line.assign(60, '-');
    cout << line  << endl;
    
    int countNorth = 0;
    double sqFtNorth = 0.0;
    double costNorth = 0.0;
    int countSouth = 0;
    double sqFtSouth = 0.0;
    double costSouth = 0.0;
    
    int countEast = 0;
    double sqFtEast = 0.0;
    double costEast = 0.0;
    int countWest = 0;
    double sqFtWest = 0.0;
    double costWest = 0.0;
    
    int countOther = 0;
    double sqFtOther = 0.0;
    double costOther = 0.0;
    
    
    for(int i = 0; i < sCode.size(); i++)
    {
        
        double costFinishedDepth = depF.at(i) * dep.at(i) * COST_PER_FOOT;
        double costFinishedLength = lenF.at(i) * len.at(i) * COST_PER_FOOT;
        double costFinishing = costFinishedDepth + costFinishedLength;
        double area = len.at(i) * hei.at(i);
        double totalCost;
        area = area + WASTAGE_AREA * area;
        area = ceil(area);         // rounds up
        
        if(reg.at(i) == "North")
        {
            countNorth++;
            sqFtNorth += area;
            
            if(sCode.at(i) == 'm')
            {
                totalCost = area * COST_MARBLE + costFinishing;
            }
            
            else if(sCode.at(i) == 'g')
            {
                totalCost = area * COST_GRANITE + costFinishing;
            }
            else if(sCode.at(i) == 'q')
            {
                totalCost = area * COST_QUARTZ + costFinishing;
            }
            
            costNorth += totalCost;
            
        }
        else if (reg.at(i) == "South")
        {
            countSouth++;
            sqFtSouth += area;
            
            if(sCode.at(i) == 'm')
            {
                totalCost = area * COST_MARBLE + costFinishing;
            }
            
            else if(sCode.at(i) == 'g')
            {
                totalCost = area * COST_GRANITE + costFinishing;
            }
            else if(sCode.at(i) == 'q')
            {
                totalCost = area * COST_QUARTZ + costFinishing;
            }
            
            costSouth += totalCost;
            
        }
        else if (reg.at(i) == "East")
        {
            countEast++;
            sqFtEast += area;
            
            if(sCode.at(i) == 'm')
            {
                totalCost = area * COST_MARBLE + costFinishing;
            }
            
            else if(sCode.at(i) == 'g')
            {
                totalCost = area * COST_GRANITE + costFinishing;
            }
            else if(sCode.at(i) == 'q')
            {
                totalCost = area * COST_QUARTZ + costFinishing;
            }
            
            costEast += totalCost;
            
        }
        else if (reg.at(i) == "West")
        {
            countWest++;
            sqFtWest += area;
            
            if(sCode.at(i) == 'm')
            {
                totalCost = area * COST_MARBLE + costFinishing;
            }
            
            else if(sCode.at(i) == 'g')
            {
                totalCost = area * COST_GRANITE + costFinishing;
            }
            else if(sCode.at(i) == 'q')
            {
                totalCost = area * COST_QUARTZ + costFinishing;
            }
            
            costWest += totalCost;
            
        }
        else if (reg.at(i) == "Other")
        {
            countOther++;
            sqFtOther += area;
            
            if(sCode.at(i) == 'm')
            {
                totalCost = area * COST_MARBLE + costFinishing;
            }
            
            else if(sCode.at(i) == 'g')
            {
                totalCost = area * COST_GRANITE + costFinishing;
            }
            else if(sCode.at(i) == 'q')
            {
                totalCost = area * COST_QUARTZ + costFinishing;
            }
            
            costOther += totalCost;
            
        }
    }
    
    cout << setw(8) << "North" << setw(8) << countNorth;
    cout << setw(15) << fixed << showpoint << setprecision(2) << sqFtNorth;
    cout << setw(15) << costNorth << endl;
    
    cout << setw(8) << "South" << setw(8) << countSouth;
    cout << setw(15) << fixed << showpoint << setprecision(2) << sqFtSouth;
    cout << setw(15) << costSouth << endl;
    
    cout << setw(8) << "East" << setw(8) << countEast;
    cout << setw(15) << fixed << showpoint << setprecision(2) << sqFtEast;
    cout << setw(15) << costEast << endl;
    
    cout << setw(8) << "West" << setw(8) << countWest;
    cout << setw(15) << fixed << showpoint << setprecision(2) << sqFtWest;
    cout << setw(15) << costWest << endl;
    
    cout << setw(8) << "Other" << setw(8) << countOther;
    cout << setw(15) << fixed << showpoint << setprecision(2) << sqFtOther;
    cout << setw(15) << costOther << endl;
    
    cout << line  << endl;
    cout << "\n\n";
} ;






void summaryByStone(const vector<char> &sCode, const vector<double> &len,
                    const vector<double> &dep, const vector<double> &hei,
                    const vector<int> &lenF, const vector<int> &depF,
                    const vector<string> &oNum, const vector<string> &reg)
{
    cout << "\n" << setw(35) << "TOTALS (all loaded files)" << endl;
    cout << setw(8) << "Stone" << setw(8) << "Count";
    cout << setw(15) << "Square Feet" << setw(13) << "Cost\n";
    string line;
    line.assign(60, '-');
    cout << line  << endl;
    double totalCost;
    
    int marbleCount = 0;
    double marbleArea = 0.0;
    double marbleCost = 0.0;
    
    int graniteCount = 0;
    double graniteArea = 0.0;
    double graniteCost = 0.0;
    
    int quartzCount = 0;
    double quartzArea = 0.0;
    double quartzCost = 0.0;
    
    
    for(int i = 0; i < sCode.size(); i++)
    {
        
        double costFinishedDepth = depF.at(i) * dep.at(i) * COST_PER_FOOT;
        double costFinishedLength = lenF.at(i) * len.at(i) * COST_PER_FOOT;
        double costFinishing = costFinishedDepth + costFinishedLength;
        double area = len.at(i) * hei.at(i);
        area = area + WASTAGE_AREA * area;
        area = ceil(area);
        
        if(sCode.at(i) == 'm')
        {
            marbleCount++;
            marbleArea += area;
            totalCost = area * COST_MARBLE + costFinishing;
            marbleCost += totalCost;
        }
        else if(sCode.at(i) == 'g')
        {
            graniteCount++;
            graniteArea += area;
            totalCost = area * COST_GRANITE + costFinishing;
            graniteCost += totalCost;
        }
        else if(sCode.at(i) == 'q')
        {
            quartzCount++;
            quartzArea += area;
            totalCost = area * COST_QUARTZ + costFinishing;
            quartzCost += totalCost;
        }
        
    }
    
    cout << setw(8) << "Marble" << setw(8) << marbleCount;
    cout << setw(15) << fixed << showpoint << setprecision(2) << marbleArea;
    cout << setw(15) << marbleCost << endl;
    
    cout << setw(8) << "Granite" << setw(8) << graniteCount;
    cout << setw(15) << graniteArea << setw(15) << graniteCost << endl;
    
    cout << setw(8) << "Quartz" << setw(8) << quartzCount;
    cout << setw(15) << quartzArea << setw(15) << quartzCost << endl;
    
    cout << line  << endl;
    cout << "\n\n";
};



bool clearAllVectors(vector<char> &sCode, vector<double> &len,
                     vector<double> &dep, vector<double> &hei,
                     vector<int> &lenF,vector<int> &depF,
                     vector<string> &oNum, vector<string> &reg)
{
    bool success = true;
    
    if(sCode.empty())
    {
        success = false;
        cout << "Nothing to do, vectors are already empty." << endl;
        
    }
    else
    {
        success = true;
        
        sCode.clear();
        len.clear();
        dep.clear();
        hei.clear();
        lenF.clear();
        depF.clear();
        oNum.clear();
        reg.clear();
        
        cout << "All vectors have been emptied of data.\n" << endl;
    }
    
    return success;
} ;

