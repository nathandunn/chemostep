// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchDriver.cpp,v 1.22 2003/07/10 23:57:02 ndunn Exp $

#include <TiFlatBaseApp.hpp>
#include <Command.hpp>
#include <Renderer.hpp>

#include "SearchDriver.hpp" 


SearchDriver::SearchDriver(string newInterfaceName, string newTypeName, AppInterface* newParent) : TiFlatBaseApp(newInterfaceName,newTypeName,newParent) 
    ,mEdgeDotOutput(true)
    ,mEdgeTextOutput(true)
    ,mDel1(" ")
    ,mDel2(" ")
    ,mIntOutput(false)
{
    description = "A network search application." ; 
}


void SearchDriver::solutionPath(ConnectionPath *path){
   cout << "the solution path" << endl ; 
}



vector<string> SearchDriver::parseNeurons(string inputs, char delimiter){
    vector<string> neurons ; 
	StringTokenizer tokenizer(inputs,delimiter) ;  

    for(int i = 0 ; i < tokenizer.size() ; i++){
		neurons.push_back(tokenizer[i]) ; 
    }

    return neurons ; 
}



bool SearchDriver::runSearch(){
//void SearchDriver::startSearch(string inputText,
//        string outputText,
//        string lookupTableFile,
//        string connectionTableFile,
//        string outputFile,
//        int depth,
//        float chemThresh,
//        float elecThresh,
//        string del1,
//        string del2,
//        string padding,
//        bool doPadding,
//        bool noStats,
//        bool intOutput,
//        bool showConnections,
//        bool stopAtTerminus,
//        string edgeLineEdit,
//        bool edgeDoTxt,
//        bool edgeDoDot,
//        bool doSelfConnections,
//        bool doRecurrentConnections,
//        bool doLabel
// ) {


    // load the appropriate tables, etc.
    // initialize the DepthFirstSearch
    // run the search, but give *this as an argument for a back-reference


    cout << "starting search parameters: " << endl ; 
    mStartNeurons = QString(mStartNeurons).replace( " ","").upper().latin1() ;
    mStopNeurons = QString(mStopNeurons).replace( " ","").upper().latin1() ;
    cout << "inputs: "<< mStartNeurons << endl ; 
    cout << "outputs: "<< mStopNeurons << endl ; 
    cout << "lookupTable: "<< mNeuronFile << endl ; 
    cout << "connectionTable: "<< mConnectivityFile << endl ; 
    cout << "outputFile: "<< mEdgeTextOutput << endl ; 
    cout << "depth: "<< mSearchDepth << endl ; 
    cout << "chemThresh: "<< mChemDepth << endl ; 
    cout << "elecThresh: "<< mElecDepth << endl ; 
    cout << "del1: "<< mDel1 << endl ; 
    cout << "del2: "<< mDel2 << endl ; 
    cout << "padding: "<< mPadding<< endl ; 
    cout << "doPadding: "<< mDoPadding << endl ; 
    cout << "noStats: "<< mDoStats << endl ; 
    cout << "intOutput: "<< mIntOutput << endl ; 
    cout << "showConnections: "<< mShowConnection << endl ; 
    cout << "stopAtTerminus: "<< mStopAtTerminus << endl ; 
    cout << "edgeLineEdit:" << mEdgeOutputFile << endl ; 
    cout << "edgeDoTxt:" << mEdgeTextOutput << endl ; 
    cout << "edgeDoDot:" << mEdgeDotOutput << endl ; 
    cout << "doSelfConnections:" << mDoSelfConnections << endl ; 
    cout << "doRecurrentConnections:" << mDoRecurrentConnections << endl ; 


    // 1. use the neuron list to create a list of neurons and a LookupTable
    ConnectionReader reader ; 
    // 1.a open the table file and read in table conversions
    lookupTable = reader.readTable(mNeuronFile) ; 

    // 2. use the connection file and the LookupTable to create a connectionList
    ThresholdList thresholdList ; 
    thresholdList.addThreshold(mElecDepth,ELECTRICAL_CONNECTION) ;
    thresholdList.addThreshold(mChemDepth,CHEMICAL_CONNECTION) ;
    NeuronList theConnectionTable = reader.readConnections(mConnectivityFile,lookupTable,thresholdList) ; 
   
    // 3. parse the inputs into ints with the lookupTable


    inputList = parseNeurons(mStartNeurons,',') ; 
    outputList = parseNeurons(mStopNeurons,',') ; 

    inputs.clear() ; 
    outputs.clear() ; 
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

    // 4. parse the outputs into ints with the lookupTable
    if(mDel1==TAB){
       mDel1="\t"  ;
    }

    if(mDel2==TAB){
       mDel2="\t"  ;
    }

    
    // 5. create the DepthFirst search with these options
    //     search = new DepthFirstSearch(    . . . . . . ) ; 
    search = new DepthFirstSearch(theConnectionTable,inputs,outputs,mSearchDepth,mStopAtTerminus,mDoSelfConnections,mDoRecurrentConnections) ;  


    // 6. create an output file stream with the ouptut file
    ofstream outputFileStream ; 

    // 7. create a connection writer with the output options
    ConnectionWriter *depthWriter = new ConnectionWriter(mDel1,mDel2,mPadding,mDoPadding,!mIntOutput, mShowConnection,mDoStats) ; 
    // 8. set the output file stream (6)
    cout << "setting output to: " ;
    if(mEdgeOutputFile==""){
        cout << " cout " << endl ; 
        depthWriter->setOutputStream(&cout) ; 
    }else{
        cout << " filename '" << mEdgeOutputFile << "'" <<   endl ; 
        outputFileStream.open(mEdgeOutputFile.c_str(),ios::out) ; 
        depthWriter->setOutputStream(&outputFileStream) ; 
    }


    // 9. set the lookup table (1) 
    depthWriter->setLookupTable(lookupTable) ; 
    // 10. set the writer for the search (5)
    search->setWriter(depthWriter) ; 
    // 11. do search
    search->doSearch()  ;
    cout << "finished" << endl ; 
    cout << search->getSolutionCount() << " solutions found-> " << endl ; 
    cout << search->getSearchTreeSize() << " nodes in search tree-> " << endl ; 
    string messageText = "finished" ; 

    if(search->getSolutionCount()>0){
        doReport( ) ;
//            edgeLineEdit,
//            edgeDoTxt,
//            edgeDoDot,
//            doSelfConnections,
//            doRecurrentConnections,
//            doLabel,
//            inputList, 
//            outputList 
//        ) ; 
    }

    ostringstream textStream ; 
    textStream << "Search Finished!" << endl ; 
    textStream  << "Nodes in search tree: "<< search->getSearchTreeSize() << endl ; 
    textStream  << "Network paths found: "<< search->getSolutionCount() << endl ; 
    textStream << "Connections in search tree: "<< theEdgeCount  << endl ; 
//    logMessage(textStream.str()) ; 

    return true ; 

}


