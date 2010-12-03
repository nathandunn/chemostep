// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--dev--1.4.2--patch-1/src/wormsim/StatReporter.hpp"
// LAST MODIFICATION: "Wed, 07 Jul 2004 16:22:42 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: StatReporter.hpp,v 1.1 2003/02/24 00:42:54 ndunn Exp $


#ifndef _STATREPORTER_
#define _STATREPORTER_

#include <iostream>
using std::endl ; 

#include <string>
using std::string ;

#include <fstream>
using std::ofstream ; 


//#include <iostream>
//using std::cout; 
//using std::ostream; 
//using std::endl; 

#include "MapSpace.hpp"

using namespace std ; 

class StatReporter{

public:
    StatReporter(string newReportFile, string newDelimiter = " ") ;
    int doReport(MapSpace *theSpace, int count, int numSteps, double originalError) ; 
    int doReportHeader() ; 


private:
    ofstream *thisReportStream ; 
    string thisReportFileName ;
    string delimiter ;

} ;


#endif



