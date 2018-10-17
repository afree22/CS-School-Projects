/*
 *  aof7P5.cpp
 *
 *  COSC 051 Spring 2016
 *  Project #5
 *
 *  Due on: April 27, 2016
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
#include <cmath>
using namespace std;


// ****** global constants ******
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


/****************************************************************************
 *                                                                          *
 *                         Counter Top Declaration                          *
 *                                                                          *
 ****************************************************************************/
class CounterTop
{
    //overloaded stream insertion operator
    friend ostream& operator<<( ostream &os, const CounterTop &rhsObj );
    
private:
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
    CounterTop *next;
    
public:

    CounterTop();
    CounterTop(int oYYYY, int oMM, int oDD, int dYYYY, int dMM, int dDD,
               char sCode, double len, double dep, double hei, int lenF, int depF,
               string oNum, string reg, string stCode, string custNameAdd,
               CounterTop *ctPtr = NULL);
    CounterTop( const CounterTop &otherObj );
    
    CounterTop operator=(const CounterTop &rhsObj);
    ~CounterTop(); //new for P5 (may not be in-line)
    
    CounterTop *getNext() {return this->next;}
    void setNext( CounterTop *cTopPtr ) {this->next = cTopPtr;}
    
    
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
    
    // other functions, more detailed calculations
    double getCounterTopArea() const;
    double getMaterialRequired() const;
    double getStoneCost() const;
    double getFinishingCost() const;
    double getTotalCost() const;
};

// ***** Stand Alone Function Prototypes ****
void uploadFile(string fName, bool &loadSuccess, unsigned long &objCount, CounterTop* &llCtop);
void summaryByStone( unsigned long objCount, CounterTop* llCtop );
void summaryByRegion( unsigned long objCount, CounterTop* llCtop );
void clearLL( unsigned long &objCount, CounterTop* &llCtop );


/****************************************************************************
 *                                                                          *
 *                          Entering Main                                   *
 *                                                                          *
 ****************************************************************************/

int main(int argc, const char * argv[])
{
    CounterTop *llCounterTopList = NULL;
    unsigned long cTopCount = 0;
    
    bool loadSuccess = false;
    int fileCount = 0;
    
    string inputFileName = " ";
    ifstream inFile;
    
    if ( argc < 2 )
    {
        cout << "Not enough command line arguments, please pass the complete path and name \n";
        cout << "of one of the \"All\" input data files as a command line argument.\n";
        cout << "Test cannot continue... Goodbye\n";
        cout << endl;
    }
    else
    {
        
        inputFileName = argv[1];
        inFile.open(inputFileName.c_str());
        
        if (!inFile)
        {
            cout << "ERROR - The input file:\n";
            cout << inputFileName << endl;
            cout << "Failed to open, the program cannot continue... Goodbye." << endl;
        }
        
        else
        {
            loadSuccess = false;
            fileCount = 0;
            
            cTopCount = 0;
            llCounterTopList = NULL;
            
            //load test data using uploadFile function
            
            cout << "calling uploadFile function\n" << endl;
            
            uploadFile( inputFileName, loadSuccess, cTopCount, llCounterTopList);
            
            //if uploadFile function successfully processed the file data,
            //then increment the count of files loaded, and run reports
            
            if (cTopCount > 0)
            {
                fileCount++;
                cout << "calling function summaryByStone\n" << endl;
                
                summaryByStone(cTopCount, llCounterTopList);
                
                cout << endl;
                
                cout << "calling function summaryByRegion\n" << endl;
                
                summaryByRegion(cTopCount, llCounterTopList);
            }
            else
            {
                cout << "ERROR - something went wrong in the uploadFile function." << endl;
            }
            
            //deallocate all deallocated memory
            
            cout << "calling clearLL function\n" << endl;
            clearLL(cTopCount, llCounterTopList);
            cout << "\t" << cTopCount << " objects are on the linked list.\n" << endl;
            fileCount = 0;
            
            if ( llCounterTopList != NULL )
            {
                cout << "ERROR - Something does not seem correct\n";
                cout << "        after the clearLL function executes,\n";
                cout << "        the linked list should be empty and\n";
                cout << "        the pointer keeping track of the list\n";
                cout << "        head should be pointing to NULL.\n";
                cout << endl;
                
            }
            
        }
        
    }
    return 0;
}





