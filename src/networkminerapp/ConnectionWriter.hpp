// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/ConnectionWriter.hpp"
// LAST MODIFICATION: "Mon, 20 Jan 2003 19:21:19 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionWriter.hpp,v 1.12 2003/01/21 04:43:46 ndunn Exp $

#ifndef _CONNECTION_WRITER_
#define _CONNECTION_WRITER_

#include <fstream.h>
using std::ofstream ; 

#include <iostream.h>
using std::cout ; 
using std::cerr ; 
using std::endl ; 
using std::ostream ; 


#include <vector.h>
using std::vector ; 

#include <string>
#include <string.h>
using std::string ; 

#include <math.h>

#include "Neuron.hpp"
#include "NeuronList.hpp"
#include "ConnectionPath.hpp"
#include "LookupTable.hpp"


class ConnectionWriter{

public:
    ConnectionWriter(string newDelimiter1 = ",", string newDelimiter2 =" ", string newPadText="#", bool newDoPadding = false , bool setDoText = true, bool seeConnection = true , bool newNoHeader = false ) ; 
    void writeConnection(ConnectionPath path) ; 
    void writeHeader(int numNeurons) ; 
    void setDoPadding(bool newDoPadding) ; 
    void setPadder(string newPadder) ; 
    void setDelimiter1(string del1) ; 
    void setDelimiter2(string del2) ; 
    // 1. use the neuron list to create a list of neurons and a LookupTable
    // 2. use the connection file and the LookupTable to create a connectionList
    // 3. parse the inputs into ints with the lokupTable
    // 4. parse the outputs into ints with the lokupTable
    // 5. create the DepthFirst search with these options
    //     search = new DepthFirstSearch(    . . . . . . ) ; 
    // 6. create an output file stream with the ouptut file
    // 7. create a connection writer with the output options
    // 8. set the output file stream (6)
    // 9. set the lookup table (1) 
    // 10. set the writer for the search (5)
    // 11. do search
    void setNoHeader(bool newNoHeader) ; 
    void write(string newText) ; 
    void setOutputStream(ostream *newOutputStream) ; 
    void setLookupTable(LookupTable newLookupTable) ; 
    bool showConnection(){
       return seeConnection ; 
    }
    bool doText() {
       return textOutput ;    
    }; 
    bool setDoText(bool newDoText) {
       textOutput = newDoText ; 
       return textOutput ; 
    }
    void setNumNeurons(int newNumNeurons){
       headerNeurons = newNumNeurons ; 
    }
	int getNumNeurons(){
       return headerNeurons ; 
    }

private:
    string delimiter1 ; 
    string delimiter2 ; 
    bool doPadding ;
    string padText ; 
    string fileName ; 
    ostream *outputStream  ; 
    LookupTable lookupTable ; 
    bool textOutput ; 
    int headerNeurons ; 
    bool seeConnection ; 
    bool noHeader ; 

} ;

#endif

