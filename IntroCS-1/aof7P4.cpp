/*
 * aof7P4.cpp
 *
 * COSC 051 Spring 2016
 * Project #4
 *
 * Due on: APR 13, 2016
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
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
#include <cmath>
using namespace std;



// ******** global constants ********
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




// ********** class declaration *********
// ****                              ****
// **************************************
class CounterTop
{
    friend ostream& operator<<( ostream &os, const CounterTop &rhsObj );
    
    
private:
    //required (you may change identifiers, but do so with caution)
    //you may NOT add any data members to the class declaration
    int orderYear, orderMonth, orderDay;
    int deliveryYear, deliveryMonth, deliveryDay;
    
    char stoneCode;
    
    double length;
    double depth;
    double height;
    
    int lengthEdgesToFinish;
    int depthEdgesToFinish;
    
    string orderNumber;
    string region;
    string fipsStateCode;
    string customerNameAddress;
    
public:
    // required constructors
    CounterTop();
    
    CounterTop(int oYYYY, int oMM, int oDD, int dYYYY, int dMM, int dDD,
               char sCode, double len, double dep, double hei, int lenF, int depF,
               string oNum, string reg, string stCode, string custNameAdd);
    
    CounterTop( const CounterTop &otherObj );
    
    // required basic mutator functions, in-line implementation
    void setStoneCode(char sCode) { stoneCode = sCode; }
    
    void setLength( double len ) { length = len; }
    void setDepth( double dep ) { depth = dep; }
    void setHeight( double hei ) { height = hei; }
    
    void setLenEdgeF( int lenF ) { lengthEdgesToFinish = lenF; }
    void setDepEdgeF( int depF ) { depthEdgesToFinish = depF; }
    
    void setOrderNum( string oNum ) { orderNumber = oNum; }
    void setRegion( string reg ) { region = reg; }
    void setFIPS( string stCode ) { fipsStateCode = stCode; }
    void setCustomerNameAdd( string custNameAdd ) { customerNameAddress = custNameAdd; }
    
    
    //required basic accessor functions, in-line implementation
    char getStoneCode() const { return stoneCode; }
    
    double getLength() const { return length; }
    double getDepth() const { return depth; }
    double getHeight() const { return height; }
    
    int getLenEdgeF() const { return lengthEdgesToFinish; }
    int getDepEdgeF() const { return depthEdgesToFinish; }
    
    string getOrderNum() const { return orderNumber; }
    string getRegion() const { return region; }
    string getFIPS() const { return fipsStateCode; }
    string getCustomerNameAdd() const { return customerNameAddress; }
    
    //required accessor functions that perform more detailed calculations
    void setOrderDate(int yyyy, int mm, int dd);
    void setDeliveryDate(int yyyy, int mm, int dd);
    
    double getCounterTopArea() const;
    double getMaterialRequired() const;
    double getStoneCost() const;
    double getFinishingCost() const;
    double getTotalCost() const;
    

    
}; //END declaration class CounterTop


// ***** Functions prototypes - not in class *****
char displayMenu();
void uploadFile(string fName, bool &loadSuccess, vector<CounterTop> &vCounterTops);
void allDetails(const vector<CounterTop> &vCounterTops);
void orderDetails(const vector<CounterTop> &vCounterTops);
void summaryByStone(const vector<CounterTop> &vCounterTops);
void summaryByRegion(const vector<CounterTop> &vCounterTops);



// ******************************
// ******* ENTERING MAIN ********
// ******************************
int main()
{
    const string exit = "Thank you for using Claude\'s Custom Counters, Inc. Calculator";
    
    vector<CounterTop> counterTop;
    char selection = '?';
    
    cout << "Welcome to Claude\'s Custom Counters, Inc. Calculator." << endl;
    cout << "This application calculates cost and fabrication" << endl;
    cout << "data based on sales data input files.\n" << endl;
    
    while(selection != 'q')
    {
        
        selection = displayMenu();
        
        if (selection == 'u')
        {
            
            string fileName = " ";
            cout << "Please enter the path and name of the file to load: " << endl;
            getline(cin, fileName);
            
            bool fileLoaded;
            
            uploadFile(fileName, fileLoaded, counterTop);
        }
        else if (selection == 'a')
        {
            if(counterTop.empty())
            {
                cout << "Error. Must upload a file.\n" << endl;
            }
            else
            {
                allDetails(counterTop);
            }
        }
        else if (selection == 'o')
        {
            if(counterTop.empty())
            {
                cout << "Error. Must upload a file.\n" << endl;
            }
            else
            {
                orderDetails(counterTop);
            }
            
        }
        else if(selection == 'r')
        {
            if(counterTop.empty())
            {
                cout << "Error. Must upload a file.\n" << endl;
            }
            else
            {
                summaryByRegion(counterTop);
            }
            
        }
        else if(selection == 's')
        {
            if(counterTop.empty())
            {
                cout << "Error. Must upload a file.\n" << endl;
            }
            else
            {
                summaryByStone(counterTop);
            }
            
        }
        
        else if (selection == 'c')
        {
            if(counterTop.empty())
            {
                cout << "Nothing to do, vectors are already empty." << endl;
            }
            else
            {
                counterTop.clear();
                cout << "Successful clear operation.\n" << endl;
            
            }
        }
        
        else if (selection =='q')
        {
            cout << exit << endl;
        }
        
        
    }
    
    
    return 0;
}




/****************************************************************************
 *                                                                          *
 *                     constructor implementation code                      *
 *                                                                          *
 ****************************************************************************/

