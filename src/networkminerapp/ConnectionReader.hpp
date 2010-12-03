// -*- C++ -*-
// FILE: "/home/ndunn/cvs/NETWORK_MINER/src/ConnectionReader.hpp"
// LAST MODIFICATION: "Mon, 13 Jan 2003 07:50:19 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionReader.hpp,v 1.9 2003/01/13 15:52:51 ndunn Exp $

// This file reads connections for a text to integer conversion table, and a 
// table of connections.  

#ifndef _ConnectionReader_
#define _ConnectionReader_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <fstream>
using std::ifstream;

#ifdef MACOSX
    #include <float.h>
#else
    #include <values.h>
#endif


#include "Neuron.hpp"  
#include "LookupTable.hpp" 
#include "Threshold.hpp" 
#include "ThresholdList.hpp" 

#include "StringTokenizer.hpp" 
using gnuworld::StringTokenizer  ;

class ConnectionReader{

public:
    vector<Neuron> readConnections(string connectionFileName,LookupTable lookupTable, ThresholdList newThresholdList) ; 
    LookupTable readTable(string tableFileName) ; 
    vector<Neuron> readTree(string connectionFileName,string tableFileName) ; 
    int findConnection(int fromId)  ; 
    int readComment(const char* line) ; // returns 0 if not a comment or a space to skip
    int addConnection(int fromId,int toId,float weightFloat,string connectionType);


private:
  vector<Neuron> connectionTable ; 
    const static char* COMMENT  ; 
    const static char* SPACE ; 

} ;

#endif
