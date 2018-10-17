

/*
 * PHMSA7000.h
 *
 * COSC 052 Fall 2016
 * Project #3
 *
 * Due on: NOV 1, 2016
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

/****************************************************************************
 ****************************************************************************
 **                  class HazMat7k declaration                            **
 ****************************************************************************
 ****************************************************************************/
#ifndef PHMSA7000_h
#define PHMSA7000_h

#include "DateTime.h"

using std::string;

class HazMat7k
{
    
    friend std::ostream& operator<< (std::ostream &os, const HazMat7k &rhsObj);
    
private:
    Date reportReceivedDate;
    string reportNumber;
    string supplementalNumber;
    string reportType;
    string operatorID;
    string name;
    string operatorStreetAddress;
    string operatorCityName;
    string operatorStateAbbreviation;
    string operatorPostalCode;
    Date localDate;
    Time localTime;
    string commodityReleasedType;
    double unintentionalReleaseBbls;
    double intentionalReleaseBbls;
    double recoveredBbls;
    string igniteInd;
    string explodeInd;
    Date preparedDate;
    string authorizerName;
    string authorizerEmail;
public:

    // Default Constructor
    HazMat7k();
    
    // Destructor
    ~HazMat7k();
    
    //Convert Constructor
    HazMat7k(const struct HazMatData &);
    
    
    void summaryReport() const;
    
    
    bool operator<(const HazMat7k &h) {return this->reportNumber < h.reportNumber;}
    bool operator>=(const HazMat7k &h) {return this->reportNumber >= h.reportNumber;}
    
    Date getReportReceivedDate() const {return reportReceivedDate;}
    string getReportNumber() const {return reportNumber;}
    string getSupplementalNumber() const {return supplementalNumber;}
    string getReportType() const {return reportType;}
    string getOperatorID() const {return operatorID;}
    string getName() const {return name;}
    string getOperatorStreetAddress() const {return operatorStreetAddress;}
    string getOperatorCityName() const {return operatorCityName;}
    string getOperatorStateAbbreviation() const {return operatorStateAbbreviation;}
    string getOperatorPostalCode() const {return operatorPostalCode;}
    Date getLocalDate() const {return localDate;}
    Time getLocalTime() const {return localTime;}
    string getCommodityReleasedType() const {return commodityReleasedType;}
    double getUnintentionalReleaseBbls() const {return unintentionalReleaseBbls;}
    double getIntentionalReleaseBbls() const {return intentionalReleaseBbls;}
    double getRecoveredBbls() const {return recoveredBbls;}
    string getIgniteInd() const {return igniteInd;}
    string getExplodeInd() const {return explodeInd;}
    Date getPreparedDate() const {return preparedDate;}
    string getAuthorizerName() const {return authorizerName;}
    string getAuthorizerEmail() const {return authorizerEmail;}
    
    
    void setReportReceivedDate (Date value){reportReceivedDate = value;}
    void setReportNumber (string value){reportNumber = value;}
    void setSupplementalNumber (string value){supplementalNumber = value;}
    void setReportType (string value){reportType = value;}
    void setOperatorID (string value){operatorID = value;}
    void setName (string value){name = value;}
    void setOperatorStreetAddress (string value){operatorStreetAddress = value;}
    void setOperatorCityName (string value){operatorCityName = value;}
    void setOperatorStateAbbreviation (string value){operatorStateAbbreviation = value;}
    void setOperatorPostalCode (string value){operatorPostalCode = value;}
    void setLocalDate (Date value){localDate = value;}
    void setLocalTime (Time value){localTime = value;}
    void setCommodityReleasedType (string value){commodityReleasedType = value;}
    void setUnintentionalReleaseBbls (double value){unintentionalReleaseBbls = value;}
    void setIntentionalReleaseBbls (double value){intentionalReleaseBbls = value;}
    void setRecoveredBbls (double value){recoveredBbls = value;}
    void setIgniteInd (string value){igniteInd = value;}
    void setExplodeInd (string value){explodeInd = value;}
    void setPreparedDate (Date value){preparedDate = value;}
    void setAuthorizerName (string value){authorizerName = value;}
    void setAuthorizerEmail (string value){authorizerEmail = value;}
};



// ********************
// *** LossOrDamage ***
// ********************
class LossOrDamage : public HazMat7k
{
public:
    //Default Constructor
    LossOrDamage();
    //Convert Constructor
    LossOrDamage(const HazMatData&);
    
};




// ************************
// *** FatalityOrInjury ***
// ************************
class FatalityOrInjury : public HazMat7k
{
    friend std::ostream& operator<< (std::ostream &os, const FatalityOrInjury &rhsObj);
    
private:
    int fatal;
    int injure;
    string narrative;
public:
    //default constructor
    FatalityOrInjury();
    
    //Convert Constructor
    FatalityOrInjury(const HazMatData&);
    
    //Overriden summary report function
    void summaryReport() const;
    
    void setFatal(int fatalValue) {fatal = fatalValue;}
    void setInjure (int injureValue) {injure = injureValue;}
    void setNarrative (string story) {narrative = story;}
    
    double getFatal() {return fatal;}
    double getInjure() {return injure;}
    string getNarrative() {return narrative;}
    
};





/****************************************************************************
 ****************************************************************************                                                                       
 **                                                                        **
 **               struct HazMatData declaration                            **
 **            Students may use this code as their                         **
 **            own, without any attribution.                               **
 **                                                                        **
 ****************************************************************************                                                                       
 ****************************************************************************/


struct HazMatData
{
    Date report_received_date;
    char report_number[10+1];
    char supplemental_number[7+1];
    char report_type[20+1];
    char operator_id[7+1];
    char name[55+1];
    char operator_street_address[57+1];
    char operator_city_name[18+1];
    char operator_state_abbreviation[4+1];
    char operator_postal_code[12+1];
    Date local_date;
    Time local_time;
    char commodity_released_type[84+1];
    double unintentional_release_bbls;
    double intentional_release_bbls;
    double recovered_bbls;
    int fatal;
    int injure;
    char ignite_ind[5+1];
    char explode_ind[5+1];
    Date prepared_date;
    char authorizer_name[45+1];
    char authorizer_email[42+1];
    char narrative[4000+1];
    
}; //END struct HazMatData declaration

#endif




