
/*
 * IncidentLog.h
 *
 * COSC 052 Fall 2016
 * Project #2
 *
 * Due on: OCT 13, 2016
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

#include <vector>
#include "PHMSA7000.h"
#include <exception>
#include <stdexcept>


#ifndef IncidentLog_h
#define IncidentLog_h




class IncidentLog
{
private:
    std::vector<FatalityOrInjury>vFatalityOrInjury;
    std::vector<LossOrDamage>vLossOrDamage;
public:
    IncidentLog();
    ~IncidentLog();
    void displayReport() const;
    void appendObject (const FatalityOrInjury&);
    void appendObject (const LossOrDamage&);
    unsigned long sizeFatalityOrInjury() const;
    unsigned long sizeLossOrDamage() const;
};

#endif
