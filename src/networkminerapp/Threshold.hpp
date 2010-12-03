// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/Threshold.hpp"
// LAST MODIFICATION: "Fri, 10 Jan 2003 15:33:15 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Threshold.hpp,v 1.1 2003/01/10 23:27:55 ndunn Exp $

#ifndef _THRESHOLD_
#define _THRESHOLD_

#include "ConnectionTypes.hpp" 

class Threshold{


public:
    Threshold(float newValue, string newType = GENERAL_CONNECTION ) ; 
    void setValue(float newValue) ; 
    float getValue() ; 
    void setType(string newType) ; 
    string getType() ; 



private:
    float value ; 
    string type ; 

} ;



#endif


