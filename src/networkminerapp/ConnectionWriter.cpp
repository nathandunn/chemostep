// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/networkminerapp/ConnectionWriter.cpp"
// LAST MODIFICATION: "Thu, 16 Feb 2006 16:03:57 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionWriter.cpp,v 1.12 2003/03/28 00:54:45 ndunn Exp $

#include "ConnectionWriter.hpp" 

ConnectionWriter::ConnectionWriter(string newDelimiter1 ,string newDelimiter2 , string newPadText, bool newDoPadding,bool setDoText ,bool newSeeConnection, bool newNoHeader ) {
    delimiter1 = newDelimiter1 ; 
    delimiter2 = newDelimiter2 ; 
    padText = newPadText ; 
    doPadding = newDoPadding ; 
    fileName = "" ; 
    textOutput = setDoText ; 
    headerNeurons = 0 ; 
    seeConnection = newSeeConnection ; 
    noHeader = newNoHeader ; 
}

void ConnectionWriter::setNoHeader(bool newNoHeader) {
   noHeader = newNoHeader ; 
}

void ConnectionWriter::setPadder(string newPadder) { 
   padText = newPadder ; 
}

void ConnectionWriter::write(string text){
   *outputStream << text ;
}


void ConnectionWriter::setOutputStream(ostream *newOutputStream){
   outputStream = newOutputStream ; 
}
 
void ConnectionWriter::setLookupTable(LookupTable newLookupTable) {
  lookupTable = newLookupTable ; 
}

void ConnectionWriter::writeConnection(ConnectionPath path) { 
    if(outputStream==0){
      return ; 
    }
    
    Connection *connection ; 

    float numConnections = (float) path.size() ; 

    if(noHeader==false){
        *outputStream << numConnections << delimiter1 ; 
        *outputStream << path.prodWeights() << delimiter1 ; 
        *outputStream << pow(path.prodWeights(),1/numConnections) << delimiter1 ; 
        *outputStream << path.sumWeights() << delimiter1 ; 
        *outputStream << (path.sumWeights()/numConnections) << delimiter1 ; 
    }



    // write out the first set

    connection = path.getConnectionAt(path.size()-1) ;

    int padCounter = headerNeurons-2 ; 
    if(doText()){
        *outputStream << lookupTable.findStringEntry(connection->getFromId()) ; 
        *outputStream << delimiter2 ; 

        if(showConnection()){
            *outputStream << (connection->getType()) ; 
            *outputStream << delimiter2 ; 
        }
        *outputStream << lookupTable.findStringEntry(connection->getToId()) ; 
        for(int i = path.size()-2 ; i >= 0 ; i--){
            --padCounter ; 
            connection = path.getConnectionAt(i)  ; 
            if(showConnection()){
                *outputStream << delimiter2 ; 
                *outputStream << (connection->getType()) ; 
                *outputStream << delimiter2 ; 
            }
            *outputStream << delimiter2 ; 
            *outputStream << lookupTable.findStringEntry(connection->getToId()) ; 
        }
    }
    else
    {
        *outputStream << (connection->getFromId()) ; 
        *outputStream << delimiter2 ; 
        if(showConnection()){
            *outputStream << (connection->getType()) ; 
            *outputStream << delimiter2 ; 
        }
        *outputStream << (connection->getToId()) ; 
        for(int i = path.size()-2 ; i >= 0 ; i--){
            --padCounter ; 
            connection = path.getConnectionAt(i)  ; 
            if(showConnection()){
                *outputStream << delimiter2 ; 
                *outputStream << (connection->getType()) ; 
                *outputStream << delimiter2 ; 
            }
            *outputStream << delimiter2 ; 
    		*outputStream << connection->getToId() ; 
        }
    }

    // add padding
    if(doPadding==true){
        while(padCounter>0){
            --padCounter ; 
            *outputStream << delimiter2 ; 
            *outputStream << padText ; 
        }
    } 

}

void ConnectionWriter::writeHeader(int numNeurons) { 

    setNumNeurons(numNeurons) ; 

    if(outputStream==0){
      return ; 
    }


    if(noHeader==false){
        *outputStream  << "hops" ;
        *outputStream << delimiter1 ; 
        *outputStream  << "prod" ;
        *outputStream << delimiter1 ; 
        *outputStream  << "prod^(1/N)" ;
        *outputStream << delimiter1 ; 
        *outputStream  << "sum" ;
        *outputStream << delimiter1 ; 
        *outputStream  << "sum/N" ;
        *outputStream << delimiter1 ; 
    }

    
    for(int i = 0 ; i < numNeurons ; i++){
      *outputStream << "n" << i << delimiter2 ; 
    }

    *outputStream << endl ; 
}


 
void ConnectionWriter::setDoPadding(bool newDoPadding) { 
    doPadding = newDoPadding ; 
}

 
void ConnectionWriter::setDelimiter1(string del1) { 
    delimiter1 = del1 ; 
}

 
void ConnectionWriter::setDelimiter2(string del2) { 
    delimiter2 = del2 ; 
}





