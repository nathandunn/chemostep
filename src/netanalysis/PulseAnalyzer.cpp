#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 

#include "PulseAnalyzer.hpp"

PulseAnalyzer::PulseAnalyzer() 
{
}

/// Returns the maximum amplitude for a given series from a start-point.
double PulseAnalyzer::getMaxAmplitude( vector<double>* timeSeries,int start) {
    int counter = start ; 
    double startValue = (*timeSeries)[counter-1] ; 
    double currentValue = (*timeSeries)[counter-1] ; 
    double nextValue = (*timeSeries)[counter] ; 
    double nextSign = nextValue - currentValue ; 
    double currentSign = nextSign ; 
//    cout << "init value[" << (counter-1) << "]=" << startValue << " sign[" << counter-1 << "]=" << 0 << endl ; 
//    cout << "first value[" << counter << "]=" << nextValue << " sign[" << counter << "]=" << nextSign << endl ; 
    while(  (( currentSign * nextSign) > 0) && (counter <  timeSeries->size())  ){
        ++counter ; 
        currentValue = nextValue ; 
        nextValue = (*timeSeries)[counter] ; 
        currentSign = nextSign ; 
        nextSign = nextValue - currentValue ; 
//        cout << "value[" << counter << "]=" << nextValue << " sign[" << counter << "]=" << nextSign << endl ; 
    }
//    cout << "stop at counter: " << counter << " value: " << currentValue << endl ; 
    return currentValue - startValue ; 
}


/// Get activities from pulses of applications.  Traces are delivered as time split traces.
vector<double>* PulseAnalyzer::getAmplitude( vector< vector<double>*>* fullTrace, int pulseLocation) 
{
   vector<double>* fullAmplitude = new vector<double>() ; 
   int numNeurons = fullTrace->size() ;
   for(int i = 0 ; i < numNeurons ; i++){
	   // pulse location is the first pulse, but not the max
       if(i==0) { fullAmplitude->push_back(  getMaxAmplitude( (*fullTrace)[i] ,pulseLocation  ) ); }
       else{ fullAmplitude->push_back(  getMaxAmplitude( (*fullTrace)[i] ,pulseLocation+1  ) );  }
   }
   return fullAmplitude ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--prune--1.4.6--patch-20/src/netanalysis/PulseAnalyzer.cpp"
// LAST MODIFICATION: "Thu, 09 Sep 2004 17:10:34 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

