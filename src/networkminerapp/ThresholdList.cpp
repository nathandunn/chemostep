// -*- C++ -*-
// FILE: "/home/ndunn/cvs/NETWORK_MINER/src/ThresholdList.cpp"
// LAST MODIFICATION: "Mon, 13 Jan 2003 07:51:36 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ThresholdList.cpp,v 1.2 2003/01/13 15:52:51 ndunn Exp $

#include "ThresholdList.hpp"  

void ThresholdList::addThreshold(Threshold newThreshold) {
   list.push_back(newThreshold) ; 
}

void ThresholdList::addThreshold(float newValue, string newType ) {
    Threshold newThreshold(newValue,newType) ; 
    addThreshold(newThreshold) ; 
}

bool ThresholdList::testHighThreshold( float value , string type) {

    for(int i = 0 ; i < list.size() ; i++){
        if(type== ((Threshold) list[i]).getType() ){
            return (value>=((Threshold) list[i]).getValue()) ;
        }
    }

    cerr << "invalid threshold type:" << type << endl ; 
    return false ; 
}


void ThresholdList::emptyThresholds() {
  list.empty() ; 
}



