// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountEachRule.hpp"
// LAST MODIFICATION: "Wed, 05 Feb 2003 16:04:52 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountEachRule.hpp,v 1.3 2003/02/06 02:09:16 ndunn Exp $


#ifndef _COUNTEACHRULE_
#define _COUNTEACHRULE_

#include "CountRule.hpp"

class CountEachRule : public CountRule{

public:
    // just adds 1 each time
    CountEachRule() ;
    CountEachRule(CountEachRule* newCountEachRule) ; 
    virtual void countValue(Connection *cnxn)  ; 
    virtual float getCount()  ; 
    virtual void reset()  ; 
    virtual string getType() ; 
    CountEachRule& operator=(const CountEachRule& rhs) ; 

} ;


#endif


