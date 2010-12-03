// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/DotWriter.hpp"
// LAST MODIFICATION: "Sat, 03 May 2003 13:29:29 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: DotWriter.hpp,v 1.3 2003/05/03 23:11:17 ndunn Exp $


#ifndef _DOTWRITER_
#define _DOTWRITER_

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

class DotWriter : public EdgeWriter{

public:
    DotWriter(bool setDoLabel, vector<string> newInputNeurons, vector<string> newOutputNeurons ) ; 
    virtual void write(EdgeStatLine edgeList,ofstream *reportStream) ; 
    virtual void writeHeader(EdgeStatLine edgeList) ; 
    virtual void writeCloser(EdgeStatLine edgeList) ; 

private:
    bool doLabel ; 
    vector<string> inputNeurons; 
    vector<string> outputNeurons; 
} ;


#endif


