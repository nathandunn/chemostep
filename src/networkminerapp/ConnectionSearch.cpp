// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/ConnectionSearch.cpp"
// LAST MODIFICATION: "Fri, 17 Jan 2003 14:38:29 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ConnectionSearch.cpp,v 1.4 2003/01/17 22:06:24 ndunn Exp $

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
#include "DepthFirstSearch.hpp"
#include "Threshold.hpp"
#include "ThresholdList.hpp"


// input variables
string TAB = "tab" ; 
ThresholdList thresholdList ; 
string delText1 ; 
string delText2 ; 
string newPadText ; 
bool noHeader ; 
bool doPadding ; 
bool doTextOutput ; 
bool doShowConnection ; 
bool stopAtTerminus  ;
string tableFile ; 
string connectionFile ; 
string resultsFile ; 
string treeFile ; 
int searchDepth ; 
string fileOut ; 
int verbosity ; 
float eThresh ; 
float cThresh ; 

vector<string> inputList ; 
vector<string> outputList ; 
vector<int> inputs  ;  
vector<int> outputs  ;  


// main variables
LookupTable lookupTable ; 
NeuronList theConnectionTable ; 


void printHelpAndExit() 
{
  cout << "Usage:" << endl;
  cout << "  Connection Search [commands]" << endl;
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
  cout << "  -tree        filename    File where the trees go." << endl;
  cout << "  -export      filename    The file output. NONE, COUT (default), <filename>" << endl;
  cout << "  -v           N           Output verbosity.  0 none, 1 prod-wts, 2 sum-wts hops" << endl;
  cout << "  -int                     Whether or not to do text output or integer output for neurons. " << endl ;
  cout << "      					  Without this flag text is default." << endl;
  cout << "  -del1        text        Delimiter 1. Use 'tab' for tab." << endl ; 
  cout << "  -del2        text        Delimiter 2.  Use 'tab' for tab." << endl ; 
  cout << "  -pad         text        Padding text. " <<  endl ; 
  cout << "  -dopad                   Whether or not to do padding. " << endl ; 
  cout << "  -showconnection          Whether or not to show connection type. " << endl ; 
  cout << "  -noheader                Eliminates header data. " << endl ; 
  cout << endl ; 

  cout << "Search parameters:" << endl;
  cout << "  -input list  			  A list of input neurons, such as 1,2-5,8." << endl  ;
  cout << "  -output list             A list of terminal neurons, such as 1,2-5,8" << endl;
  cout << "  -depth N                 Maximum search-depth (or number of hops)." << endl;
  cout << "  -cthresh v                 Maximum chemical search-threshold (or connection strength) that will be considered." << endl;
  cout << "  -ethresh v                 Maximum electrical search-threshold (or connection strength) that will be considered." << endl;
  cout << "  -stopatterminus           Indicates whether or not to stop once any endpoint has been hit." << endl  ;
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
    stopAtTerminus = opt.getFlag("stopatterminus",false) ; 
    delText1  = opt.getOption("del1",",") ; 
    delText2  = opt.getOption("del2"," ") ; 
    doPadding = opt.getFlag("dopad",false) ; 
    noHeader = opt.getFlag("noheader",false) ; 
    doShowConnection = opt.getFlag("showconnection",false) ; 
    newPadText  = opt.getOption("pad","") ; 
    if(newPadText!=""){
        cout << "setting to true" << endl ;
       doPadding=true ; 
    }
    if(newPadText=="" && doPadding==true){
       newPadText="#" ; 
    }
    doTextOutput = !(opt.getFlag("int",false)) ; 
    eThresh= (float) opt.getDouble("ethresh",0.0) ; 
    cThresh = (float) opt.getDouble("cthresh",0.0) ; 
    verbosity = opt.getInt("v",0) ; 
    searchDepth = opt.getInt("depth",INT_MAX) ; 
    tableFile = opt.getOption("table","") ; 
    fileOut = opt.getOption("export","COUT") ; 
    connectionFile = opt.getOption("connections","") ; 
    resultsFile = opt.getOption("results","") ; 
    treeFile = opt.getOption("tree","") ; 
    inputList = opt.getTokenizedStringList("input",',') ;
    outputList = opt.getTokenizedStringList("output",',') ;

    thresholdList.addThreshold(eThresh,ELECTRICAL_CONNECTION) ;
    thresholdList.addThreshold(cThresh,CHEMICAL_CONNECTION) ;

    if(delText1==TAB){
       delText1="\t"  ;
    }

    if(delText2==TAB){
       delText2="\t"  ;
    }

  return true;
}


