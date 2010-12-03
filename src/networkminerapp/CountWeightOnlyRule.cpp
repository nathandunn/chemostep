// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountWeightOnlyRule.cpp"
// LAST MODIFICATION: "Tue, 01 Apr 2003 13:01:28 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountWeightOnlyRule.cpp,v 1.1 2003/04/01 21:24:00 ndunn Exp $

#include "CountWeightOnlyRule.hpp"

CountWeightOnlyRule::CountWeightOnlyRule() {
}

CountWeightOnlyRule::CountWeightOnlyRule(CountWeightOnlyRule* newCountWeightOnlyRule) {
   reset() ; 
   count = ((CountWeightOnlyRule*) newCountWeightOnlyRule)->getCount() ; 
}

void CountWeightOnlyRule::countValue(Connection *cnxn){
   count = cnxn->getWeight() ;  
}

float CountWeightOnlyRule::getCount(){
    return count ; 
}


void CountWeightOnlyRule::reset(){
    count = 0.0 ; 
}

string CountWeightOnlyRule::getType() {
   return COUNT_WEIGHT_ONLY; 
}

CountWeightOnlyRule& CountWeightOnlyRule::operator=(const CountWeightOnlyRule& rhs){
    reset() ; 
    count = ((CountWeightOnlyRule) rhs).getCount(); 
    return *this ; 
}

