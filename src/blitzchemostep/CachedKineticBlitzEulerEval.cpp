/*
 * $Id: CachedKineticBlitzEulerEval.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */



#include <iostream>
using std::cout ; 
using std::endl ; 

using std::min ; 
using std::max ; 

#include "KineticBlitzEulerEval.hpp"
#include "CachedKineticBlitzEulerEval.hpp"
#include "NeuralNetwork.hpp"
#include "FeederSet.hpp"
#include "SetFeeder.hpp"
#include "Feeder.hpp"



CachedKineticBlitzEulerEval::CachedKineticBlitzEulerEval() : KineticBlitzEulerEval()
    ,cacheStimulusVector(NULL)
    ,cacheTargetVector(NULL)
    ,cacheSetLengthsVector(NULL)
{
    cout << "constructing CachedKineticBlitzEulerEval" << endl ; 
}

CachedKineticBlitzEulerEval::~CachedKineticBlitzEulerEval() {
    delete cacheStimulusVector ; 
    delete cacheTargetVector ; 
    delete cacheSetLengthsVector ; 
}

double CachedKineticBlitzEulerEval::eval(NeuralNetwork* newNetwork) 
{
    if(newNetwork->getValid()==true){
        return newNetwork->getValue(); 
    }

    setNetwork(newNetwork)  ; 

    if(numSets==0 || cacheStimulusVector==NULL || cacheTargetVector==NULL || cacheSetLengthsVector==NULL ||  newNetwork->getValid() == false ){
        if(cacheFeeders()==false){
            throw "Problem caching feeder\n" ; 
        } 
    }


    /// For some reason, its better to leave the variables in here in terms of speed.  Probably reduces code bloat.  
    double timeCounter = 0 ; 
    double error = 0 ; 
    double targetPoint = 0 ; 
    double targetSig = 1 ; 
    double localError = 0 ; 
    int setLength = 0 ; 
    int feederCounter = 0 ; 

    currentNeuronPoint = 0 ; 
    currentErrorPoint = 0 ; 
    stimCount = 0 ; 
    targetCount = 0 ; 
    totalNetOutput= 0 ; 

    resetRelax() ; 


    for(int i = 0 ; i < cacheSetLengthsVector->rows() ; i++){
        // reset the network
        initEvaluator()  ; 
        resetNet()  ; 
        relaxNet() ;   ; 
        initEvaluator()  ; 
        // relax the network
        setLength = (int) (*cacheSetLengthsVector)(i) ; 

        // handle a single set
        for(int j = 0 ; j < setLength ; j++){
            for(int k = 0 ; k < numStimulus ; k++){
                (*inputVector)[k] = (*cacheStimulusVector)(feederCounter,k) ; 
            }


            targetPoint = (*cacheTargetVector)(feederCounter,0) ; 
            targetSig = (*cacheTargetVector)(feederCounter,1) ;  // just get the first feeder of the targets


//            if( (*cacheStimulusVector)(feederCounter,numStimulus)!=false){
            netOutput = evalPoint(inputVector,true) ; 
            totalNetOutput += netOutput ; 
            ++stimCount ; 
            if((stimCount*stimulus->getDeltaT())  >=  target->getDeltaT() ){
                ++targetCount; 
                // sum squared error
                localError = targetSig * pow((( totalNetOutput/ (double) stimCount)-targetPoint),2.0) ; 
                addErrorTrace(localError); 
                error += localError ; 
                stimCount= 0 ; 
                targetCount= 0 ; 
                totalNetOutput= 0 ; 
            }  // added error here to be averaged
//            }  // if a valid stimulus
            ++feederCounter ; 
        }  // a single training epoch
    }  // all training epochs

    newNetwork->setValue(error) ; 
    newNetwork->setValid(true) ; 
  return error ; 
}

bool CachedKineticBlitzEulerEval::cacheFeeders() 
{
    if(stimulus==NULL || target==NULL){
        // throw "stimulus or target not set" ; 
        return false  ;
    }


    // since we don't know what to do with networks, yet, just
    // compare the difference between two inputs and use that
    maxTime = min(target->getTotalTime(),stimulus->getTotalTime()) ;  // just need the first one
    mMinDeltaT= min(target->getDeltaT(),stimulus->getDeltaT()) ; 
    totalPoints = (int)  ceil(maxTime/mMinDeltaT) ;  // make a call to ceiling to counter rounding-off errors on x86
    theErrorPoints = (int)  (maxTime/target->getDeltaT()) ; 
    resetTrace(totalPoints,theErrorPoints) ; 

    // add the cached portion
    numSets = stimulus->getNumSets() ; 
    numStimulus = stimulus->getNumInputs() ; 
    numTargets = target->getNumInputs() ; 

    cacheSetLengthsVector = new Vector(numSets) ; 
    cacheStimulusVector = new Matrix(  (int) (stimulus->getTotalTime()/stimulus->getDeltaT()*numSets),numStimulus) ; 

    // add one row to the to the target to add significance
    cacheTargetVector = new Matrix( (int) (target->getTotalTime()/target->getDeltaT()*numSets),numTargets+1) ;


    int feederCounter2 = 0 ; 
    int prevFeederCount = 0 ; 
    int setCounter = 0 ; 
    double timeCounter = 0 ; 
    bool validStim = false ; 
    bool validTarget = false ; 
    double targetPoint   = 0.0 ; 
    double targetSig = 1.0  ; 

    stimulus->reset() ; 
    target->reset() ; 

    while( (float) timeCounter < (float) maxTime && stimulus->hasMorePoints() && target->hasMorePoints() ){
        if(stimulus->isNewSet() || target->isNewSet()){
            // just populate the cacheSetLengthsVector counter
            if(setCounter>0){
                (*cacheSetLengthsVector)(setCounter) = feederCounter2-prevFeederCount ; 
            }
            prevFeederCount = feederCounter2 ; 
            ++setCounter ; 
        }


        validStim = stimulus->isTimePointValid() ; 
        
        inputVector = stimulus->getNextTimeStepVector(mMinDeltaT) ; 

        for(int i = 0 ; i < numStimulus ; i++){
            (*cacheStimulusVector)(feederCounter2,i) = (*inputVector)[i] ; 
        }


        // this could be a loop at some point
        targetPoint = target->getNextTimeStep(mMinDeltaT) ; 
        targetSig = target->getNextSigTimeStep(mMinDeltaT,0) ;  // just get the first feeder of the targets
        (*cacheTargetVector)(feederCounter2,0) = targetPoint ; 
        (*cacheTargetVector)(feederCounter2,1) = targetSig ; 

        timeCounter+= mMinDeltaT ;
        ++feederCounter2 ; 
    }
    // handle the last loop
    (*cacheSetLengthsVector)(setCounter-1) = feederCounter2-prevFeederCount ; 

    return true ; 
}

void CachedKineticBlitzEulerEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"cachedkineticblitzeulereval\">" << endl ;
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}


//Matrix* CachedKineticBlitzEulerEval::cacheStimulusVector  = NULL ; 
//Matrix* CachedKineticBlitzEulerEval::cacheTargetVector = NULL ; 
//Vector* CachedKineticBlitzEulerEval::cacheSetLengthsVector = NULL ; 



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

