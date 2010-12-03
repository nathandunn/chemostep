
#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <iterator>
using std::ostream_iterator ; 

#include <numeric>
using std::fill; 

#include "ZeroOrderImpulseLabelIdentifier.hpp"

#include "ZeroOrderLabel.hpp"
#include "ZeroOrderFilter.hpp"
#include "ZeroOrderImpulseFilter.hpp"
#include "DataFilter.hpp"
#include "LabelSet.hpp"
#include "blitzdefs.hpp"

LabelSet* ZeroOrderImpulseLabelIdentifier::identifyLabel(DataFilter* newDataFilter) 
{
    LabelSet* labelSet = new LabelSet(newDataFilter->getNumSignals()) ; 
//    labelSet->setMaxTime( newDataFilter->getTotalTimePoints() ) ; 
    ZeroOrderLabel* firstOrderLabel = NULL ; 
    for(int i = 0 ; i < labelSet->size() ; i++){
        firstOrderLabel = new ZeroOrderLabel(i) ;
        calculateError(firstOrderLabel,newDataFilter)    ; // calcualte error and stor it in firstOrderLabel
        (*labelSet)[i] =  firstOrderLabel ; 
    }

    return labelSet ; 
}

/// Calculates diff-squared error for a pulse relative to raw-signal.
double ZeroOrderImpulseLabelIdentifier::calculateError(Label* newLabel,DataFilter* newFilter) 
{
    int labelCount = newLabel->getLabelCount() ; 
    Matrix* rawSignal = newFilter->getSignal() ; 
    double error = 0.0 ; 
    int timeFromPeakCounter = 0 ;  // This counter is for the 1st-order impulse function
    int absoluteTimeCounter =   ((ZeroOrderImpulseFilter*) newFilter)->getImpulseTime() ; // This counter is for raw data, so it starts at the first peak.
    int totalTime = newFilter->getTotalTimePoints() ; 
    vector<double>* errorVector = new vector<double>(totalTime) ; 
    vector<double>* modelTraceVector = new vector<double>(totalTime) ; 

    fill(errorVector->begin(),errorVector->end(),0.0) ; 
    fill(modelTraceVector->begin(),modelTraceVector->end(),((ZeroOrderImpulseFilter*) newFilter)->getBaseline(labelCount)) ; 
    
//    cout << "1st order absoluteTimeCounter: " << absoluteTimeCounter << " totalTime: " << totalTime << endl ; 

    while( absoluteTimeCounter < totalTime ){
        (*modelTraceVector)[absoluteTimeCounter] =   ((ZeroOrderImpulseFilter*) newFilter)->getBaseline(labelCount) ; 
//        (*errorVector)[absoluteTimeCounter] = pow( (*rawSignal) ( absoluteTimeCounter,labelCount) -  (*modelTraceVector)[absoluteTimeCounter]  , 2.0) ; 
        (*errorVector)[absoluteTimeCounter] = fabs( (*rawSignal) ( absoluteTimeCounter,labelCount) -  (*modelTraceVector)[absoluteTimeCounter]  ) ; 
        ++absoluteTimeCounter ; 
        ++timeFromPeakCounter; 
    }

    newLabel->setErrorVector( errorVector ) ; 
    newLabel->setModelTraceVector( modelTraceVector ) ; 

    return error ; 
}

int ZeroOrderImpulseLabelIdentifier::calculateErrorPoints(Label* newLabel,DataFilter* newFilter) 
{
    return (newFilter->getTotalTimePoints() - ((ZeroOrderImpulseFilter*) newFilter)->getImpulseTime() )  ; 
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