int doTreeSearch(){
    
    ConnectionReader reader ; 
    // 1. open the table file and read in table conversions
    lookupTable = reader.readTable(tableFile) ; 
    
    // 2. open the connection file and read in the new connections
    theConnectionTable = reader.readConnections(connectionFile,lookupTable,thresholdList) ; 

    // 3. convert the search inputs and outputs to ints using the API on the table
    for(int i = 0 ; i < inputList.size() ; i++){
       inputs.push_back(lookupTable.findId(inputList[i])) ; 
       cout << "input: " << inputList[i] << " " << inputs[i] << endl ; 
       if(inputs[inputs.size()-1]<0){
		  cerr << "bad input, exiting" << endl ; 
		  cerr << "bad input, " << inputList[i] << " exiting" << endl ; 
          exit(1) ; 
       }
    }

    for(int i = 0 ; i < outputList.size() ; i++){
       outputs.push_back(lookupTable.findId(outputList[i])) ; 
       cout << "output: " << outputList[i] << " " << outputs[i] << endl ; 
       if(outputs[outputs.size()-1]<0){
		  cerr << "bad output, " << outputList[i] << " exiting" << endl ; 
          exit(1) ; 
       }
    }

    cout << "verbosity: " << verbosity << endl ; 
    if(verbosity>2){
        Neuron bNeuron ; 
        Connection *bConnection ;  
        for(int i = 0; i < theConnectionTable.size() ; i++){
           bNeuron = theConnectionTable.getNeuronAt(i) ; 
           cout << bNeuron.getId() << Neuron::delimiter ; 
           cout << "--- "  ;
           for(int j = 0 ; j < bNeuron.numConnections() ; j++ ){
              bConnection = bNeuron.getConnection(j) ; 
              cout << "( " ;
              cout << bConnection->getFromId() << Neuron::delimiter ; 
              cout << bConnection->getType() << Neuron::delimiter ; 
              cout << bConnection->getToId() << Neuron::delimiter ; 
              cout << " ) " ;
           }
           cout << endl ; 
        }
        cout << endl ; 
    }
    cout << endl ; 
    
    // 5. perform the search
    DepthFirstSearch depthFirstSearch (theConnectionTable,inputs,outputs,searchDepth,stopAtTerminus); 

    
    ofstream outputFileStream ; 
   
    ConnectionWriter *depthWriter = new ConnectionWriter(delText1,delText2,newPadText,doPadding,doTextOutput, doShowConnection,noHeader) ; 
    depthWriter->setLookupTable(lookupTable) ; 

    // need to do this externally, otherwise it will fall out of scope, unless we make it static
    ofstream fileStream ; 

    cout << "setting output to: " ;
    if(fileOut=="NONE"){
        // don't do anything here
        cout << " NONE " << endl ; 
    }else
    if(fileOut=="COUT"){
        cout << " cout " << endl ; 
        depthWriter->setOutputStream(&cout) ; 
    }else{
        cout << " filename '" << fileOut << "'" <<   endl ; 
        fileStream.open(fileOut.c_str(),ios::out) ; 
        depthWriter->setOutputStream(&fileStream) ; 
    }

    depthFirstSearch.setWriter(depthWriter) ; 

    cout << "max depth: " << searchDepth << endl ; 

    cout << "starting" << endl ; 
    depthFirstSearch.doSearch()  ;
    cout << "finished" << endl ; 
    cout << depthFirstSearch.getSolutionCount() << " solutions found. " << endl ; 
    cout << depthFirstSearch.getSearchTreeSize() << " nodes in search tree. " << endl ; 


}


int main(int argc, char *argv[]){

    cout << "running"  << endl ; 

  if (!init(argc, argv)) {
    cerr << "Connection Search: initialization errors" << endl;
    return 1;
  }

  return doTreeSearch() ; 

}


