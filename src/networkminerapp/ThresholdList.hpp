// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/ThresholdList.hpp"
// LAST MODIFICATION: "Fri, 10 Jan 2003 15:49:34 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ThresholdList.hpp,v 1.1 2003/01/10 23:27:55 ndunn Exp $

#ifndef _THRESHOLD_LIST_
#define _THRESHOLD_LIST_

#include <vector.h>
using std::vector ; 

#include "Threshold.hpp" 

class ThresholdList{

public:
    void addThreshold(Threshold newThreshold) ; 
    void addThreshold(float newValue, string type ) ; 
    bool testHighThreshold(float newValue, string type) ; 
    void emptyThresholds() ; 

    

private:
    vector<Threshold> list ; 

} ;


#endif 


