

/*
 *  PHMSA7000.cpp
 *
 *  COSC 052 Fall 2016
 *  Project #1
 *
 *  Due on: SEP 27, 2016
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
#include <string>
#include "PHMSA7000.h"

using std::cout;
using std::endl;

//default constructor
HazMat7k::HazMat7k():
reportReceivedDate(1861,1,1), localDate(1861, 1, 1), localTime(0, 0),
preparedDate(1861, 1, 1)
{
 
    reportNumber = "unknown";
    supplementalNumber = "unknwon";
    reportType = "unknown";
    operatorID = "unknown";
    name = "unknown";
    operatorStreetAddress = "unknown";
    operatorCityName = "unknown";
    operatorStateAbbreviation = "unknown";
    operatorPostalCode = "unknown";
    commodityReleasedType = "unknown";
    unintentionalReleaseBbls = 0.0;
    intentionalReleaseBbls = 0.0;
    recoveredBbls = 0.0;
    fatal = 0;
    injure = 0;
    igniteInd = "unknown";
    explodeInd = "unknown";
    authorizerName = "unknown";
    authorizerEmail = "unknown";
    narrative = "unknown";
}

//destructor
HazMat7k::~HazMat7k()
{
    
}

//Convert Constructor
HazMat7k::HazMat7k(const struct HazMatData &hmd1):
reportReceivedDate(hmd1.report_received_date), localDate(hmd1.local_date),
localTime(hmd1.local_time), preparedDate(hmd1.prepared_date)
{
    this->reportNumber = string(hmd1.report_number);
    this->supplementalNumber = string(hmd1.supplemental_number);
    this->reportType = string(hmd1.report_type);
    this->operatorID = string(hmd1.operator_id);
    this->name = string(hmd1.name);
    this->operatorStreetAddress = string(hmd1.operator_street_address);
    this->operatorCityName = string(hmd1.operator_city_name);
    this->operatorStateAbbreviation = string(hmd1.operator_state_abbreviation);
    this->operatorPostalCode = string(hmd1.operator_postal_code);
    this->commodityReleasedType = string(hmd1.commodity_released_type);
    this->unintentionalReleaseBbls = hmd1.unintentional_release_bbls;
    this->intentionalReleaseBbls = hmd1.intentional_release_bbls;
    this->recoveredBbls = hmd1.recovered_bbls;
    this->fatal = hmd1.fatal;
    this->injure = hmd1.injure;
    this->igniteInd = string(hmd1.ignite_ind);
    this->explodeInd = string(hmd1.explode_ind);
    this->authorizerName = string(hmd1.authorizer_name);
    this->authorizerEmail = string(hmd1.authorizer_email);
    this->narrative = string(hmd1.narrative);

}


void HazMat7k::summaryReport() const
{
    cout << "Report Number and Date:\t" << this->reportNumber << "  " << this->reportReceivedDate << endl;
    cout << "Local Date and Time:   \t" << this->localDate << "  " << this->localTime << endl;
    cout << "Number of Injuries:" << std::setw(10) << this->injure << endl;
    cout << "Number of Fatalities:" << std::setw(8) << this->fatal << endl;
    cout << "Narrative Length:" << std::setw(12) << this->narrative.length() << endl;
    cout << "Narrative: " << this->narrative << endl;
}

//The stream insertion operator should output all data members on one line
std::ostream& operator<< (std::ostream &os, const HazMat7k &rhsObj)
{
    os << rhsObj.reportReceivedDate << " " << rhsObj.reportNumber << " " << rhsObj.supplementalNumber;
    os << " " << rhsObj.reportType << " " << rhsObj.operatorID << " " << rhsObj.name;
    os << " " << rhsObj.operatorStreetAddress << " " << rhsObj.operatorCityName;
    os << " " << rhsObj.operatorStateAbbreviation << " " << rhsObj.operatorPostalCode;
    os << " " << rhsObj.localDate << " " << rhsObj.localTime << " " << rhsObj.commodityReleasedType;
    os << " " << rhsObj.unintentionalReleaseBbls << " " << rhsObj.intentionalReleaseBbls;
    os << " " << rhsObj.recoveredBbls << " " << rhsObj.fatal << " " << rhsObj.injure;
    os << " " << rhsObj.igniteInd << " " << rhsObj.explodeInd << " " << rhsObj.preparedDate;
    os << " " << rhsObj.authorizerName << " " << rhsObj.authorizerEmail << " " << rhsObj.narrative;
    
    return os;
}







