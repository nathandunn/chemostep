// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/DepthFirstSearch.hpp"
// LAST MODIFICATION: "Fri, 28 Mar 2003 18:24:20 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: DepthFirstSearch.hpp,v 1.19 2003/03/31 22:29:14 ndunn Exp $


#ifndef _DEPTHFIRSTSEARCH_
#define _DEPTHFIRSTSEARCH_

#include <iostream.h>
using std::ostream ; 

#include <vector.h>
using std::vector ; 

#include "Neuron.hpp"
#include "NeuronList.hpp"
#include "ConnectionWriter.hpp"
#include "ConnectionPath.hpp"
#include "LookupTable.hpp"

class DepthFirstSearch{
public:
    DepthFirstSearch(NeuronList newConnectionList, vector<int> start, vector<int> stop,int depth=INT_MAX, bool newDoStopAtTerminus = false, bool newDoSelfConnections = false, bool newDoRecurrentConnections = false ) ; 
    NeuronList makeTree(NeuronList connectionList,vector<int> start, vector<int> stop) ; 
    void setStartPoints(vector<int> newStart) ; 
    void setStopPoints(vector<int> newStop) ; 
    void setStartPoint(int newStart) ; 
    void setStopPoint(int newStop) ; 
    void addSolutionPath(ConnectionPath path) ; 
	bool isTerminus(Neuron terminusNeuron) ; 
    int doSearch() ;   // init components and begin search
    int singleSearch(Neuron parentNeuron) ;  
    int processChildren(Neuron parentNeuron) ; 
    void makeList(Neuron rootNeuron) ;  // recursively iterate from root, up through parents
    int getSearchTreeSize() {
       return searchTree.size() ; 
    }
    int getSolutionCount() {
       return solutionCount ;     
    } ; 
    void setSolutionCount(int newSolutionCount ) {
       solutionCount = newSolutionCount ;     
    } ; 
    vector<ConnectionPath> getSolutionPaths() {
        return solutionPaths ; 
    }


    void setWriter(ConnectionWriter *newWriter){
       writer = newWriter ; 
    }

private:
    NeuronList searchTree ;   // Neurons don't have a unique entry, 
                              // and can be included more than once or not at all.
                              // Initially empty and filled during search.
    NeuronList connectionList ;   // The total number of neurons N 
      							  // each neuron having a unique entry.
    vector<NeuronList> validConnections ; 
    vector<int> startPoints ; 
    vector<int> stopPoints ; 
    vector<int> globalStopPoints ; 
    int maxDepth ; 
    int solutionCount ; 
    bool doStopAtTerminus; 
    bool doSelfConnections; 
    bool doRecurrentConnections; 
    ConnectionWriter *writer ; 
    ostream *outputStream ; 
    vector<ConnectionPath> solutionPaths ; 

    
} ;

#endif
