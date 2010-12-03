/*
 * $Id: AutoWKineticBlitzEulerEval.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */

#include <vector>
using std::vector ; 

using std::max ; 
using std::min ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "float.h"
#include "KineticBlitzEulerEval.hpp"
#include "AutoWKineticBlitzEulerEval.hpp"
#include "Feeder.hpp"
#include "FeederSet.hpp"
#include "FileFeeder.hpp"

AutoWKineticBlitzEulerEval::AutoWKineticBlitzEulerEval() : KineticBlitzEulerEval()
,hVector(NULL)
,doTrace(false) 
,initDeltaW(1.0) 
,initLowDeltaValue(0.001) 
{
    cout << "constructing AutoWKineticBlitzEulerEval" << endl ; 
}

AutoWKineticBlitzEulerEval::~AutoWKineticBlitzEulerEval() {
    delete input ; 
    delete sigma ; 
}

double AutoWKineticBlitzEulerEval::getInitDeltaW() 
{
    return initDeltaW ; 
}

void AutoWKineticBlitzEulerEval::setInitDeltaW(double newInitDeltaW) 
{
    initDeltaW = newInitDeltaW ; 
}


/// This calculates the h value at every timepoint using eval. 
double AutoWKineticBlitzEulerEval::eval(NeuralNetwork* newNetwork) 
{
    if(stimulus==NULL || target==NULL){
        // throw "stimulus or target not set" ; 
        return 0 ;
    }
    setNetwork(newNetwork)  ; 

    // since we don't know what to do with networks, yet, just
    // compare the difference between two inputs and use that
    maxTime = min(target->getTotalTime(),stimulus->getTotalTime()) ; 
    mMinDeltaT = min(target->getDeltaT(),stimulus->getDeltaT()) ; 
    totalPoints = (int)  (maxTime/mMinDeltaT) ; 
    theErrorPoints = (int)  (maxTime/target->getDeltaT()) ; 
    resetTrace(totalPoints,theErrorPoints) ; 

    double timeCounter = 0 ; 
    double error = 0 ; 
//    double stimPoint = 0 ; 
    vector<double>* stimVector = NULL ; 
    double targetPoint = 0 ; 
    double targetSig = 1 ; 

    stimulus->reset() ; 
    target->reset() ; 

    bool validStim; 
    bool validTarget; 

    currentNeuronPoint = 0 ; 
    currentErrorPoint = 0 ; 
    if (hVector==NULL || hVector->size() != stimulus->getNumPoints() ){
     	hVector = new vector<double>(stimulus->getNumPoints()) ; 
    }

    int i = 0 ; 
    while(timeCounter < maxTime && stimulus->hasMorePoints() && target->hasMorePoints() ){
        if(stimulus->isNewSet() || target->isNewSet()){
            // reset the network
            resetNet()  ; 
            // relax the network
            relaxNet() ;    
        }
        validStim = stimulus->isTimePointValid() ; 
        validTarget = target->isTimePointValid() ; 
//        stimPoint = stimulus->getNextTimeStep(mMinDeltaT) ; 
        stimVector = stimulus->getNextTimeStepVector(mMinDeltaT) ; 
        targetPoint = target->getNextTimeStep(mMinDeltaT) ; 
       
        if(validStim){
            (*hVector)[i] = eval(stimVector,targetPoint) ; 
        }
        timeCounter+= mMinDeltaT ;
        i++ ; 
    }

    return findBestError(  (*evalWeights)(evalNeurons->size()-1,evalNeurons->size()-1) ) ; 


//    return 0 ; 
}

double AutoWKineticBlitzEulerEval::findBestError(double initW) 
{
    double currentError = 0 ; 
    double previousError = 0 ; 
    double bestError = DBL_MAX ; 

    double currentW = initW ; 
    double bestW = 0 ; 

    bool finished = false ; 
    double deltaW  ; 

    // implement gradient-descent error



    // our best set is our starting point, initially
    bestW = initW;
    bestError = calculateError(initW) ; 
    currentError = bestError ; 

    // initial movement is up
    double deltaValue = initDeltaW ; 
    deltaW = initDeltaW ; 
    double lowDeltaValue = initLowDeltaValue ; 
    double prevDeltaError; 
    double strike = 0 ; 

    // while there is no improvement either direction
    int counter = 0 ; 
    while(!finished){
        previousError = currentError ; 
        currentW += deltaW ; 
        currentError = calculateError(currentW) ; 
        prevDeltaError = currentError - previousError ; 
        if(deltaW *(currentError - previousError) > 0 ){
            deltaW = -deltaValue ; 
        }
        else 
        if(deltaW * (currentError - previousError) < 0 ){
            deltaW = deltaValue ; 
        }

        if(currentError <  bestError){
            bestError = currentError ; 
            bestW = currentW ; 
        }
//        cout << "currentW: " << currentW << " deltaW: " << deltaW << " currentError: " << currentError << " previousError: " << previousError << " deltaError: " << (currentError-previousError)  << "prevDeltaError: " << prevDeltaError << endl ; 

        if( (prevDeltaError) >0){
            ++strike ; 
        }
        else{
            strike = 0 ; 
        }

        if(strike>=1 && counter > 0 ){
            deltaValue = deltaValue / 10.0 ; 
            strike = 0 ; 
        }
        if(deltaW==0 || deltaValue<=lowDeltaValue || counter > 200){
            finished = true ; 
        }
        ++counter ; 
    }

//    cout << "numAdjustments: " << counter << endl ; 
   
    // add the error trace
    calculateError(bestW,true) ; 

//     do this at the very end once we have the best value
    (*outputVector)[evalNeurons->size()-1] = P0 ; 

    setBestW(bestW) ; 


    return bestError ; 
}/// Optimize w for the target using gradient descent (or a variation thereof). 


