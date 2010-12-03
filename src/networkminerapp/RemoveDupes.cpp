// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/NETWORK_MINER/src/RemoveDupes.cpp"
// LAST MODIFICATION: "Wed, 15 Jan 2003 19:33:53 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: RemoveDupes.cpp,v 1.4 2003/01/16 03:03:24 ndunn Exp $

#include <fstream.h>
using std::ofstream ; 

#include <iostream.h>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include "NeuronList.hpp" 
#include "OptionList.hpp"
#include "StringTokenizer.hpp"
#include "LookupTable.hpp"
#include "ConnectionReader.hpp"
#include "ConnectionPath.hpp"


// input variables
string tableFile ; 
string connectionFile ; 
string resultsFile ; 
string fileOut ; 
int verbosity ; 


ConnectionPath theConnections ; 

// main variables
LookupTable lookupTable ; 
NeuronList theConnectionTable ; 


void printHelpAndExit() 
{
  cout << "Usage:" << endl;
  cout << "  RemoveDupes [commands]" << endl;
  cout << endl;

  // help commands
  cout << "Help options:" << endl  ;
  cout << "  -help           Print this message" << endl;
  cout << endl ; 

  // neural networks 
  cout << "File parameters:" << endl;
  cout << "  -table filename          The text to int conversion table.  A single list that " << endl  ;
  cout << " 						  will be numbered from 1 to N." << endl;
  cout << "  -connections filename    File that contains all the connections and weight (from to weight)." << endl;
  cout << "  -results     filename    File where the results go for each path." << endl;
  cout << "  -export      filename    The file output. NONE, COUT (default), <filename>" << endl;
  cout << "  -v           N           Output verbosity.  0 none, 1 prod-wts, 2 sum-wts hops" << endl;
  cout << "  -int                     Whether or not to do text output or integer output for neurons. " << endl ;
  cout << "      					  Without this flag text is default." << endl;
  cout << endl ; 


  exit(1) ; 
}


bool init(int argc, char *argv[]) 
{
  // create a command line parser object:
  OptionList opt(argc,argv);
  
  // if no command line arguments, or if -help speficied, print a 
  // message and exit

  if ((argc == 1) || (opt.getFlag("help",false)))
    printHelpAndExit();

  // Get the command line settings
    verbosity = opt.getInt("v",0) ; 
    tableFile = opt.getOption("table","") ; 
    fileOut = opt.getOption("export","COUT") ; 
    connectionFile = opt.getOption("connections","") ; 
    resultsFile = opt.getOption("results","") ; 

  return true;
}




int removeDupes(){
    
    ConnectionReader reader ; 
    // 1. open the table file and read in table conversions
    lookupTable = reader.readTable(tableFile) ; 
    

  ifstream connectionFileStream(connectionFile.c_str(),ios::in) ; 

     if(connectionFileStream==0){
        cerr << "unable to open file: " << connectionFile << endl ; 
        exit(1) ; 
     }else{
        cout << "reading connections: "<< connectionFile << endl ; 
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


  int numDupes = 0 ; 

  // read everything in to a big connection path 

  while(connectionFileStream.getline(buffer,30,'\n')){


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

        theConnections.addConnection(new Connection(fromId,toId,weightFloat,connectionType)) ; 
           
  }  // end of while loop

   connectionFileStream.close() ; 


   // iterate through, and for each element, do a check to make sure its not a dupe
   Connection *aCnxn ; 
   int tempFromId = 0 ; 
   int tempToId = 0 ; 
   int dupeConnection = -1 ; 
   int initSize = theConnections.size() ; 
   for(int i = 0  ; i <  theConnections.size() ; i++){
	 aCnxn = theConnections.getConnectionAt(i) ; 
     tempFromId = aCnxn->getFromId() ; 
     tempToId = aCnxn->getToId() ; 


     // see if the self-connection exists
     if(tempToId==tempFromId){
         theConnections.removeConnectionAt(i) ; 
         cout << "remove self-connection at " <<  i << ": "  ; 
         cout << lookupTable.findStringEntry(tempFromId) << Neuron::delimiter ; 
         cout << lookupTable.findStringEntry(tempToId)  << endl ;
         ++numDupes ; 
         --i ;
     }
     else{
         // see if the reverse connection exists
         dupeConnection = theConnections.hasConnection(tempToId,tempFromId) ;  
         if(dupeConnection>=0){
             theConnections.removeConnectionAt(dupeConnection) ; 
             cout << "remove dupe at " <<  dupeConnection << ": "  ; 
             cout << lookupTable.findStringEntry(tempToId) << Neuron::delimiter ; 
             cout << lookupTable.findStringEntry(tempFromId)  << Neuron::delimiter ;
             cout << " for " << i << Neuron::delimiter ; 
             cout << lookupTable.findStringEntry(tempFromId) << Neuron::delimiter ; 
             cout << lookupTable.findStringEntry(tempToId)  << endl ;
             ++numDupes; 
             --i ;
         }
     }
   }

   

   cout << "the number of initial connections: " << initSize << endl ; 
   cout << "the number of dupes: " << numDupes << endl ; 
   cout << "the number of final connections: " << theConnections.size() << endl ; 

  return numDupes ; 
}

int writeDupes() {

    // need to do this externally, otherwise it will fall out of scope, unless we make it static
    ofstream fileStream ; 

        cout << " filename '" << fileOut << "'" <<   endl ; 
        fileStream.open(fileOut.c_str(),ios::out) ; 

        if(fileStream==0){
             cerr << "could not write to file: " << fileStream << endl ; 
             exit(1) ; 
        }

        Connection *bCnxn ; 
    for(int i = 0 ; i < theConnections.size() ; i++){
        bCnxn = theConnections.getConnectionAt(i) ; 
        fileStream << lookupTable.findStringEntry(bCnxn->getFromId()) << Neuron::delimiter ; 
        fileStream << lookupTable.findStringEntry(bCnxn->getToId()) << Neuron::delimiter ; 
        fileStream << bCnxn->getWeight() << Neuron::delimiter ; 
        fileStream << bCnxn->getType() << Neuron::delimiter ; 
        fileStream << endl ; 

    }

}


int main(int argc, char *argv[]){

    cout << "running"  << endl ; 

  if (!init(argc, argv)) {
    cerr << "Connection Search: initialization errors" << endl;
    return 1;
  }


  removeDupes()  ; 
  writeDupes() ; 

  return 0 ; 

}


