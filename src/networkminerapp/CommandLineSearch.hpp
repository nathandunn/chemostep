// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/CommandLineSearch.hpp"
// LAST MODIFICATION: "Thu, 06 Feb 2003 14:51:37 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CommandLineSearch.hpp,v 1.1 2003/02/06 23:39:26 ndunn Exp $
//
// This class is only responsible for grabbing command-line input and handing 
// it off to the SearchDriver, which does all of the work.
//
// 

#ifndef _COMMAND_LINE_SEARCH_
#define _COMMAND_LINE_SEARCH_

#include <fstream.h>
using std::ofstream ; 

#include <iostream.h>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include <string>
using std::string ; 

//#include "NeuronList.hpp" 
#include "OptionList.hpp"
//#include "StringTokenizer.hpp"
//#include "LookupTable.hpp"
//#include "ConnectionReader.hpp"
//#include "DepthFirstSearch.hpp"
//#include "Threshold.hpp"
//#include "ThresholdList.hpp"
#include "SearchDriver.hpp"

class CommandLineSearch{


public:
    void printHelpAndExit() ; 
    bool init(int argc,char **argv) ; 
    int doTreeSearch() ; 


private:
    const static string TAB ; 
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

    string inputList ; 
    string outputList ; 

    string edgeReportOutput ;
    bool edgeDoTxt ;
    bool edgeDoDot ;
    string nodeReportOutput ;
    bool nodeDoTxt ;
    bool nodeDoDot ;



} ;

#endif