//  Takes all solutions from each path, and add to the different stat lines.

void SearchDriver::doReport( ){
//        string edgeLineEdit,
//        bool edgeDoTxt,
//        bool edgeDoDot,
//        bool doSelfConnections,
//        bool doRecurrentConnections, 
//        bool doLabel,
//        vector<string> inputList,
//        vector<string> outputList
//        ) {

    vector<ConnectionPath> solutions = search->getSolutionPaths() ; 
    ConnectionPath path = solutions[0] ; 
    Connection* connection ;  
    EdgeStatLine edgeStats ; 

    CountRule *eachRule = new CountEachRule() ; 
    CountRule *weightRule = new CountWeightRule() ; 
    CountRule *weightOnlyRule = new CountWeightOnlyRule() ; 
    edgeStats.addRule(eachRule) ; 
    edgeStats.addRule(weightRule) ; 
    edgeStats.addRule(weightOnlyRule) ; 
    
    int edgeCount = 0 ; 
    int nodeCount = 0 ; 

    for( int i = 0 ; i < solutions.size() ; i++){
        path = solutions[i] ; 
        for(int j = 0 ; j < path.size() ; j++){
            connection = path.getConnectionAt(j) ; 

            // have edgestat calculate stat based on connection
						edgeCount += edgeStats.calcPath(connection) ; 	

            // have nodestat calculate stat based on connection
        }
    }

    cout << "number of edges: " << edgeCount << endl ; 

    theEdgeCount = edgeCount ; 

    // set outputstreams for report
    // hand the outputstream to the report writer
//        edgeLineEdit,
//        edgeDoTxt,
//        edgeDoDot,
//        nodeLineEdit,
//        nodeDoTxt,
//        nodeDoDot

    ofstream reportStream ; 
    if(mEdgeTextOutput==true){
        string edgeTextOutput = mEdgeOutputFile + ".txt" ; 
        TextEdgeWriter edgeWriter ; 
        reportStream.open(edgeTextOutput.c_str(),ios::out) ; 
        edgeWriter.write(edgeStats,&reportStream) ; 
        reportStream.close() ; 
    }

    if(mEdgeDotOutput==true){
        DotWriter dotWriter(mLabelConnections,inputList,outputList)  ; 
        string edgeDotOutput = mEdgeOutputFile+ ".dot" ; 
        reportStream.open(edgeDotOutput.c_str(),ios::out) ; 
        dotWriter.write(edgeStats,&reportStream) ; 
        reportStream.close() ; 
    }

}

