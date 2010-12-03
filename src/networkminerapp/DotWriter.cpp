// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/networkminerapp/DotWriter.cpp"
// LAST MODIFICATION: "Mon, 27 Feb 2006 11:25:44 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: DotWriter.cpp,v 1.8 2003/05/03 23:11:17 ndunn Exp $

#include "DotWriter.hpp"

DotWriter::DotWriter(bool setDoLabel, vector<string> newInputNeurons, vector<string> newOutputNeurons ) 
{
   doLabel = setDoLabel ; 
   inputNeurons = newInputNeurons ; 
   outputNeurons = newOutputNeurons ; 
}


void DotWriter::write(EdgeStatLine edgeStats,ofstream *newReportStream) {

    reportStream = newReportStream ; 
    writeHeader(edgeStats) ; 
    
    // add writer's to writer-list for now, but later, init from gui
    EdgeStat *anEdge ; 
//    float maxEdge = edgeStats.getMaxForRule(CountRule::COUNT_WEIGHT) ; 

    float maxEdge = edgeStats.getMaxForRule(CountRule::COUNT_WEIGHT_ONLY) ; 
    float scale = 0.1  ;
    float gray = 1.0 ;

    
    for(int i = 0 ; i < edgeStats.numEdges() ; i++){
        anEdge = edgeStats.getEdge(i) ; 

        // write edge
        // set label
        gray = 1.0 - (1.0 - scale)*((anEdge->getStatFromRule(CountRule::COUNT_WEIGHT_ONLY)/maxEdge)  ) - scale ; 
        *reportStream << anEdge->getFrom() << " -> " << anEdge->getTo() << " " ; 
        if(anEdge->getType()=="c"){
            *reportStream << "[" ;
            *reportStream << "style=bold" ; 
            *reportStream << "," ;
            *reportStream << "color=\""  <<  gray << " "<< gray <<" "<< gray <<"\"";
        }
        else
        if(anEdge->getType()=="e"){
            *reportStream << "[" ;
            *reportStream << "style=dashed" ; 
            *reportStream << "," ;
            *reportStream << "dir=none" ; 
            *reportStream << "," ;
            *reportStream << "color=\""  <<  gray << " "<< 0.0 <<" "<< 0.0 <<"\"";
        }
        if(doLabel){
            *reportStream << "," ;
            *reportStream << "label=\""  ; 
            *reportStream << anEdge->getStatFromRule(CountRule::COUNT_EACH)   ;
            *reportStream << "/" ;
            *reportStream << anEdge->getStatFromRule(CountRule::COUNT_WEIGHT_ONLY)  ; 
            *reportStream << "\"" ;
        }
		*reportStream << "];" ;



        // end label
		*reportStream << endl ; 


//        for(int j = 0 ; j < anEdge->numRules() ; j++){
//			*reportStream << anEdge->getStatFromRule(j) << "  " ;
//        }
        *reportStream << endl ; 
    }


    writeCloser(edgeStats) ; 

}


void DotWriter::writeHeader(EdgeStatLine edgeStats) {

    *reportStream << " digraph connectivity { " << endl  ;
}



void DotWriter::writeCloser(EdgeStatLine edgeStats) {
    *reportStream << "} " << endl ; 
}