//default constructor
CounterTop :: CounterTop()
{
    orderYear = 0;
    orderMonth = 0;
    orderDay = 0;
    deliveryYear = 0;
    deliveryMonth = 0;
    deliveryDay = 0;
    
    stoneCode = ' ';
    
    length = 0.0;
    depth = 0.0;
    height = 0.0;
    
    lengthEdgesToFinish = 0;
    depthEdgesToFinish = 0;
    
    orderNumber = " ";
    region = " ";
    fipsStateCode = " ";
    customerNameAddress = " ";
    
}


// constructor with parameters
CounterTop :: CounterTop(int oYYYY, int oMM, int oDD, int dYYYY, int dMM, int dDD,
char sCode, double len, double dep, double hei, int lenF, int depF,
string oNum, string reg, string stCode, string custNameAdd)
{
    orderYear = oYYYY;
    orderMonth = oMM;
    orderDay = oDD;
    deliveryYear = dYYYY;
    deliveryMonth = dMM;
    deliveryDay = dDD;
    
    stoneCode = sCode;
    
    length = len;
    depth = dep;
    height = hei;
    
    lengthEdgesToFinish =lenF;
    depthEdgesToFinish = depF;
    
    orderNumber = oNum;
    region = reg;
    fipsStateCode = stCode;
    customerNameAddress = custNameAdd;
}

//copy constructor
CounterTop :: CounterTop(const CounterTop &otherObj)
{
    orderYear = otherObj.orderYear;
    orderMonth = otherObj.orderMonth;
    orderDay = otherObj.orderDay;
    deliveryYear = otherObj.deliveryYear;
    deliveryMonth = otherObj.deliveryMonth;
    deliveryDay = otherObj.deliveryDay;
    
    stoneCode = otherObj.stoneCode;
    
    length = otherObj.length;
    depth = otherObj.depth;
    height = otherObj.height;
    
    lengthEdgesToFinish = otherObj.lengthEdgesToFinish;
    depthEdgesToFinish = otherObj.depthEdgesToFinish;
    
    orderNumber = otherObj.orderNumber;
    region = otherObj.region;
    fipsStateCode = otherObj.fipsStateCode;
    customerNameAddress = otherObj.customerNameAddress;
}




/****************************************************************************
 *                                                                          *
 *                  mutator member function implementation                  *
 *                                                                          *
 ****************************************************************************/


void CounterTop::setOrderDate(int yyyy, int mm, int dd)
{
    orderYear = yyyy;
    orderMonth = mm;
    orderDay = dd;
}

void CounterTop::setDeliveryDate(int yyyy, int mm, int dd)
{
    deliveryYear = yyyy;
    deliveryMonth = mm;
    deliveryDay = dd;
}




/****************************************************************************
 *                                                                          *
 *                  accessor member function implementation                 *
 *                                                                          *
 ****************************************************************************/

double CounterTop::getCounterTopArea() const
{
    double area = length * height;
    return area;
}

double CounterTop::getMaterialRequired() const
{
    double area = getCounterTopArea();
    double quantityStone = area + WASTAGE_AREA * area;
    quantityStone = ceil(quantityStone);
    
    return quantityStone;
    
}

double CounterTop::getStoneCost() const
{
    double quantityStone = getMaterialRequired();
    double stoneCost;
    
    if(stoneCode == 'm')
    {
        stoneCost = quantityStone * COST_MARBLE;
    }
    else if(stoneCode == 'g')
    {
        stoneCost = quantityStone * COST_GRANITE;
    }
    else if(stoneCode == 'q')
    {
        stoneCost = quantityStone * COST_QUARTZ;
    }
    
    return stoneCost;

}

double CounterTop::getFinishingCost() const
{
    int depFin = depthEdgesToFinish;
    double dep = depth;
    double costFinishedDepth = depFin * dep * COST_PER_FOOT;
   
    int lenFin = lengthEdgesToFinish;
    double len = length;
    double costFinishedLength = lenFin * len * COST_PER_FOOT;

    double totalFinishingCost = costFinishedDepth + costFinishedLength;
    
    return totalFinishingCost;
}

double CounterTop::getTotalCost() const
{
    double stoneCost = getStoneCost();
    double finishingCost = getFinishingCost();
    double totalCost = stoneCost + finishingCost;
    
    return totalCost;
}