//void SearchDriver::logMessage(string message) 
//{
////   gui->logTheMessage(message) ; 
//}

bool SearchDriver::createLocalMaps()  
{
   // variables to keep
   // set 1 - search variables
    addOptionToMap( "01_START_NEURONS", OPT_STRING,&mStartNeurons,"APP/NetParser","start search at neurons (separated by commas)") ; 
    addOptionToMap( "02_STOP_NEURONS", OPT_STRING,&mStopNeurons,"APP/NetParser","stop search at neurons (separated by commas)") ; 
    addOptionToMap( "03_CONNECT_FILE", OPT_FILE_LOAD,&mConnectivityFile,"APP/NetParser","synaptic connection file") ; 
    addOptionToMap( "04_NEURON_FILE", OPT_FILE_LOAD,&mNeuronFile,"APP/NetParser","neuron file") ; 
    addOptionToMap( "05_SEARCH_DEPTH", OPT_INT,&mSearchDepth,"APP/NetParser","number of sequential synapses to search") ; 
    addOptionToMap( "06_CHEM_DEPTH", OPT_INT,&mChemDepth,"APP/NetParser","minimum number of chemical synapses") ; 
    addOptionToMap( "07_ELEC_DEPTH", OPT_INT,&mElecDepth,"APP/NetParser","minimum number of electrical synapses") ; 
    addOptionToMap( "08_OUTPUT_FILE", OPT_FILE_SAVE,&mEdgeOutputFile,"APP/NetParser","output file") ; 

   // set 2 - output variables
    addOptionToMap( "09_STOP_AT_TERMINUS", OPT_BOOL,&mStopAtTerminus,"APP/NetParser","end search at stop neuron") ; 
    addOptionToMap( "10_SELF_CONNECTIONS", OPT_BOOL,&mDoSelfConnections,"APP/NetParser","map self-connections") ; 
    addOptionToMap( "11_RECURRENT_CONNECTIONS", OPT_BOOL,&mDoRecurrentConnections,"APP/NetParser","map recurrent connections") ; 
    addOptionToMap( "12_SEARCH_OUTPUT", OPT_BOOL,&mEdgeTextOutput,"APP/NetParser","data output") ; 
    addOptionToMap( "13_LABEL_CONNECTIONS", OPT_BOOL,&mLabelConnections,"APP/NetParser","label connections") ; 
   
   
//    addCommandToMap( "open") ; 
//    addCommandToMap( "quit") ; 
    addCommandToMap( "search") ; 
}

string SearchDriver::doLocalCommand(Command* theCommand) 
{
    cout << "doing command: " << theCommand->getName() << endl ; 
    mRenderer->savePreferences() ; 

    // eventually this should be start and stop annealer
    string theName  = theCommand->getName() ; 
    string returnString = "" ; 
    if(theName=="search"){
        if(runSearch()==true){
            returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS; 
        }
        else{
            returnString += InterfaceXmlString::COMMANDSTATUS_FAILURE ; 
        }
    }
    else
    if(theName=="quit"){
        exit(0) ; 
    }
    cout << "the return string:" << returnString  << endl ; 
    return returnString ; 
}



const string SearchDriver::TAB = "tab" ; 

