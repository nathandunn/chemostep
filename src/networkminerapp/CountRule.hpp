// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountRule.hpp"
// LAST MODIFICATION: "Tue, 01 Apr 2003 13:01:43 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountRule.hpp,v 1.5 2003/04/01 21:24:00 ndunn Exp $

#ifndef _COUNTRULE_
#define _COUNTRULE_

#include <string.h>

#include <string>
using std::string ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "Connection.hpp"


// an interface which contains rule methods
class CountRule{

public:
    CountRule() ; 
    CountRule(CountRule* newCountRule) ; 
    virtual void countValue(Connection *cnxn)   ; 
    virtual float getCount()   ; 
    virtual void reset() { } ; 
    virtual string getType() ; 
    CountRule& operator=(const CountRule& rhs) ; 
    static const string COUNT_TYPE  ; 
    static const string COUNT_EACH  ; 
    static const string COUNT_WEIGHT  ; 
    static const string COUNT_WEIGHT_ONLY  ; 

protected:
    float count ; 



} ;


#endif 


