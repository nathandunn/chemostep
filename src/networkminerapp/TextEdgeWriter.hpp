// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/TextEdgeWriter.hpp"
// LAST MODIFICATION: "Thu, 20 Feb 2003 20:04:20 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: TextEdgeWriter.hpp,v 1.2 2003/02/21 04:25:53 ndunn Exp $


#ifndef _TEXTEDGEWRITER_
#define _TEXTEDGEWRITER_

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 

#include <vector>
using std::vector ; 

#include <string>
using std::string ; 

#include "EdgeStatLine.hpp"
#include "EdgeWriter.hpp"

class TextEdgeWriter : public EdgeWriter{

public:
    virtual void write(EdgeStatLine edgeList,ofstream *reportStream) ; 
    virtual void writeHeader(EdgeStatLine edgeList) ; 


protected:
    virtual void setUniqueSet(string edge) ; 
    vector<string> *uniqueNodes ; 

} ;


#endif


