// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/ConnectionReader.cpp"
// LAST MODIFICATION: "Fri, 17 Jan 2003 14:28:50 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionReader.cpp,v 1.15 2003/01/17 22:06:24 ndunn Exp $

#include "ConnectionReader.hpp"  


int ConnectionReader::findConnection(int fromId){

    for(int i = 0 ; i < connectionTable.size() ; i++){
//        cout << ((Neuron) connectionTable[i]).getId() << " " ; 
		if(  ((Neuron) connectionTable[i]).getId() == fromId ){
			return i ; 
        }
    }

    return -1 ; 

}

// if a comment is read, return COMMENT
// if space is read return SPACE
// else return 0 ; 
int ConnectionReader::readComment(const char* line){
    int comment ; 
    int space ; 

    space = INT_MAX ; 
    comment = strcspn(line,COMMENT) ; 
    space = strcspn(line,SPACE) ; 
   
    if(space==0){
       return (int) SPACE ; 
    }
    if(comment==0){
      ++line ; 
      cout << "reading comment: " << line << endl ; 
      return (int) COMMENT ; 
    }


    return 0 ; 
}

vector<Neuron> ConnectionReader::readConnections(string connectionFileName,LookupTable lookupTable, ThresholdList newThresholdList) {

  ifstream connectionFileStream(connectionFileName.c_str(),ios::in) ; 

     if(connectionFileStream==0){
        cerr << "unable to open file: " << connectionFileName << endl ; 
        exit(1) ; 
     }else{
        cout << "reading connections: "<< connectionFileName << endl ; 
     }


  const int INPUT_BUFF = 30 ; 
  char input ;
  int charCount = 0 ; 
  char *buffer = new char[INPUT_BUFF] ; 
int i = 0 ; 

  string fromNeuronString ; 
  string toNeuronString ; 
  string weightString; 

  int fromId ; 
  int toId ; 
  float weightFloat; 
  string connectionType  ; 

  int connectionCounter = 0 ; 
  int neuronCounter = 0 ; 

//  int j = 0  ; 
  while(connectionFileStream.getline(buffer,30,'\n')){

//      cout << "j: " << j++  ; 
//      cout << " for buffer: " << buffer << endl ; 
     if(readComment(buffer)==0){

      StringTokenizer tokens(buffer,' ') ; 

        fromNeuronString = tokens[0] ; 
        toNeuronString = tokens[1] ; 
        weightString = tokens[2] ; 

        connectionType = GENERAL_CONNECTION ; 
           
        if(tokens.size()==4){
            connectionType = tokens[3] ; 
        }


    
    // find the neurons this corresponds to, (convert it)
        fromId = lookupTable.findId(fromNeuronString) ; 
        toId = lookupTable.findId(toNeuronString) ; 
        weightFloat = atof(weightString.c_str()) ; 

           
    // implement a threshold
   if(newThresholdList.testHighThreshold(weightFloat,connectionType)){
       neuronCounter += addConnection(fromId,toId,weightFloat,connectionType) ;
       if(connectionType==ELECTRICAL_CONNECTION){
           neuronCounter += addConnection(toId,fromId,weightFloat,connectionType) ;
           ++connectionCounter ;  	
       }
       ++connectionCounter ;  	
   }  // end of testThresh
   }  // end of comment if
  }  // end of while loop


    cout << "neurons: " << neuronCounter << " connections: " << connectionCounter << endl ; 

//    for(int i = 0 ; i < connectionTable.size() ; i++){
//       cout << i << ": " << connectionTable[i]  << endl ; 
//    }

   connectionFileStream.close() ; 
  return connectionTable ; 
}


int ConnectionReader::addConnection(int fromId,int toId,float weightFloat,string connectionType){
//        cout << "adding: " << fromId << " " << toId << " wt: " <<  weightFloat << endl ; 

    // determine if the neuron already exists in the connectionTable (id>0)
      int neuronCounterReturn = 0  ;
      Neuron aNeuron(0) ; 
        int existingFromId = findConnection(fromId) ; 
        


    // if it exists, pull the neuron create a connection and add it to the neuron 
    // if it does exist, add this connection and weight to its downstream components
    // do this for the presynaptic neuron
    if(existingFromId>=0){
		  aNeuron  = ((Neuron) connectionTable[existingFromId]) ; 

          // add a connection
          aNeuron.addDownstreamConnection(fromId,toId,weightFloat,connectionType) ; 

          // adding neuron back to the table
          connectionTable[existingFromId] = aNeuron ; 
    }
    // if it doesn't exist, add the neuron, and add this downstream connection
    else{ 
      ++neuronCounterReturn ; 
      Neuron newNeuron(fromId) ; 
      newNeuron.addDownstreamConnection(fromId,toId,weightFloat,connectionType) ; 
      connectionTable.push_back(newNeuron) ; 

//      cout << "adding it: " << newNeuron << " table size: " << connectionTable.size() << endl ;
    }


    // add neuron for the postsynaptic neuron
    // if it exists, do nothing 
    // if it doesn't exist, add the neuron
    existingFromId = findConnection(toId) ; 
    if(existingFromId<0){
      ++neuronCounterReturn ;
      Neuron newNeuron(toId) ; 
      // there is no connection to add, just a neuron
      connectionTable.push_back(newNeuron) ; 
//      cout << "adding it: " << newNeuron << " table size: " << connectionTable.size() << endl ;
    }


    return neuronCounterReturn ; 


}

LookupTable ConnectionReader::readTable(string tableFileName) {
  LookupTable newTable ;  
  ifstream tableFileStream(tableFileName.c_str(),ios::in) ; 

     if(tableFileStream==0){
        cerr << "unable to open file: " << tableFileName << endl ; 
        exit(1) ; 
     }else{
        cout << "reading file: "<< tableFileName << endl ; 
     }
 
  const int INPUT_BUFF = 30 ; 
  char input ;
  int charCount = 0 ; 
  char *buffer = new char[INPUT_BUFF] ; 

  while(tableFileStream.getline(buffer,30,'\n')){
      if(readComment(buffer)==0){
        newTable.addEntry(buffer) ;  
      }
  }
   tableFileStream.close() ; 
  
  return newTable ;    
} 

const char* ConnectionReader::COMMENT = "#" ; 
const char* ConnectionReader::SPACE= " " ; 


