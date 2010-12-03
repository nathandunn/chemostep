// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/EdgeStat.hpp"
// LAST MODIFICATION: "Tue, 01 Apr 2003 13:22:38 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: EdgeStat.hpp,v 1.8 2003/04/01 21:24:00 ndunn Exp $


#ifndef _EDGESTAT_
#define _EDGESTAT_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 


#include "Connection.hpp"
#include "Stat.hpp"
#include "LookupTable.hpp"
#include "CountRule.hpp" 
#include "CountEachRule.hpp" 
#include "CountWeightRule.hpp" 
#include "CountWeightOnlyRule.hpp" 

class EdgeStat : public Stat {

public:
    EdgeStat() ; 
    EdgeStat(Connection* cnxn) ; 
    virtual void addRule(CountRule* newRule) ; 
    virtual void addRules(const vector<CountRule*> newRules) ; 
    virtual int numRules() ;
    virtual string getTo() ; 
    virtual string getFrom() ; 
    virtual string getType() ; 
    virtual void calcStats(Connection* cnxn)  ; 
    virtual string getStats()  ; 
    virtual void resetRules() ; 
    virtual float getStatFromRule(int count) ; 
    virtual float getStatFromRule(string rule) ; 
    virtual string getRuleType(int count) ; 
    CountRule *getRule(int ruleNum) ; 


protected:
    string from  ;
    string to ;  
    string type ;  
    vector<CountRule*> rules ; 


} ;

#endif