/****************************************************************************
 *                                                                          *
 *                      Constructors / Destructors                          *
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

//constructor with parameters
CounterTop :: CounterTop(int oYYYY, int oMM, int oDD, int dYYYY, int dMM, int dDD,
                             char sCode, double len, double dep, double hei, int lenF, int depF,
                             string oNum, string reg, string stCode, string custNameAdd,
                             CounterTop *ctPtr)
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
    next = ctPtr;
}

// Copy Constructor
CounterTop :: CounterTop(const CounterTop &otherObj)
{
    this->orderYear = otherObj.orderYear;
    this->orderMonth = otherObj.orderMonth;
    this->orderDay = otherObj.orderDay;
    this->deliveryYear = otherObj.deliveryYear;
    this->deliveryMonth = otherObj.deliveryMonth;
    this->deliveryDay = otherObj.deliveryDay;
    
    this->stoneCode = otherObj.stoneCode;
    
    this->length = otherObj.length;
    this->depth = otherObj.depth;
    this->height = otherObj.height;
    
    this->lengthEdgesToFinish = otherObj.lengthEdgesToFinish;
    this->depthEdgesToFinish = otherObj.depthEdgesToFinish;
    
    this->orderNumber = otherObj.orderNumber;
    this->region = otherObj.region;
    this->fipsStateCode = otherObj.fipsStateCode;
    this->customerNameAddress = otherObj.customerNameAddress;
    
    this->next = NULL;
    
}



CounterTop::~CounterTop()
{
    //destructor does not have much to do
    
    
} //END destructor




/****************************************************************************
 *                                                                          *
 *                         Overloaded Functions                             *
 *                                                                          *
 ****************************************************************************/

// Overloaded Assignment
CounterTop CounterTop :: operator=(const CounterTop &rhsObj)
{
    this->orderYear = rhsObj.orderYear;
    this->orderMonth = rhsObj.orderMonth;
    this->orderDay = rhsObj.orderDay;
    this->deliveryYear = rhsObj.deliveryYear;
    this->deliveryMonth = rhsObj.deliveryMonth;
    this->deliveryDay = rhsObj.deliveryDay;
    
    this->stoneCode = rhsObj.stoneCode;
    
    this->length = rhsObj.length;
    this->depth = rhsObj.depth;
    this->height = rhsObj.height;
    
    this->lengthEdgesToFinish = rhsObj.lengthEdgesToFinish;
    this->depthEdgesToFinish = rhsObj.depthEdgesToFinish;
    
    this->orderNumber = rhsObj.orderNumber;
    this->region = rhsObj.region;
    this->fipsStateCode = rhsObj.fipsStateCode;
    this->customerNameAddress = rhsObj.customerNameAddress;
    this->next = rhsObj.next;
    
    return CounterTop(orderYear, orderMonth, orderDay, deliveryYear,
                      deliveryMonth, deliveryDay, stoneCode, length,
                      depth, height, lengthEdgesToFinish,
                      depthEdgesToFinish, orderNumber, region,
                      fipsStateCode, customerNameAddress, next);
    
}

ostream& operator<<( ostream &os, const CounterTop &rhsObj )

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




/****************************************************************************
 *                                                                          *
 *                   stand alone function implementation                    *
 *                                                                          *
 ****************************************************************************/

void uploadFile(string fName, bool &loadSuccess, unsigned long &objCount, CounterTop* &llCtop)
{
    
    ifstream inputFile;
    inputFile.open(fName.c_str());
    
    unsigned long sizeInitial = objCount;
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
        
        double hMin = 0.0;
        double hMax = 0.0;
 
        
        getline (inputFile, columnHeadings);
        cout << setw(8) << "Order";
        cout << setw(12) << "Delivery";
        cout << setw(5) << "S";
        cout << setw(25) << "L";
        cout << setw(4) << "D" << endl;
        cout << setw(8) << "Date";
        cout << setw(12) << "Date";
        cout << setw(5) << "C";
        cout << setw(7) << "Len.";
        cout << setw(7) << "Dep.";
        cout << setw(7) << "Hei.";
        cout << setw(4) << "E" << setw(4) << "E" << endl;
        string line;
        line.assign(75, '-');
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
            
            hMin = MIN_HEIGHT_RATIO * depth;
            hMax = MAX_HEIGHT_RATIO * depth;
            
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
                
                // need to add Counter Top Objects to the end of the list
                if(llCtop == NULL)
                {
                    llCtop = new CounterTop(orderY, orderM, orderD, deliveryY, deliveryM,
                                            deliveryD,stoneCode, length, depth, height, finishedLength,
                                            finishedDepth, orderNumber, region, stCode, custName);
                    //added object to the end of the list, which is the beginning in this case
                    objCount++;
                    noErrors++;
                    
                    
                }
                else
                {
                    CounterTop *cPtr = llCtop;
                    while(cPtr->getNext() != NULL)
                    {
                        cPtr = cPtr->getNext();
                    }
                    
                    //now at the end of the list, know that cPtr->next is empty
                    cPtr->setNext(new CounterTop(orderY, orderM, orderD, deliveryY, deliveryM,
                                                deliveryD,stoneCode, length, depth, height, finishedLength,
                                                 finishedDepth, orderNumber, region, stCode, custName));
                    objCount++;
                    noErrors++;
                }
                
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

    }
    
    unsigned long sizeFinal;
    sizeFinal = objCount;
    
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
}


