
#include <iostream>
using std::cout ; 
using std::endl ; 

using std::max ; 
using std::min ; 

#include <math.h>

#include "BinNetEvaluator.hpp"
#include "NeuralNetwork.hpp"
#include "Feeder.hpp"
#include "FeederSet.hpp"



BinNetEvaluator::BinNetEvaluator()  : NetEvaluator() {
}


double BinNetEvaluator::eval(NeuralNetwork* newNetwork) 
{
    if(newNetwork->getValid()==true){
//        cout << "Net is VALID" << endl ; 
        return newNetwork->getValue(); 
    }

    
//    cout << "evaluating in BinNetEvaluator" << endl ; 
    if(stimulus==NULL || target==NULL){
         throw "stimulus or target not set" ; 
//        return 0 ;
    }
    setNetwork(newNetwork)  ; 
   
    // since we don't know what to do with networks, yet, just
    // compare the difference between two inputs and use that
   
    
    maxTime = min(target->getTotalTime(),stimulus->getTotalTime()) ;  // just need the first one
    mMinDeltaT = min(target->getDeltaT(),stimulus->getDeltaT()) ; 
    totalPoints = (int)  ceil(maxTime/mMinDeltaT ) ;  // make a call to ceiling to counter rounding-off errors on x86
    theErrorPoints = (int)  (maxTime/target->getDeltaT()) ; 

//    cout << "stimulus total time: " << stimulus->getTotalTime() << endl ; 
//    cout << "target total time: " << target->getTotalTime() << endl ; 
//    cout << "stimulus number points: " << stimulus->getNumPoints() << endl ; 
//    cout << "target number points: " << target->getNumPoints() << endl ; 
//    cout << "maxTime: " << maxTime << endl ;
//    cout << "mMinDeltaT: " << mMinDeltaT << endl ;
//    cout << "totalPoints: " << totalPoints << endl ;
//    cout << "theErrorPoints: " << theErrorPoints << endl ;

    resetTrace(totalPoints,theErrorPoints) ; 


    /// For some reason, its better to leave the variables in here in terms of speed.  Probably reduces code bloat.  
    double timeCounter = 0 ; 
    double error = 0 ; 
//    double stimPoint = 0 ; 
    double targetPoint = 0 ; 
    double targetSig = 1 ; 
    double localError ; 
    bool validStim; 
    bool validTarget; 


    stimulus->reset() ; 
    target->reset() ; 


    currentNeuronPoint = 0 ; 
    currentErrorPoint = 0 ; 
    stimCount = 0 ; 
    targetCount = 0 ; 
    totalNetOutput= 0 ; 

    resetRelax() ; 

    // we cast it back, just in case of any roundoff errors
    while( (float) timeCounter < (float) maxTime && stimulus->hasMorePoints() && target->hasMorePoints() ){
        if(stimulus->isNewSet() || target->isNewSet()){
            // reset the network
            initEvaluator()  ; 
            resetNet()  ; 
            relaxNet() ;   ; 
            initEvaluator()  ; 
            // relax the network
        }
        validStim = stimulus->isTimePointValid() ; 
        validTarget = target->isTimePointValid() ; 
        // TODO: get vector of vectors, here
        inputVector = stimulus->getNextTimeStepVector(mMinDeltaT) ; 

        // TODO: get vector here
        targetPoint = target->getNextTimeStep(mMinDeltaT) ; 
        // TODO: get vector here
        targetSig = target->getNextSigTimeStep(mMinDeltaT,0) ;  // just get the first feeder of the targets

//        cout << "targetSig: " << targetSig << endl ; 
//        cout << "  timeCounter: "<< timeCounter ; 
//        cout << "  validStim: "<< validStim ; 
//        cout << "  validTarget: "<< validTarget << endl ; 
        if(validStim  ){
            netOutput = evalPoint(inputVector) ; 
            totalNetOutput += netOutput ; 
            ++stimCount ; 

            if((stimCount*stimulus->getDeltaT())>=target->getDeltaT() ){
                ++targetCount; 
                // Using sum-squared error
                 localError = targetSig * pow((( totalNetOutput/ (double) stimCount)-targetPoint),2.0) ; 
                addErrorTrace(localError); 
                error += localError ; 
//                cout << "  timeCounter: " << timeCounter  ; 
//                cout << "  totalNetOutput: " << totalNetOutput  ; 
//                cout << "  stimCount: " << stimCount  ; 
//                cout << "  targetCount: " << targetCount ; 
//                cout << "  targetPoint: " << targetPoint  ; 
//                cout << "  localError: " << localError  ; 
//                cout << "  error: " << error  ; 
                stimCount= 0 ; 
                targetCount= 0 ; 
                totalNetOutput= 0 ; 
            }
        }
        timeCounter+= mMinDeltaT ;
    }

    newNetwork->setValue(error) ; 
    newNetwork->setValid(true) ; 

    return error ; 
}

/**  Sets the relax vector back to the original initNeuron Vector, necessary after each perturbation.
 * 
 * In BinNetEvaluator it does nothing.
 */
bool BinNetEvaluator::resetRelax()   
{
    return true; 
}


double BinNetEvaluator::evalPoint(vector<double>* stimVector, bool doTrace) 
{
    // this should be the network stimulus fed into the network and then calculated but . . . 
    // for simplicity
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*outputVector)[i] =  (*stimVector)[i] ; 
    }
    
    if(doTrace){
        addNeuronTrace( outputVector ) ; 
    }
   
    return (*outputVector)[0] ; 
}

void BinNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"binetevaluator\">" << endl ;
  doBaseXML(s) ; 
  addSpacer(s,-1) ; 
  // close the XML
  *s << "</evaluator>" << endl ;
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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

