// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountWeightRule.hpp"
// LAST MODIFICATION: "Wed, 05 Feb 2003 15:52:16 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountWeightRule.hpp,v 1.3 2003/02/06 02:09:16 ndunn Exp $


#ifndef _COUNTWEIGHTRULE_
#define _COUNTWEIGHTRULE_

#include "CountRule.hpp"

class CountWeightRule : public CountRule{

public:
    // just adds 1 each time
    CountWeightRule() ;
    CountWeightRule(CountWeightRule* newCountWeightRule) ; 
    virtual void countValue(Connection *cnxn)  ; 
    virtual float getCount()  ; 
    virtual void reset()  ; 
    virtual string getType() ; 
    CountWeightRule& operator=(const CountWeightRule& rhs) ; 

} ;



#endif


