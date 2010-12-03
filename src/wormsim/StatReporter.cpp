// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/PETRIE_2/source/StatReporter.cpp"
// LAST MODIFICATION: "Sun, 23 Feb 2003 14:20:06 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: StatReporter.cpp,v 1.1 2003/02/24 00:42:54 ndunn Exp $

#include "StatReporter.hpp"

StatReporter::StatReporter(string newReportFile, string newDelimiter){

    delimiter = newDelimiter ; 

    if(newReportFile==""){
//        thisReportStream = (ofstream *) &cout ; 
        thisReportStream = NULL ; 
    }else{
        thisReportStream = new ofstream(newReportFile.c_str(),ios::out) ; 
    }
}

int StatReporter::doReportHeader() {

        *thisReportStream << "run"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "error"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "time_at_center"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "avg_time_at_center"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "time_to_center"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "avg_time_to_center"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "%_time_to_center"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "%_time_died"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "avg_output"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "%_pirouette"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "%_middle"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "%_run"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "%_sharpturn"   ;
        *thisReportStream << delimiter  ; 
        *thisReportStream << "%_run"   ;
        *thisReportStream << delimiter  ; 

        *thisReportStream << "avg_conc_diff_mM/s"   ;
        *thisReportStream << delimiter  ; 
        

        *thisReportStream << endl ; 
}

int StatReporter::doReport(MapSpace *space,int count, int numSteps, double originalError) {

        // run report on starting, stopping, compile stats
        *thisReportStream <<  count  ; 
        *thisReportStream << delimiter  ; 
        *thisReportStream <<  originalError ; 
        *thisReportStream << delimiter  ; 


        *thisReportStream <<  space->getAverageTimeAtCenter()  ; 
        *thisReportStream << delimiter  ; 
        *thisReportStream  << (space)->getAverageTimeAtCenter()/numSteps   ; 
        *thisReportStream << delimiter  ; 
        *thisReportStream << space->getAverageTimeToCenter() ; 
        *thisReportStream << delimiter  ; 
        *thisReportStream << (space)->getAverageTimeToCenter()/numSteps    ; 
        *thisReportStream << delimiter  ; 


        *thisReportStream  << (space)->getAverageReachedCenter()  ; 
        *thisReportStream << delimiter  ; 
        *thisReportStream  << (space)->getAverageWormDies()   ; 
        *thisReportStream << delimiter  ; 


        *thisReportStream << space->getProbabilityAverage()   ; 
        *thisReportStream << delimiter  ; 


        *thisReportStream << (space)->getPirouetteDecisionRatio()  ;  
        *thisReportStream << delimiter  ; 
        *thisReportStream << (space)->getMiddleDecisionRatio() ;  
        *thisReportStream << delimiter  ; 
        *thisReportStream << (space)->getRunDecisionRatio()  ;  
        *thisReportStream << delimiter  ; 


        *thisReportStream << (space)->getSharpTurnBehaviorRatio() ;  
        *thisReportStream << delimiter ; 
        *thisReportStream << (space)->getRunBehaviorRatio() ;  
        *thisReportStream << delimiter ; 



        *thisReportStream << space->getAverageConcentrationDiff()  ;  
        *thisReportStream << endl ; 

        return 1 ; 
}