void summaryByStone( unsigned long objCount, CounterTop* llCtop )
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
    
    
    
    CounterTop *cPtr = llCtop;
    while(cPtr != NULL)
    {
        double area = cPtr->getMaterialRequired();
        totalCost = cPtr->getTotalCost();
        
        if(cPtr->getStoneCode() == 'm')
        {
            marbleCount++;
            marbleArea += area;
            marbleCost += totalCost;
        }
        else if (cPtr->getStoneCode() == 'g')
        {
            graniteCount++;
            graniteArea += area;
            graniteCost += totalCost;
        }
        else if (cPtr->getStoneCode() == 'q')
        {
            quartzCount++;
            quartzArea += area;
            quartzCost += totalCost;
        }
        
        cPtr = cPtr->getNext();
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


void summaryByRegion( unsigned long objCount, CounterTop* llCtop )
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
    
    CounterTop *cPtr = llCtop;
    while(cPtr != NULL)
    {
        double area = cPtr->getMaterialRequired();
        double totalCost = cPtr->getTotalCost();
        
        if(cPtr->getRegion() == "North")
        {
            countNorth++;
            sqFtNorth += area;
            costNorth += totalCost;
        }
        else if(cPtr->getRegion() == "South")
        {
            countSouth++;
            sqFtSouth += area;
            costSouth += totalCost;
        }
        else if(cPtr->getRegion() == "East")
        {
            countEast++;
            sqFtEast += area;
            costEast += totalCost;
        }
        else if(cPtr->getRegion() == "West")
        {
            countWest++;
            sqFtWest += area;
            costWest += totalCost;
        }
        else if (cPtr->getRegion() == "Other")
        {
            countOther++;
            sqFtOther += area;
            costOther += totalCost;
        }
        cPtr = cPtr->getNext();
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


void clearLL( unsigned long &objCount, CounterTop* &llCtop )
{
    cout << "\tEntered function clearLL( " << objCount << ", " << llCtop << " )" << endl;
    CounterTop *current = llCtop;
    while(current != NULL)
    {
        current = current->getNext();
        delete llCtop;
        llCtop = current;
        objCount--;
    }
    cout << "\tExiting function." << endl;
    // This loop exits when current = NULL
    // At that point llCtop should also be NULL
}



/****************************************************************************
 *                                                                          *
 *                     Other Assisting Member Functions                     *
 *                                                                          *
 ****************************************************************************/

double CounterTop :: getCounterTopArea() const
{
    double area = this->length * this->height;
    return area;
}

double CounterTop :: getMaterialRequired() const
{
    double area = getCounterTopArea();
    double quantityStone = area + WASTAGE_AREA * area;
    quantityStone = ceil(quantityStone);
    
    return quantityStone;
}

double CounterTop :: getStoneCost() const
{
    double quantityStone = getMaterialRequired();
    double stoneCost;
    
    if(this->stoneCode == 'm')
    {
        stoneCost = quantityStone * COST_MARBLE;
    }
    else if(this->stoneCode == 'g')
    {
        stoneCost = quantityStone * COST_GRANITE;
    }
    else if(this->stoneCode == 'q')
    {
        stoneCost = quantityStone * COST_QUARTZ;
    }
    
    return stoneCost;
    
}

double CounterTop :: getFinishingCost() const
{
    int depFin = this->depthEdgesToFinish;
    double dep = this->depth;
    double costFinishedDepth = depFin * dep * COST_PER_FOOT;
    
    int lenFin = this->lengthEdgesToFinish;
    double len = this->length;
    double costFinishedLength = lenFin * len * COST_PER_FOOT;
    
    double totalFinishingCost = costFinishedDepth + costFinishedLength;
    
    return totalFinishingCost;
    
}

double CounterTop :: getTotalCost() const
{
    double stoneCost = getStoneCost();
    double finishingCost = getFinishingCost();
    double totalCost = stoneCost + finishingCost;
    
    return totalCost;
    
}