/****************************************************************************
 *                                                                          *
 *                   class Widget non-member functions                      *
 *                                                                          *
 ****************************************************************************/

ostream& operator<<( ostream &os, const CounterTop &rhsObj)
{
    double material = rhsObj.getMaterialRequired();
    double totalCost = rhsObj.getTotalCost();
    
    os << setw(13) << rhsObj.orderNumber << setw(8) << rhsObj.region << setw(3) << rhsObj.stoneCode;
    os << setw(7) << fixed << showpoint << setprecision(2) << rhsObj.length;
    os << setw(7) << rhsObj.depth << setw(7) << rhsObj.height;
    os << setw(3) << rhsObj.lengthEdgesToFinish << setw(3) << rhsObj.depthEdgesToFinish;
    os << setw(8) << material << setw(10) << totalCost;
    
    return os;
}




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
        cout << "\n";
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
            menuChoice != 'r' && menuChoice != 'c' &&
            menuChoice != 's'&& menuChoice != 'q')
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





void uploadFile(string fName, bool &loadSuccess, vector<CounterTop> &vCounterTops)

{
    
    ifstream inputFile;
    inputFile.open(fName.c_str());
    
    double sizeInitial;
    sizeInitial = vCounterTops.size();
    
    if(inputFile)
    {
        string columnHeadings = " ";
        
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
        string stCode = " ";
        string custName = " ";
        
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
            getline(inputFile, custName);
            
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
                if (stoneCode == 'm')
                {
                    stCode = "marble";
                }
                else if (stoneCode == 'g')
                {
                    stCode = "granite";
                }
                else if (stoneCode == 'q')
                {
                    stCode = "quartz";
                }
                    
                vCounterTops.push_back(CounterTop (orderY, orderM, orderD, deliveryY, deliveryM, deliveryD,stoneCode, length, depth, height, finishedLength, finishedDepth, orderNumber, region, stCode, custName));
                
                noErrors++;
            }
            else
            {
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
        cout << vCounterTops.size() << " total records now loaded.\n" << endl;
    }
    
    double sizeFinal;
    sizeFinal = vCounterTops.size();
    if(sizeInitial == sizeFinal)
    {
        cout << "Error opening file\n" << endl;
        loadSuccess = false;
    }
    else if (sizeFinal > sizeInitial)
    {
        loadSuccess = true;
    }
    else
    {
        cout << "Error opening file\n" << endl;
        loadSuccess = false;
    }
} ;





void allDetails(const vector<CounterTop> &vCounterTops)
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
    
    for(int i = 0; i < vCounterTops.size(); i++)
    {
        cout << vCounterTops.at(i) << endl;
    }
    
    cout << "\n\n";
}


void orderDetails(const vector<CounterTop> &vCounterTops)
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
    
    for(int i = 0; i < vCounterTops.size(); i++)
    {
        if(vCounterTops.at(i).getOrderNum() == findOrder)
        {
            found = true;
            cout << vCounterTops.at(i) << endl;
        }
    }
    if(!found)
    {
        cout << "Sorry, order number, " << findOrder << " not found..." << endl;
    }
    cout << "\n\n";
    
}



void summaryByStone(const vector<CounterTop> &vCounterTops)
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
    
    
    for(int i = 0; i< vCounterTops.size(); i++)
    {
        double area = vCounterTops.at(i).getMaterialRequired();
        totalCost = vCounterTops.at(i).getTotalCost();
        
        if(vCounterTops.at(i).getStoneCode()  == 'm')
        {
            marbleCount++;
            marbleArea += area;
            marbleCost += totalCost;
        }
        else if (vCounterTops.at(i).getStoneCode() == 'g')
        {
            graniteCount++;
            graniteArea += area;
            graniteCost += totalCost;
        }
        else if (vCounterTops.at(i).getStoneCode() == 'q')
        {
            quartzCount++;
            quartzArea += area;
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
}




void summaryByRegion(const vector<CounterTop> &vCounterTops)
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
    
    for(int i = 0; i < vCounterTops.size(); i++)
    {
        double area = vCounterTops.at(i).getMaterialRequired();
        double totalCost = vCounterTops.at(i).getTotalCost();
        
        if(vCounterTops.at(i).getRegion() == "North")
        {
            countNorth++;
            sqFtNorth += area;
            costNorth += totalCost;
        }
        else if(vCounterTops.at(i).getRegion() == "South")
        {
            countSouth++;
            sqFtSouth += area;
            costSouth += totalCost;
        }
        else if(vCounterTops.at(i).getRegion() == "East")
        {
            countEast++;
            sqFtEast += area;
            costEast += totalCost;
        }
        else if(vCounterTops.at(i).getRegion() == "West")
        {
            countWest++;
            sqFtWest += area;
            costWest += totalCost;
        }
        else if (vCounterTops.at(i).getRegion() == "Other")
        {
            countOther++;
            sqFtOther += area;
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
    
}

