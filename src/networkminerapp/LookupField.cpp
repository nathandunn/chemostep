// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/LookupField.cpp"
// LAST MODIFICATION: "Sat, 04 Jan 2003 15:12:38 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: LookupField.cpp,v 1.1 2003/01/05 04:56:00 ndunn Exp $

#include "LookupField.hpp" 

LookupField::LookupField(int newId, string newEntry) {
  id = newId ; 
  name = newEntry ; 
}

void LookupField::setId(int newId) {
  id = newId ; 
}

void LookupField::setName(string newName) {
  name = newName ; 
}
string LookupField::getName() { return name ;  } 
int LookupField::getId() {  return id ; }  


