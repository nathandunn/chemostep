// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/CommandLineSearch.cpp"
// LAST MODIFICATION: "Thu, 06 Feb 2003 15:01:07 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CommandLineSearch.cpp,v 1.1 2003/02/06 23:39:26 ndunn Exp $



#include "CommandLineSearch.hpp" 

void CommandLineSearch::printHelpAndExit() 
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

  cout << "Report parameters:" << endl;
  cout << "  -report file             The general name the report files go under" << endl ; 
  cout << "  -dot                     Produce .dot output from report filename." << endl ; 
  cout << "  -txt                     Produce .txt output from report filename." << endl ; 



  exit(1) ; 
}


bool CommandLineSearch::init(int argc, char *argv[]) 
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
    inputList = opt.getOption("input","") ; 
    outputList = opt.getOption("output",",") ;

    if(delText1==TAB){
       delText1="\t"  ;
    }

    if(delText2==TAB){
       delText2="\t"  ;
    }

    edgeReportOutput = opt.getOption("report","") ; 
    edgeDoTxt = opt.getFlag("txt",false) ; 
    edgeDoDot = opt.getFlag("dot",false) ; 

    // disabled?
    nodeReportOutput = opt.getOption("nodereport","") ; 
    nodeDoTxt = opt.getFlag("txt",false) ; 
    nodeDoDot = opt.getFlag("dot",false) ; 


  return true;
}


// init SearchDriver and run
int CommandLineSearch::doTreeSearch(){
  
    SearchDriver *driver = new SearchDriver() ; 
    driver->startSearch(
        (string) inputList,
        (string) outputList,
        (string) tableFile ,
        (string) connectionFile ,
        (string) resultsFile,
        searchDepth,
        cThresh,
        eThresh,
        delText1,
        delText2,
        newPadText,
        doPadding,
        noHeader,
        !doTextOutput,
        doShowConnection,
        stopAtTerminus,
        edgeReportOutput,
        edgeDoTxt,
        edgeDoDot,
        nodeReportOutput,
        nodeDoTxt,
        nodeDoDot
        ) ;



}


int main(int argc, char *argv[]){

    cout << "running"  << endl ; 

  CommandLineSearch commandLineSearch ;
  if (commandLineSearch.init(argc, argv)!=true) {
    cerr << "Connection Search: initialization errors" << endl;
    return 1;
  }

  return commandLineSearch.doTreeSearch() ; 

}

const string CommandLineSearch::TAB="tab"  ;

