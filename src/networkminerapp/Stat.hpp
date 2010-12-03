// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/Stat.hpp"
// LAST MODIFICATION: "Wed, 05 Feb 2003 02:08:41 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Stat.hpp,v 1.5 2003/02/05 10:03:55 ndunn Exp $


#ifndef _STAT_
#define _STAT_


#include <string>
using std::string ; 

#include <vector>
using std::vector ; 



#include "Connection.hpp" 
#include "CountRule.hpp" 


class Stat {

public:
    virtual void addRule(CountRule* newRule) {  }   ; 
    virtual void addRules(vector<CountRule*> newRules) {  }  ; 
    virtual int numRules() { return  0 ; }
    virtual float getStatFromRule(int count) { return 0.0 ; }   ; 
    virtual void calcStats(Connection *cnxn) {}   ; 
    virtual string getRuleType(int count) {  } ; 


} ;

#endif

