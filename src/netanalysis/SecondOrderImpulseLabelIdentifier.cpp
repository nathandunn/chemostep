
#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <iterator>
using std::ostream_iterator ; 


#include <numeric>
using std::fill; 

#include "SecondOrderImpulseLabelIdentifier.hpp"

#include "SecondOrderLabel.hpp"
#include "SecondOrderFilter.hpp"
#include "SecondOrderImpulseFilter.hpp"
#include "DataFilter.hpp"
#include "LabelSet.hpp"
#include "blitzdefs.hpp"

LabelSet* SecondOrderImpulseLabelIdentifier::identifyLabel(DataFilter* newDataFilter) 
{
    LabelSet* labelSet = new LabelSet(newDataFilter->getNumSignals()) ; 
//    labelSet->setMaxTime( newDataFilter->getTotalTimePoints() ) ; 
    SecondOrderLabel* secondOrderLabel = NULL ; 
    for(int i = 0 ; i < labelSet->size() ; i++){
        secondOrderLabel = new SecondOrderLabel(i) ;
        secondOrderLabel->setDecay( ((SecondOrderFilter*) newDataFilter)->getDecay(i )) ; 
        secondOrderLabel->setAmplitude( ((SecondOrderFilter*) newDataFilter)->getAmplitude( i )) ; 
        secondOrderLabel->setPeriod( ((SecondOrderFilter*) newDataFilter)->getPeriod(i )) ; 
        secondOrderLabel->setPhaseShift( ((SecondOrderFilter*) newDataFilter)->getPhaseShift(i )) ; 
        calculateError(secondOrderLabel,newDataFilter)    ; // calcualte error and stor it in secondOrderLabel
        (*labelSet)[i] =  secondOrderLabel ; 
    }

    return labelSet ; 
}

/// Calculates diff-squared error for a pulse relative to raw-signal.
double SecondOrderImpulseLabelIdentifier::calculateError(Label* newLabel,DataFilter* newFilter) 
{
    int labelCount = newLabel->getLabelCount() ; 
    double amplitude = ((SecondOrderLabel*) newLabel)->getAmplitude() ; 
    double decay = ((SecondOrderLabel*) newLabel)->getDecay() ; 
    double period = ((SecondOrderLabel*) newLabel)->getPeriod() ; 
    double phaseShift = ((SecondOrderLabel*) newLabel)->getPhaseShift() ; 
    Matrix* rawSignal = newFilter->getSignal() ; 
    double error = 0.0 ; 
    int timeFromPeakCounter = 0 ;  // This counter is for the 1st-order impulse function
    int absoluteTimeCounter =   ((SecondOrderImpulseFilter*) newFilter)->getImpulseTime(); // This counter is for raw data, so it starts at the first peak.
    int totalTime = newFilter->getTotalTimePoints() ; 
    vector<double>* errorVector = new vector<double>(totalTime) ; 
    vector<double>* modelTraceVector = new vector<double>(totalTime) ; 

    fill(errorVector->begin(),errorVector->end(),0.0) ; 
    fill(modelTraceVector->begin(),modelTraceVector->end(),((SecondOrderImpulseFilter*) newFilter)->getBaseline(labelCount)) ; 
   

    while( absoluteTimeCounter < totalTime ){
        (*modelTraceVector)[absoluteTimeCounter] =  ( amplitude * exp( -timeFromPeakCounter * decay ) * sin( timeFromPeakCounter * period + phaseShift)  + ((SecondOrderImpulseFilter*) newFilter)->getBaseline(labelCount)) ; 
        (*errorVector)[absoluteTimeCounter] = fabs( (*rawSignal) ( absoluteTimeCounter,labelCount) -  (*modelTraceVector)[absoluteTimeCounter]  ) ; 
        ++absoluteTimeCounter ; 
        ++timeFromPeakCounter; 
    }


    newLabel->setErrorVector( errorVector ) ; 
    newLabel->setModelTraceVector( modelTraceVector ) ; 

    return error ; 
}

int SecondOrderImpulseLabelIdentifier::calculateErrorPoints(Label* newLabel,DataFilter* newFilter) 
{
    return newFilter->getTotalTimePoints() - (int) ((SecondOrderImpulseFilter*) newFilter)->getTimeToFirstPeak(newLabel->getLabelCount()) ; 
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


