/*
 * $Id: autowtest.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetPerturber.hpp" 
#include "BlitzEulerNetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 
#include "AutoWKineticBlitzEulerEval.hpp" 


#include "autowtest.hpp"

autowtest::autowtest(): 
	testsPassed(0)  
    ,testsRun(0)  
{
    if(!initData()){
        cout << "could not initialize the data" << endl ; 
        exit(0) ; 
    }
}

inline bool autowtest::rendertests(string description, bool results) 
{
    if(results){
        cout << description << ":  [PASS]" << endl ; 
        ++testsPassed ;
    }
    else{
        cout << description << ":  [FAIL]" << endl ; 
    }
    ++testsRun ; 

    return results ; 
}


bool autowtest::initData() 
{
    try{
        
    blitzNet = new BlitzNet() ; 
    evaluator = new AutoWKineticBlitzEulerEval() ;    
    // set feeders
    stimLeft = new FileFeeder() ; 
    stimRight = new FileFeeder() ; 
    targetSet = new FileFeeder() ; 
    // stim feeders
    stimLeft->setDeltaT(1.0) ; 
    stimRight->setDeltaT(1.0) ; 
    targetSet->setDeltaT(1.0) ; 
    stimLeft->setFile("../../DATA/TEST/stimEleft.txt") ; 
    stimRight->setFile("../../DATA/TEST/stimFright.txt") ; 
    targetSet->setFile("../../DATA/TEST/testsetE.txt") ; 
    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.5 ; 
    (*relaxVector)[1] = 0.5 ; 
    evaluator->setRelaxValue(relaxVector) ; 
    evaluator->setK10(0.7351243) ; 
    evaluator->setK01( 0.727093 ) ; 
    evaluator->setStimulus(stimLeft,0) ; 
    evaluator->setStimulus(stimRight,1) ; 
    evaluator->setTarget(targetSet) ; 
    evaluator->setRelaxTime(50) ; 
    evaluator->setRelaxDeltaT(1) ; 
    evaluator->setRelaxTau(3) ; 

    weights = new Matrix(4,4) ; 
    weightMask = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    biasMask = new Vector(4) ; 
    tau = new Vector(4) ; 
    tauMask = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    initNeuronMask= new Vector(4) ; 
    tracer = new TextEvalTrace() ; 
    tracer->setTimeDelimiter(",") ; 
    blitzNet->setNumNeurons(4) ; 
    *weights = 0 ; 
    *bias = 0 ; 
    *tau = 5 ; 
    *initNeuron = 0.5 ; 
//    *biasMask = 1 ; 
//    *tauMask = 1 ; 
//    *initNeuronMask = 0 ; 
//    (*weightMask) =  0,1,1,1,
//                     0,1,1,1,
//                     0,1,1,1,
//                     0,0,0,1;
//    (*weights) = 0 ; 
//    (*weights) =  0,0,0,0,
//                  0,0,0,0,
//                  0,0,0,0,
//                  0,0,0,0;
//    (*weights) =  0,0,10,2,  // the real answer
//                  0,0,-10,0,
//                  0,0,0,-3,
//                  0,0,0,-2;
    (*weights) =  0,0,10,2,  // the real answer
                  0,0,-10,0,
                  0,0,0,-3,
                  0,0,0,-2;
//                  0,0,0,-37.417;
    (*bias) = -5,-5,-5,-5 ;   // only the middle bias matters
    (*tau) = 30,30,30,30 ; 
    (*initNeuron) = 0.5,0.5,0.00669285 ,0.4098808 ;  // should be the final answer
//    (*initNeuron) = 0.5,0.5,0.5,0.5; 
    blitzNet->setWeights(weights) ; 
//    blitzNet->setWeightMask(weightMask) ; 
    blitzNet->setBias(bias) ; 
//    blitzNet->setBiasMask(biasMask) ; 
    blitzNet->setTau(tau) ; 
//    blitzNet->setTauMask(tauMask) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
//    blitzNet->setInitNeuronMask(initNeuronMask) ; 
    blitzNet->setEvaluator(evaluator) ; 
    tracer->setEvaluator(evaluator) ; 


    }
    catch(...){
        cout << "an error ? " << endl ; 
        return false ; 
    }

    return true ; 
}


int autowtest::runtests(){


    dotest1() ; 
    dotest2() ; 

    cout << "-----------\n-----------" << endl ; 
    cout << "number of tests passed: "  << testsPassed   << endl ; 
    cout << "number of tests run: "  << testsRun  << endl ; 
    return testsPassed ; 
}

bool autowtest::dotest1() 
{
    cout << "----------\ntest 1\n-----------" << endl ; 

    evaluator->setInitDeltaW(1.0) ; 
    evaluator->setLowDeltaValue(0.0001) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "bestW: " << evaluator->getBestW() << endl ; 
//    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    cout << "all neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    cout << "last neuronTrace: " << endl << tracer->lastNeuronTrace() << endl ; 
//    cout << "target trace: " << endl << tracer->targetTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0)) < 0.001) ; 
    return rendertests("test 1",status); 
}


bool autowtest::dotest2() 
{
    cout << "----------\ntest 2\n-----------" << endl ; 

    delete targetSet ; 
    targetSet = new FileFeeder() ; 
    targetSet->setDeltaT(10.0) ; 
    targetSet->setFile("../../DATA/TEST/targetDelta10.txt") ; 
    evaluator->setTarget(targetSet) ; 

//    evaluator->setInitDeltaW(1.0) ; 
//    evaluator->setLowDeltaValue(0.0001) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "bestW: " << evaluator->getBestW() << endl ; 
//    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "all neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "last neuronTrace: " << endl << tracer->lastNeuronTrace() << endl ; 
    cout << "target trace: " << endl << tracer->targetTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0)) < 0.001) ; 
    return rendertests("test 2",status); 
}


/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    cout << "running tests: " << endl ; 
    autowtest *test = new autowtest() ; 
    test->runtests() ; 

    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemotestapps/autowtest.cpp"
// LAST MODIFICATION: "Sun, 14 Dec 2003 07:49:42 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: autowtest.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

