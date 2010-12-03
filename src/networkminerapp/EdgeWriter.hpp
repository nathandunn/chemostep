// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/EdgeWriter.hpp"
// LAST MODIFICATION: "Wed, 05 Feb 2003 19:57:07 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: EdgeWriter.hpp,v 1.1 2003/02/06 06:05:44 ndunn Exp $


#ifndef _EDGEWRITER_
#define _EDGEWRITER_

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 
using std::ios ; 

#include <string>
using std::string ; 

#include "EdgeStatLine.hpp"

class EdgeWriter{

public:
    virtual void write(EdgeStatLine edgeList,ofstream *reportStream) ; 

protected:
    virtual void writeHeader(EdgeStatLine edgeList) {} ; 
    ofstream *reportStream; 

} ;


#endif


