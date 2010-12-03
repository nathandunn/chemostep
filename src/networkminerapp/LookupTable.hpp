// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/LookupTable.hpp"
// LAST MODIFICATION: "Fri, 17 Jan 2003 10:35:25 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: LookupTable.hpp,v 1.4 2003/01/17 18:10:16 ndunn Exp $

// has accessor functions for the table of conversions for int to string

#ifndef _LookupTable_
#define _LookupTable_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 


#include "LookupField.hpp" 

class LookupTable{

public:
     static void addEntry(string newEntry) ; 
     static int findId(string name);
  	 static string findStringEntry(int findId) ;

    static vector<LookupField> fields ; 

private:

} ;

#endif

