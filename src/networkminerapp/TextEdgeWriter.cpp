// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/NETWORK_MINER/src/TextEdgeWriter.cpp"
// LAST MODIFICATION: "Mon, 24 Mar 2003 22:21:41 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: TextEdgeWriter.cpp,v 1.4 2003/03/28 00:54:45 ndunn Exp $

#include "TextEdgeWriter.hpp"

void TextEdgeWriter::write(EdgeStatLine edgeStats,ofstream *newReportStream) {

    reportStream = newReportStream ; 
    writeHeader(edgeStats) ; 

    uniqueNodes = new vector<string>() ; 
    
    // add writer's to writer-list for now, but later, init from gui
    EdgeStat *anEdge ; 
    for(int i = 0 ; i < edgeStats.numEdges() ; i++){
        anEdge = edgeStats.getEdge(i) ; 

        setUniqueSet(anEdge->getFrom()) ; 
        setUniqueSet(anEdge->getTo()) ; 

        *reportStream << anEdge->getFrom() << "-" << anEdge->getTo() << " " << anEdge->getType() << " " ; 
        for(int j = 0 ; j < anEdge->numRules() ; j++){
			*reportStream << anEdge->getStatFromRule(j) << "  " ;
        }
        *reportStream << endl ; 
    }

    *reportStream << endl ; 
    *reportStream << "Unique neurons: " << uniqueNodes->size() << endl ; 
    for(int i = 0 ; i < uniqueNodes->size() ; i++){
       *reportStream << (*uniqueNodes)[i] << endl ; 
    }

}

void TextEdgeWriter::setUniqueSet(string edge){

    for(int i = 0 ; i < uniqueNodes->size() ; i++){
        if(edge==(*uniqueNodes)[i]){
           return ; 
        }
    }

    uniqueNodes->push_back(edge) ; 
}


void TextEdgeWriter::writeHeader(EdgeStatLine edgeStats) {

    *reportStream << "cnxns "  ; 
    for(int j = 0 ; j < edgeStats.numRules() ; j++){
        *reportStream << ((CountRule*) edgeStats.getRule(j))->getType() << "  " ;
    }
    *reportStream << endl ; 

}





