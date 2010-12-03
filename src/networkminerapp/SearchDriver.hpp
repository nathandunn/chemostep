// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchDriver.hpp,v 1.18 2003/07/10 23:57:02 ndunn Exp $


#ifndef _SEARCH_DRIVER_
#define _SEARCH_DRIVER_

#include "DepthFirstSearch.hpp"
#include "NeuronList.hpp" 
#include "OptionList.hpp"
#include "LookupTable.hpp"
#include "ConnectionReader.hpp"
#include "DepthFirstSearch.hpp"
#include "Threshold.hpp"
#include "ThresholdList.hpp"
#include "EdgeStatLine.hpp"
#include "CountRule.hpp"
#include "CountWeightRule.hpp"
#include "CountEachRule.hpp"
#include "CountWeightOnlyRule.hpp"
#include "TextEdgeWriter.hpp"
#include "DotWriter.hpp"
#include "SearchGui.hpp"

#include "StringTokenizer.hpp"
using gnuworld::StringTokenizer ; 

#include <sstream>
using std::ostringstream; 

#include <TiFlatBaseApp.hpp>


class SearchGui ; 

/**  Depth-first network searcher.
 *
 * Searches a given network of connectivity given electrical and chemical synaptic connectivity data.
 *
 * \todo Eliminate the need to produce a list of unique neurons (i.e., generate from the unique connectivity list.
 * \todo Fix coloring in dotty output.
 * \todo Fix rank in dotty output (Start nodes at top, Stop nodes at bottom).  
 * \todo Implement multiple interfaces (search and output interfaces).
 *
 */

class SearchDriver  : public TiFlatBaseApp {


public:
//    SearchDriver(SearchGui *theGui)   ; 
    SearchDriver(string newInterfaceName, string newTypeName, AppInterface* newParent)   ; 
//    virtual void logMessage(string message) ;
    virtual void solutionPath(ConnectionPath *path) ;
    virtual bool runSearch() ; 
//    virtual void startSearch(string inputs,
//        string outputs,
//        string lookupTable,
//        string connectionTable,
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
//        bool doLabel = false 
//     ) ; 

    virtual void doReport() ; 
//    virtual void doReport( 
//        string edgeLineEdit,
//        bool edgeDoTxt,
//        bool edgeDoDot,
//        bool doSelfConnections,
//        bool doRecurrentConnections, 
//        bool doLabel ,
//        vector<string> inputList,
//        vector<string> outputList
//    ) ; 


    // autogui methods
    virtual bool createLocalMaps()  ; 
    virtual string doLocalCommand(Command* theCommand) ;

private:  
    int theEdgeCount ; 
    DepthFirstSearch *search ;
    SearchGui *gui ; 

    vector<string> parseNeurons(string inputs, char delimiter) ; 
    vector<string> inputList ; 
    vector<string> outputList ; 
    vector<int> inputs  ;  
    vector<int> outputs  ;  
    const static string TAB ;  
    LookupTable lookupTable;  


    // local variables 
   string mStartNeurons ; 
   string mStopNeurons ; 
   int mSearchDepth ; 
   int mChemDepth ; 
   int mElecDepth ; 
   string mConnectivityFile ; 

   // set 2 - output variables
   bool mEdgeTextOutput ; 
   bool mStopAtTerminus ; 
   bool mEdgeDotOutput ; 
   bool mDoSelfConnections ; 
   bool mDoRecurrentConnections ; 
   bool mLabelConnections ; 

   
   
   // variables to axe
   string mDel1 ; 
   string mDel2 ; 
   string mPadding ; 
   string mNeuronFile ; 
   bool mShowConnection ; 
   bool mIntOutput ;   /// not sure what this is
   bool mDoPadding ;  /// whether or not to implement padding
   bool mDoStats ; 
   string mEdgeOutputFile ; 



} ;



#endif