void AutoWKineticBlitzEulerEval::setLowDeltaValue(double newLowDeltaValue) 
{
    initLowDeltaValue = newLowDeltaValue ; 
}



/// Based on a particular h, calculate lowest error for w's using gradient descent.
double AutoWKineticBlitzEulerEval::calculateError(double currentW,bool doTrace) 
{
    double currentH ; 
    double localError = 0 ; 
    double currentTarget ; 
    double P0avg,timeCount ; 

    // calculated P_forward or P_0 from h and w
    // for each h in hVector . . . calculate testError (P0 - target) at each time-point
    target->reset() ; 

    P1 = initP1 ; 
    P0= initP0 ; 
    P0avg = 0 ; 
    timeCount = 1 ; 
    for(int i = 0 ; i < hVector->size() ; i++){
        currentH = (*hVector)[i] ; 
        k01 = 1/(1+exp(-currentH )  ) ;   // k01 = sigma(h) 
        k10 = 1 - 1/(1+exp(- (currentH+ currentW )  )  ) ;   // k10 = sigma(h+w) ; 

        if(P1 < 0 || P0 < 0){ // we are at the starting condition
        // set the values to their initial steady-state values
            P1 =   k01 / (k01+k10) ; 
        }
        else{
            P1 = P1 + mMinDeltaT* ( k01 + k10) * ( -P1 + ( k01 / (k01+k10))) ; 
        }
        P0 = 1 - P1 ; 

        // set the last neuron to P0 - ouch
        // we assume that the other neurons have already been set
        (*(*neuronTrace)[i])[evalNeurons->size()-1] = P0 ; 

        currentTarget= target->getNextTimeStep(mMinDeltaT) ; 

        P0avg += P0 ; 
        if(timeCount >=  (target->getDeltaT() / stimulus->getDeltaT())   ) { 
            P0avg = P0avg / (timeCount) ; 
            localError +=  fabs( P0avg - currentTarget ) ; 
            if(doTrace){
//                addErrorTrace(  fabs( P0avg - currentTarget )  ) ; 
                addErrorTrace(  pow ( ( P0avg - currentTarget ),2.0  ) ) ; 
            }
            P0avg = 0 ; 
            timeCount = 0 ; 
        }
        timeCount += mMinDeltaT ; 
    }

    // set the last neuron to P0?

    return localError ; 
}

double AutoWKineticBlitzEulerEval::getBestW() 
{
    return bestW ; 
}

double AutoWKineticBlitzEulerEval::setBestW(double newBestW) 
{
    bestW = newBestW ; 
}



// note we may lose this later if not quick enough
//double BlitzEulerNetEvaluator::eval(double stim,double target,bool doTrace) 
double AutoWKineticBlitzEulerEval::eval(vector<double>* stimVector,bool newDoTrace) 
{
    doTrace = newDoTrace ; 
    // eval for the point 
  
    long double aOne = 1.0 ; 
    (*input) = (*evalNeurons) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...
    (*sigma) = (1.0 / (1.0 + exp( -(*input) )));
    
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*sigma)(i) = (*stimVector)[i];
        (*evalNeurons)(i) = (*stimVector)[i];
    }
    (*evalNeurons) += ( ( (*sigma) - (*evalNeurons) ) / (*evalTau) ) * localDt;
    if(doTrace){
        for(int i = 0  ; i < evalNeurons->size() ; i++){
            (*outputVector)[i] = (*evalNeurons)(i) ; 
        }
        addNeuronTrace( outputVector ) ; 
    }

    // sum all interneurons going onto the output neuron
    // or implement as:    
//             sumh = (*evalNeurons)(Range::all()) * (*evalWeights)(Range::all(),evalNeurons->size()-1)
    double sumh = 0 ; 
    for(int i = 0  ; i < evalNeurons->size()-1 ; i++){ // allow kinections from initial neuron
        sumh += (*evalNeurons)(i) * (*evalWeights)(i,evalNeurons->size()-1); 
    }
//    cout << "sumh: " << sumh << endl ; 
    return sumh ; 
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
// FILE: "/Users/ndunn/tla/auto3--nathanevo--1.4.2--patch-33/src/blitzchemostep/AutoWKineticBlitzEulerEval.cpp"
// LAST MODIFICATION: "Wed, 07 Jul 2004 12:00:52 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AutoWKineticBlitzEulerEval.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

