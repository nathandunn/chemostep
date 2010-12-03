// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountWeightRule.cpp"
// LAST MODIFICATION: "Wed, 05 Feb 2003 16:24:54 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountWeightRule.cpp,v 1.3 2003/02/06 02:09:16 ndunn Exp $

#include "CountWeightRule.hpp"

CountWeightRule::CountWeightRule() {
}

CountWeightRule::CountWeightRule(CountWeightRule* newCountWeightRule) {
   reset() ; 
   count = ((CountWeightRule*) newCountWeightRule)->getCount() ; 
}

void CountWeightRule::countValue(Connection *cnxn){
   count += cnxn->getWeight() ;  
}

float CountWeightRule::getCount(){
    return count ; 
}


void CountWeightRule::reset(){
    count = 0.0 ; 
}

string CountWeightRule::getType() {
   return COUNT_WEIGHT; 
}

CountWeightRule& CountWeightRule::operator=(const CountWeightRule& rhs){
    reset() ; 
    count = ((CountWeightRule) rhs).getCount(); 
    return *this ; 
}

