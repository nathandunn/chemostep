
#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <iterator>
using std::ostream_iterator ; 

#include <numeric>
using std::fill; 

#include "FirstOrderImpulseLabelIdentifier.hpp"

#include "FirstOrderLabel.hpp"
#include "FirstOrderFilter.hpp"
#include "FirstOrderImpulseFilter.hpp"
#include "DataFilter.hpp"
#include "LabelSet.hpp"
#include "blitzdefs.hpp"

LabelSet* FirstOrderImpulseLabelIdentifier::identifyLabel(DataFilter* newDataFilter) 
{
    LabelSet* labelSet = new LabelSet(newDataFilter->getNumSignals()) ; 
//    labelSet->setMaxTime( newDataFilter->getTotalTimePoints() ) ; 
    FirstOrderLabel* firstOrderLabel = NULL ; 
    for(int i = 0 ; i < labelSet->size() ; i++){
        firstOrderLabel = new FirstOrderLabel(i) ;
        firstOrderLabel->setTau( ((FirstOrderFilter*) newDataFilter)->getTau(i )) ; 
        firstOrderLabel->setAmplitude( ((FirstOrderFilter*) newDataFilter)->getAmplitude( i )) ; 
        calculateError(firstOrderLabel,newDataFilter)    ; // calcualte error and stor it in firstOrderLabel
        (*labelSet)[i] =  firstOrderLabel ; 
    }

    return labelSet ; 
}

/// Calculates diff-squared error for a pulse relative to raw-signal.
double FirstOrderImpulseLabelIdentifier::calculateError(Label* newLabel,DataFilter* newFilter) 
{
    int labelCount = newLabel->getLabelCount() ; 
    double amplitude = ((FirstOrderLabel*) newLabel)->getAmplitude() ; 
    double tau = ((FirstOrderLabel*) newLabel)->getTau() ; 
    Matrix* rawSignal = newFilter->getSignal() ; 
    double error = 0.0 ; 
    int timeFromPeakCounter = 0 ;  // This counter is for the 1st-order impulse function
    int absoluteTimeCounter = (int) ((FirstOrderImpulseFilter*) newFilter)->getTimeToFirstPeak(labelCount) +  ((FirstOrderImpulseFilter*) newFilter)->getImpulseTime() ; // This counter is for raw data, so it starts at the first peak.
//    int absoluteTimeCounter =   ((FirstOrderImpulseFilter*) newFilter)->getImpulseTime() ; // This counter is for raw data, so it starts at the first peak.
    int totalTime = newFilter->getTotalTimePoints() ; 
    vector<double>* errorVector = new vector<double>(totalTime) ; 
    vector<double>* modelTraceVector = new vector<double>(totalTime) ; 

    fill(errorVector->begin(),errorVector->end(),0.0) ; 
    fill(modelTraceVector->begin(),modelTraceVector->end(),((FirstOrderImpulseFilter*) newFilter)->getBaseline(labelCount)) ; 
    
//    cout << "1st order absoluteTimeCounter: " << absoluteTimeCounter << " totalTime: " << totalTime << endl ; 

    while( absoluteTimeCounter < totalTime ){
        (*modelTraceVector)[absoluteTimeCounter] =  ( amplitude / tau * exp( -timeFromPeakCounter/ tau ) + ((FirstOrderImpulseFilter*) newFilter)->getBaseline(labelCount)) ; 
//        (*errorVector)[absoluteTimeCounter] = pow( (*rawSignal) ( absoluteTimeCounter,labelCount) -  (*modelTraceVector)[absoluteTimeCounter]  , 2.0) ; 
        (*errorVector)[absoluteTimeCounter] = fabs( (*rawSignal) ( absoluteTimeCounter,labelCount) -  (*modelTraceVector)[absoluteTimeCounter]  ) ; 
        ++absoluteTimeCounter ; 
        ++timeFromPeakCounter; 
    }

    newLabel->setErrorVector( errorVector ) ; 
    newLabel->setModelTraceVector( modelTraceVector ) ; 

    return error ; 
}

int FirstOrderImpulseLabelIdentifier::calculateErrorPoints(Label* newLabel,DataFilter* newFilter) 
{
    return newFilter->getTotalTimePoints() - (int) ((FirstOrderImpulseFilter*) newFilter)->getTimeToFirstPeak(newLabel->getLabelCount()) ; 
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


