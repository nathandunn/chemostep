// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountRule.cpp"
// LAST MODIFICATION: "Tue, 01 Apr 2003 13:01:59 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountRule.cpp,v 1.4 2003/04/01 21:24:00 ndunn Exp $

#include "CountRule.hpp"

CountRule::CountRule(CountRule* newCountRule) {
   reset() ; 
   count = ((CountRule*) newCountRule)->getCount() ; 
}

CountRule::CountRule() {
}

void CountRule::countValue(Connection *cnxn){
    cout << "trying to count in no count: type " << getType() << " "  ; 
}


float CountRule::getCount() {
   return count ; 
}

string CountRule::getType() {
   return COUNT_TYPE ;
}


CountRule& CountRule::operator=(const CountRule& rhs){
    cout << "copy from: " << &rhs << " to: " << this << endl ; 
    reset() ; 
    count = ((CountRule) rhs).getCount(); 
    return *this ; 
}


const string CountRule::COUNT_TYPE = "NONE" ; 
const string CountRule::COUNT_EACH= "COUNTEACH" ; 
const string CountRule::COUNT_WEIGHT = "COUNTWEIGHT" ; 
const string CountRule::COUNT_WEIGHT_ONLY = "COUNTWEIGHTONLY" ; 

