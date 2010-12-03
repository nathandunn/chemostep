#ifndef TTESTACCEPTMODEL_HPP_
#  define TTESTACCEPTMODEL_HPP_

#include <iostream>
using std::ostream ; 

#include <vector>
using std::vector ; 

#include "AcceptModel.hpp"  


/**  Uses a two-tailed t-test to see if results are truly significant.
 *
 */
class TtestAcceptModel : public AcceptModel{

public:
    TtestAcceptModel(double newCrit=0) ; 
    virtual bool accept(double* variables) ; 
    virtual int getNumVariables() ; 
    virtual void toXML(ostream* s) ; 

    virtual void setCriticalCutoff(double newCrit) ; 
    virtual double getCriticalCutoff() ; 

protected:
    bool compareTValue(double crit, double tvalue, int count) ; 
    bool initTable() ; 
    double mCrit ; 
    // calculate on it
    double mTvalue ; 

    // table data
    double* df100 ; 
    double* df50 ; 
    double* dfInf ; 

} ;

#endif /* ifndef TTESTACCEPTMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

