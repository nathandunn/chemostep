// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountWeightOnlyRule.hpp"
// LAST MODIFICATION: "Tue, 01 Apr 2003 13:00:14 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountWeightOnlyRule.hpp,v 1.1 2003/04/01 21:24:00 ndunn Exp $

#ifndef _COUNTWEIGHTONLYRULE_
#define _COUNTWEIGHTONLYRULE_

#include "CountRule.hpp"

class CountWeightOnlyRule : public CountRule{

public:
    // just adds 1 each time
    CountWeightOnlyRule() ;
    CountWeightOnlyRule(CountWeightOnlyRule* newCountWeightOnlyRule) ; 
    virtual void countValue(Connection *cnxn)  ; 
    virtual float getCount()  ; 
    virtual void reset()  ; 
    virtual string getType() ; 
    CountWeightOnlyRule& operator=(const CountWeightOnlyRule& rhs) ; 

} ;



#endif





