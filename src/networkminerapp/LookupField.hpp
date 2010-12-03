// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/LookupField.hpp"
// LAST MODIFICATION: "Sat, 04 Jan 2003 15:11:39 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: LookupField.hpp,v 1.1 2003/01/05 04:56:00 ndunn Exp $

#include <string>
using std::string ; 

class LookupField{

public:
   LookupField(int id, string entry) ; 
   void setId(int newId) ; 
   void setName(string newName) ; 
   string getName() ; 
   int getId() ; 


private:
   int id ;  
   string name ;  


} ;


