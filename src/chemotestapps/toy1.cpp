/*
 * $Id: toy1.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "StepFeeder.hpp"
#include "SetFeeder.hpp"
#include "FileFeeder.hpp"
#include "BlitzNet.hpp"
#include "BlitzEulerNetEvaluator.hpp"
#include "TextEvalTrace.hpp"
#include "PowerTempSchedule.hpp"  
#include "BlitzNetAnnealer.hpp"  
#include "toy1.hpp"

#ifdef DOMPI
    #include "mpi.h"
    int myid ; 
    int nprocs ; 
#endif 


toy1::toy1() 
{

    if(createToy()){
        cout << "toy created" << endl ; 
    }

    if(createEvaluator()){
        cout << "evaluator created" << endl ; 
    }


    toyNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 

    #ifdef DOMPI 
    MPI_Comm_rank(MPI_COMM_WORLD, &myid);
    MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
    if(myid==0){
    #endif
    cout << "toyNet->eval(): " << toyNet->eval() << endl ;
    cout << "toyNet->evalNorml(): " << toyNet->evalNorml() << endl ;
    cout << "toyNet->render()" << toyNet->render() << endl ;
    #ifdef DOMPI 
    }
    #endif 

    if(createAnnealer()){
        cout << "annealer created" << endl ; 
    }

    cout << "A" << endl ; 
    annealer->setAnnealingTarget(trainNet) ; 
    cout << "B" << endl ; 
}

bool toy1::anneal() {


    BlitzNet *greatNet = (BlitzNet*)  annealer->anneal() ; 
    cout << "C" << endl ; 
    cout << "trainNet: " << endl << trainNet->render() << endl ; 
    cout << "greatNet: " << endl << greatNet->render() << endl ; 
    greatNet->setEvaluator(blitzEval) ; 
    cout << "D" << endl ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "E" << endl ; 

    #ifdef DOMPI 
    if(myid==0){
    #endif
    cout << "greatNet->eval(): " << greatNet->eval() << endl ;
    cout << "greatNet->evalNorml(): " << greatNet->evalNorml() << endl ;
    cout << "greatNet->render(): " << greatNet->render() << endl ;
//    tracer->setTimeDelimiter(",") ; 
//    cout << "tracer->errorTrace(): " << endl << tracer->errorTrace() << endl ;
//    cout << "tracer->allNeuronTrace(): " << endl << tracer->allNeuronTrace() << endl ; 

    
    #ifdef DOMPI 
    }
    #endif


   return true ;  
}


bool toy1::createAnnealer() 
{
    trainNet = new BlitzNet() ; 
    trainNet->setNumNeurons(4) ; 

    perturber = new BlitzNetPerturber() ; 
    tempSchedule = new PowerTempSchedule() ;  
    annealer = new BlitzNetAnnealer() ; 

//    tempSchedule->setNumPoints(30) ; 
    tempSchedule->setNumPoints(1) ; 
    tempSchedule->setHighTemp(1.0) ; 
    tempSchedule->setLowTemp(0.001) ; 
    tempSchedule->setPower(2.0) ; 
    tempSchedule->initTemps() ; 

    trainNet->setPerturber(perturber) ; 
    trainNet->setEvaluator(blitzEval) ; 

    annealer->setTempSchedule(tempSchedule) ; 
//    annealer->setIterPerTemp(10000) ; 
    annealer->setIterPerTemp(1) ; 
    annealer->setAnnealingTarget(trainNet) ; 

    return true ; 
}


bool toy1::createEvaluator() 
{
    blitzEval = new BlitzEulerNetEvaluator() ; 
    tracer = new TextEvalTrace() ; 
    stimulus = new SetFeeder() ; 
    target = new SetFeeder() ; 
    stimA = new StepFeeder() ; 
    targetA = new FileFeeder() ; 
    stimB = new StepFeeder() ; 
    targetB = new FileFeeder() ; 

    stimA->setPreStepTime(120.0) ; 
    stimA->setPostStepTime(180.0) ; 
    stimA->setPreStepValue(0.5) ; 
    stimA->setPostStepValue(1.0) ; 
    targetA->setFile("../../DATA/TEST/set9respdt10_0.5_1.0.txt") ; 
    stimB->setPreStepTime(120) ; 
    stimB->setPostStepTime(180) ; 
    stimB->setPreStepValue(0.5) ; 
    stimB->setPostStepValue(0.0) ; 
    targetB->setFile("../../DATA/TEST/set9respdt10_0.5_0.0.txt") ; 

    stimulus->addFeeder(stimA) ; 
    stimulus->addFeeder(stimB) ; 
    stimulus->setScale(1.0/50.0) ; 
    stimulus->setDeltaT(0.1) ; 

    target->addFeeder(targetA) ; 
    target->addFeeder(targetB) ; 
    target->setDeltaT(10) ; 

    blitzEval->setStimulus(stimulus) ; 
    blitzEval->setTarget(target) ; 


    return true ; 
}


bool toy1::createToy() 
{
    toyNet = new BlitzNet() ; 
    weights = new Matrix(4,4) ; 
    tau = new Vector(4) ; 
    bias = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    toyNet->setNumNeurons(4) ; 

    (*weights) =  0,-4,-1,1,
    			  0,0,0,1,
    			  0,0,0,1,
    			  0,0,0,0;
    (*bias) = -0.5,2.0,0.5,-1.5 ; 
    (*tau) = 0.5,30,2,5 ; 
    (*initNeuron) = 0.5,0.5,0.5,0.5 ; 
    // set for 0.5 stim yields a rest value of 0.5 for all neurons
    toyNet->setWeights(weights) ; 
    toyNet->setBias(bias) ; 
    toyNet->setTau(tau) ; 
    toyNet->setInitNeuron(initNeuron) ; 

    return true ; 
}




/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    #ifdef DOMPI
        MPI_Init(&argc,&argv) ; 
        MPI_Comm_rank(MPI_COMM_WORLD,&myid) ; 
        MPI_Comm_size(MPI_COMM_WORLD,&nprocs) ; 
    #endif 
    toy1 *toy = new toy1() ; 
    toy->anneal() ; 



    #ifdef DOMPI
        MPI_Finalize() ; 
    #endif 

    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/active/auto3/src/chemotestapps/toy1.cpp"
// LAST MODIFICATION: "Sat, 15 Nov 2003 17:52:45 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: toy1.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

