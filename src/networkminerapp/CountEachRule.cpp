// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/CountEachRule.cpp"
// LAST MODIFICATION: "Wed, 05 Feb 2003 17:01:51 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CountEachRule.cpp,v 1.3 2003/02/06 02:09:16 ndunn Exp $

#include "CountEachRule.hpp"

CountEachRule::CountEachRule(CountEachRule* newCountEachRule) {
   reset() ; 
   count = ((CountEachRule*) newCountEachRule)->getCount() ; 
}


CountEachRule::CountEachRule() {
}

void CountEachRule::countValue(Connection *cnxn){
   count += 1.0 ;  
}

float CountEachRule::getCount(){
    return count ; 
}


void CountEachRule::reset(){
    count = 0.0 ; 
}

string CountEachRule::getType() {
   return COUNT_EACH ; 
}

CountEachRule& CountEachRule::operator=(const CountEachRule& rhs){
    reset() ; 
    count = ((CountEachRule) rhs).getCount(); 
    return *this ; 
}


