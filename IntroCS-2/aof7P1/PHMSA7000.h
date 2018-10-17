

/*
 *  PHMSA7000.h
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
    int fatal;
    int injure;
    string igniteInd;
    string explodeInd;
    Date preparedDate;
    string authorizerName;
    string authorizerEmail;
    string narrative;
public:

    // Default Constructor
    HazMat7k();
    
    
    ~HazMat7k();
    
    HazMat7k(const struct HazMatData &hmd1);
    void summaryReport() const;
    
    Date get_reportReceivedDate() const {return reportReceivedDate;}
    string get_reportNumber() const {return reportNumber;}
    string get_supplementalNumber() const {return supplementalNumber;}
    string get_reportType() const {return reportType;}
    string get_operatorID() const {return operatorID;}
    string get_name() const {return name;}
    string get_operatorStreetAddress() const {return operatorStreetAddress;}
    string get_operatorCityName() const {return operatorCityName;}
    string get_operatorStateAbbreviation() const {return operatorStateAbbreviation;}
    string get_operatorPostalCode() const {return operatorPostalCode;}
    Date get_localDate() const {return localDate;}
    Time get_localTime() const {return localTime;}
    string get_commodityReleasedType() const {return commodityReleasedType;}
    double get_unintentionalReleaseBbls() const {return unintentionalReleaseBbls;}
    double get_intentionalReleaseBbls() const {return intentionalReleaseBbls;}
    double get_recoveredBbls() const {return recoveredBbls;}
    int get_fatal() const {return fatal;}
    int get_injure() const {return injure;}
    string get_igniteInd() const {return igniteInd;}
    string get_explodeInd() const {return explodeInd;}
    Date get_preparedDate() const {return preparedDate;}
    string get_authorizerName() const {return authorizerName;}
    string get_authorizerEmail() const {return authorizerEmail;}
    string get_narrative() const {return narrative;}
    
    
    void set_reportReceivedDate (Date value){reportReceivedDate = value;}
    void set_reportNumber (string value){reportNumber = value;}
    void set_supplementalNumber (string value){supplementalNumber = value;}
    void set_reportType (string value){reportType = value;}
    void set_operatorID (string value){operatorID = value;}
    void set_name (string value){name = value;}
    void set_operatorStreetAddress (string value){operatorStreetAddress = value;}
    void set_operatorCityName (string value){operatorCityName = value;}
    void set_operatorStateAbbreviation (string value){operatorStateAbbreviation = value;}
    void set_operatorPostalCode (string value){operatorPostalCode = value;}
    void set_localDate (Date value){localDate = value;}
    void set_localTime (Time value){localTime = value;}
    void set_commodityReleasedType (string value){commodityReleasedType = value;}
    void set_unintentionalReleaseBbls (double value){unintentionalReleaseBbls = value;}
    void set_intentionalReleaseBbls (double value){intentionalReleaseBbls = value;}
    void set_recoveredBbls (double value){recoveredBbls = value;}
    void set_fatal (int value){fatal = value;}
    void set_injure (int value){injure = value;}
    void set_igniteInd (string value){igniteInd = value;}
    void set_explodeInd (string value){explodeInd = value;}
    void set_preparedDate (Date value){preparedDate = value;}
    void set_authorizerName (string value){authorizerName = value;}
    void set_authorizerEmail (string value){authorizerEmail = value;}
    void set_narrative (string value){narrative = value;}
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




