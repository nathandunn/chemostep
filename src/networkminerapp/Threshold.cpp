// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/Threshold.cpp"
// LAST MODIFICATION: "Fri, 10 Jan 2003 15:52:38 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: Threshold.cpp,v 1.1 2003/01/10 23:27:55 ndunn Exp $

#include "Threshold.hpp"

Threshold::Threshold(float newValue, string newType) {
    value = newValue ; 
    type = newType ; 

}

void Threshold::setValue(float newValue) {
   value = newValue ; 
}

float Threshold::getValue() {
  return value ; 
}

void Threshold::setType(string newType) {
   type = newType ; 
}

string Threshold::getType() {
  return type ; 
}


