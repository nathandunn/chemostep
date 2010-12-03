/*
 * $Id: test3cache.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $
 */

//#include <iostream>
//using std::cout ; 
//using std::endl ; 

#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetPerturber.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 
#include "CachedKineticBlitzEulerEval.hpp" 
#include "BinNetEvaluator.hpp" 


#include "test3cache.hpp"

test3cache::test3cache(): testsPassed(0)  
    ,testsRun(0)  
{
    if(!initData()){
        cout << "could not initialize the data" << endl ; 
        exit(0) ; 
    }
}

inline bool test3cache::rendertests(string description, bool results) 
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


bool test3cache::initData() 
{
    try{
        
    tracer = new TextEvalTrace() ; 
    stimA = new StepFeeder() ; 
    targetA = new FileFeeder() ; 
    stimB = new StepFeeder() ; 
    targetB = new FileFeeder() ; 
    stimC = new StepFeeder() ; 
    stimD = new StepFeeder() ; 
    stimE = new FileFeeder() ; 
    stimF = new FileFeeder() ; 
    targetC = new FileFeeder() ; 
    targetE = new FileFeeder() ; 
    regNet = new NeuralNetwork() ; 
    netEval = new BinNetEvaluator() ; 
    blitzNet = new BlitzNet() ; 
    kineticEval = new CachedKineticBlitzEulerEval() ; 
    weights = new Matrix(3,3) ; 
    tau = new Vector(3) ; 
    bias = new Vector(3) ; 
    initNeuron = new Vector(3) ; 
    blitzNet->setNumNeurons(3) ; 

    tracer->setTimeDelimiter(",") ; 
    stimA->setPreStepTime(2.0) ; 
    stimA->setPostStepTime(4.0) ; 
    stimA->setPreStepValue(3.0) ; 
    stimA->setPostStepValue(7.0) ; 
    targetA->setFile("../../DATA/TEST/testsetA.txt") ; 
    stimB->setPreStepTime(2.0) ; 
    stimB->setPostStepTime(2.0) ; 
    stimB->setPreStepValue(0.5) ; 
    stimB->setPostStepValue(0.5) ; 
    targetB->setFile("../../DATA/TEST/testsetB.txt") ; 
    targetB->loadSigFile("../../DATA/TEST/testsetsigB.txt") ; 
    targetC->setFile("../../DATA/TEST/testsetC.txt") ; 

    (*weights) =  0,1,1,
    			  0,0,-1,
    			  0,0,0;
    (*bias) = -0.5,-0.5,0 ; 
    (*tau) = 5,5,5 ; 
    (*initNeuron) = 0.5,0.5,0.5 ; 
    // set for 0.5 stim yields a rest value of 0.5 for all neurons
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 




    }
    catch(...){
        cout << "an error ? " << endl ; 
        return false ; 
    }

    return true ; 
}


int test3cache::runtests(){


    dotest1() ; 
    dotest2() ; 
    dotest3() ; 
    dotest4() ; 
    dotest5() ; 
    dotest6() ; 
    dotest7() ; 
    dotest8() ; 
    dotest9() ; 

    cout << "-----------\n-----------" << endl ; 
    cout << "number of tests passed: "  << testsPassed   << endl ; 
    cout << "number of tests run: "  << testsRun  << endl ; 
    return testsPassed ; 
}

bool test3cache::dotest1() 
{
    cout << "----------\ntest 1\n-----------" << endl ; 
    stimA->setDeltaT(1.0) ; 
    targetA->setDeltaT(1.0) ; 
    netEval->setStimulus(stimA) ; 
    netEval->setTarget(targetA) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 

    cout << "stimA->getNumPoints():  " << stimA->getNumPoints() << endl ; 
    cout << "targetA->getNumPoints():  " << targetA->getNumPoints() << endl ; 
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // (4-2)^2 * 1 
    bool status = ( fabs(regNet->evalNorml()- (16.0/6.0)) < 0.001) ; 
    return rendertests("test 1",status); 
}

bool test3cache::dotest2() 
{
    cout << "----------\ntest 2\n-----------" << endl ; 
    cout << "does this work for 1 input?" << endl ; 
    stimB->setDeltaT(1.0) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetD.txt") ; 
    kineticEval->setStimulus(stimB) ; 
    kineticEval->setTarget(targetB) ; 
    (*weights) =  0,1,0,
    			  0,0,1,
    			  0,0,-1 ;
    (*bias) = -2,-0.5,3 ;   // only the middle bias matters
    (*tau) = 5,5,5 ; 
    (*initNeuron) = 0.5,0.5 ,0.5 ;  
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "precache " << endl ; 
    kineticEval->cacheFeeders() ; 
    cout << "postcache " << endl ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimB->getNumPoints():  " << stimB->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl << endl  ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl << endl ; 
    // o.04 + 0.04 + 0.0149963 + 0.09 = 0.1849963
    bool status = ( fabs(blitzNet->evalNorml()- (0.1849963/4.0)) < 0.000001) ; 
    return rendertests("test 2",status); 
}

bool test3cache::dotest3() 
{
    cout << "----------\ntest 3\n-----------" << endl ; 
    cout << "does this work for 2 interneurons?" << endl ; 
    stimB->setDeltaT(1.0) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetD.txt") ; 
    kineticEval->setStimulus(stimB) ; 
    kineticEval->setTarget(targetB) ; 
    weights = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    tau = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,1,1,0,
    			  0,0,0,0.5,
    			  0,0,0,0.5,
    			  0,0,0,-1.244918;
    (*bias) = -2,0,0,2 ;   // only the middle bias matters
    (*tau) = 5,5,5,5 ; 
    (*initNeuron) = 0.5,0.6225,0.6225,0.5 ; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimB->getNumPoints():  " << stimB->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // 0.185
    bool status = ( fabs(blitzNet->evalNorml()- (0.185/4.0)) < 0.00001) ; 
    return rendertests("test 3",status); 
}

bool test3cache::dotest4() 
{
    cout << "----------\ntest 4\n-----------" << endl ; 
    cout << "does this work for 2 inputs?" << endl ; 
    stimC->setDeltaT(1.0) ; 
    stimD->setDeltaT(1.0) ; 
    stimC->setPreStepTime(2.0) ; 
    stimC->setPostStepTime(2.0) ; 
    stimC->setPreStepValue(0.3) ; 
    stimC->setPostStepValue(0.3) ; 
    stimD->setPreStepTime(2.0) ; 
    stimD->setPostStepTime(2.0) ; 
    stimD->setPreStepValue(0.2) ; 
    stimD->setPostStepValue(0.2) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetD.txt") ; 
    kineticEval->setStimulus(stimC,0) ; 
    kineticEval->setStimulus(stimD,1) ; 
    kineticEval->setTarget(targetB) ; 
//    weights = new Matrix(4,4) ; 
//    bias = new Vector(4) ; 
//    tau = new Vector(4) ; 
//    initNeuron = new Vector(4) ; 
//    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,0,1,0,
    			  0,0,1,0,
    			  0,0,0,1,
    			  0,0,0,-1.244918;
    (*bias) = -2,9,0,2 ;   // only the middle bias matters
    (*tau) = 5,5,5,5 ; 
    (*initNeuron) = 0.3,0.2,0.62246,0.5 ; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimB->getNumPoints():  " << stimB->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.184996/4.0)) < 0.000001) ; 
    return rendertests("test 4",status); 
}

bool test3cache::dotest5() 
{
    cout << "----------\ntest 5\n-----------" << endl ; 
    stimC->setDeltaT(1.0) ; 
    stimD->setDeltaT(1.0) ; 
    stimC->setPreStepTime(2.0) ; 
    stimC->setPostStepTime(2.0) ; 
    stimC->setPreStepValue(0.2) ; 
    stimC->setPostStepValue(0.2) ; 
    stimD->setPreStepTime(2.0) ; 
    stimD->setPostStepTime(2.0) ; 
    stimD->setPreStepValue(0.3) ; 
    stimD->setPostStepValue(0.3) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetD.txt") ; 
//   kineticEval->setRelaxTime(50) ; 
//   kineticEval->setRelaxDeltaT(1) ; 
//   kineticEval->setRelaxValue(0.5) ; 
    kineticEval->setStimulus(stimC,0) ; 
    kineticEval->setStimulus(stimD,1) ; 
    kineticEval->setTarget(targetB) ; 
    weights = new Matrix(6,6) ; 
    bias = new Vector(6) ; 
    tau = new Vector(6) ; 
    initNeuron = new Vector(6) ; 
    blitzNet->setNumNeurons(6) ; 
    (*weights) =  0,0,1,1,0,0,
    			  0,0,0,1,1,0,
    			  0,0,0,0,0,-1,
    			  0,0,0,0,-1,0.5,
    			  0,0,0,0,0,1,
    			  0,0,0,0,0,-0.5;
    (*bias) = 0,0,-0.2,-0.5,0.2,0.5 ;   // only the middle bias matters
    (*tau) = 5,5,5,5,5,5 ; 
    (*initNeuron) = 0.2,0.3,0.5,0.5,0.5,0.5; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimB->getNumPoints():  " << stimB->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // 0.25 - 0.7, 0.3 - 0.25, 0.6224593 - 0.25, 0.8-0.25 = 1.4224593
    bool status = ( fabs(blitzNet->evalNorml()- (0.184996/4.0)) < 0.000001) ; 
    return rendertests("test 5 (we don't care what the last neuron is)",status); 
}


bool test3cache::dotest6() 
{
    cout << "----------\ntest 6\n-----------" << endl ; 
    cout << "Relaxed, bad init, two inputs, three interneurons." << endl ; 
    kineticEval->setRelaxTime(100) ; 
    kineticEval->setRelaxDeltaT(1) ; 
    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.2 ; 
    (*relaxVector)[1] = 0.3 ; 
    kineticEval->setRelaxValue(relaxVector) ; 
    kineticEval->setStimulus(stimC,0) ; 
    kineticEval->setStimulus(stimD,1) ; 
    kineticEval->setTarget(targetB) ; 
    (*initNeuron) = 0.0,0.0,0.0,0.0,0.0,0.0; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
//    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // 0.25 - 0.7, 0.3 - 0.25, 0.6224593 - 0.25, 0.8-0.25 = 1.4224593
    bool status = ( fabs(blitzNet->evalNorml()- (0.184996/4.0)) < 0.000001) ; 
    return rendertests("test 6",status); 
}


bool test3cache::dotest7() 
{
    cout << "----------\ntest 7\n-----------" << endl ; 
    cout << "Is this the same as Shawn's network (static) ?" << endl ; 
    weights = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    tau = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    blitzNet->setNumNeurons(4) ; 
//    (*weights) =  0,0,10,2,
//                  0,0,-10,0,
//                  0,0,0,-3,
//                  0,0,0,-2;
    (*weights) =  0,0,-10,0,
    			  0,0,10,2,
    			  0,0,0,-3,
    			  0,0,0,-2;
    (*bias) = -5,-5,-5,-5 ;   // only the middle bias matters
    (*tau) = 30,30,30,30 ; 
    (*initNeuron) = 0.5,0.5,0.00669285 ,0.502746;  // should be the final answer
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    stimC->setPreStepValue(0.5) ; 
    stimC->setPostStepValue(0.5) ; 
    stimD->setPreStepValue(0.5) ; 
    stimD->setPostStepValue(0.5) ; 
    kineticEval->setRelaxTime(0) ; 
    kineticEval->setStimulus(stimC,0) ; 
    kineticEval->setStimulus(stimD,1) ; 
    kineticEval->setTarget(targetB) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimC->getNumPoints():  " << stimC->getNumPoints() << endl ; 
    cout << "stimD->getNumPoints():  " << stimD->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // 0.7 -0.502746, 0.3 - 0.502746, 0.6224593 - 0.502746, 0.8-0.502746 = 0.816967
    bool status = ( fabs(blitzNet->evalNorml()- (0.182029/4.0)) < 0.001) ; 
    return rendertests("test 7",status); 
}


bool test3cache::dotest8() 
{
    cout << "----------\ntest 8\n-----------" << endl ; 
    cout << "Is this Shawn's network? (dynamic)" << endl ; 
    stimE->setDeltaT(1.0) ; 
    stimF->setDeltaT(1.0) ; 
    stimE->setFile("../../DATA/TEST/a0big.txt") ; 
    stimF->setFile("../../DATA/TEST/a1big.txt") ; 
    targetE->setDeltaT(1.0) ; 
    targetE->setFile("../../DATA/TEST/Pfor_up_big.txt") ; 
   kineticEval->setRelaxTime(100) ; 
   kineticEval->setRelaxDeltaT(1) ; 
   kineticEval->setRelaxTau(3) ; 
    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.5 ; 
    (*relaxVector)[1] = 0.5 ; 
    kineticEval->setRelaxValue(relaxVector) ; 
//    kineticEval->setK10(0.7351243) ; 
//    kineticEval->setK01( 0.727093 ) ; 
    kineticEval->setStimulus(stimE,0) ; 
    kineticEval->setStimulus(stimF,1) ; 
    kineticEval->setTarget(targetE) ; 
    weights = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    tau = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    blitzNet->setNumNeurons(4) ; 
//    (*weights) =  0,0,10,2,
//                  0,0,-10,0,
//                  0,0,0,-3,
//                  0,0,0,-2;
    (*weights) =  0,0,-10,0,
    			  0,0,10,2,
    			  0,0,0,-3,
    			  0,0,0,-2;
    (*bias) = -5,-5,-5,-5 ;   // only the middle bias matters
    (*tau) = 30,30,30,30 ; 
    (*initNeuron) = 0.5,0.5,0.00669285 ,0.4098808 ;  // should be the final answer
//    (*initNeuron) = 0.5,0.5,0.5,0.5; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "stimE->getNumPoints():  " << stimE->getNumPoints() << endl ; 
//    cout << "stimF->getNumPoints():  " << stimF->getNumPoints() << endl ; 
//    cout << "targetC->getNumPoints():  " << targetE->getNumPoints() << endl ; 
//    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
//    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    cout << "lastneuronTrace: " << endl << tracer->lastNeuronTrace() << endl ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0)) < 0.000001) ; 
    return rendertests("test 8",status); 
}

bool test3cache::dotest9() 
{
    cout << "----------\ntest 9\n-----------" << endl ; 
    cout << "Toy 2, big up, big down, small up, small down." << endl ; 
    SetFeeder *stimLeft = new SetFeeder() ; 
    FileFeeder *stimLeft1 = new FileFeeder() ; 
    FileFeeder *stimLeft2 = new FileFeeder() ; 
    FileFeeder *stimLeft3 = new FileFeeder() ; 
    FileFeeder *stimLeft4 = new FileFeeder() ; 
    SetFeeder *stimRight = new SetFeeder() ; 
    FileFeeder *stimRight1 = new FileFeeder() ; 
    FileFeeder *stimRight2 = new FileFeeder() ; 
    FileFeeder *stimRight3 = new FileFeeder() ; 
    FileFeeder *stimRight4 = new FileFeeder() ; 
    SetFeeder *targetSet = new SetFeeder() ; 
    FileFeeder *targetSet1 = new FileFeeder() ; 
    FileFeeder *targetSet2 = new FileFeeder() ; 
    FileFeeder *targetSet3 = new FileFeeder() ; 
    FileFeeder *targetSet4 = new FileFeeder() ; 

    // stim feeders
    stimLeft1->setFile("../../DATA/TEST/a0big.txt") ; 
    stimRight1->setFile("../../DATA/TEST/a1big.txt") ; 
    stimLeft2->setFile("../../DATA/TEST/a1big.txt") ; 
    stimRight2->setFile("../../DATA/TEST/a0big.txt") ; 
    targetSet1->setFile("../../DATA/TEST/Pfor_up_big.txt") ; 
    targetSet2->setFile("../../DATA/TEST/Pfor_down_big.txt") ; 
    stimLeft3->setFile("../../DATA/TEST/a0small.txt") ; 
    stimRight3->setFile("../../DATA/TEST/a1small.txt") ; 
    stimLeft4->setFile("../../DATA/TEST/a1small.txt") ; 
    stimRight4->setFile("../../DATA/TEST/a0small.txt") ; 
    targetSet3->setFile("../../DATA/TEST/Pfor_up_small.txt") ; 
    targetSet4->setFile("../../DATA/TEST/Pfor_down_small.txt") ; 
    stimLeft->addFeeder(stimLeft1) ; 
    stimLeft->addFeeder(stimLeft2) ; 
    stimLeft->addFeeder(stimLeft3) ; 
    stimLeft->addFeeder(stimLeft4) ; 
    stimRight->addFeeder(stimRight1) ; 
    stimRight->addFeeder(stimRight2) ; 
    stimRight->addFeeder(stimRight3) ; 
    stimRight->addFeeder(stimRight4) ; 
    targetSet->addFeeder(targetSet1) ; 
    targetSet->addFeeder(targetSet2) ; 
    targetSet->addFeeder(targetSet3) ; 
    targetSet->addFeeder(targetSet4) ; 
//    targetSet->setDeltaT(10.0) ; 
    stimLeft->setDeltaT(1.0) ; 
    stimRight->setDeltaT(1.0) ; 
    targetSet->setDeltaT(1.0) ; 

    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.5 ; 
    (*relaxVector)[1] = 0.5 ; 
    kineticEval->setRelaxValue(relaxVector) ; 
    kineticEval->setK10(0.7351243) ; 
    kineticEval->setK01( 0.727093 ) ; 
    kineticEval->setStimulus(stimLeft,0) ; 
    kineticEval->setStimulus(stimRight,1) ; 
    kineticEval->setTarget(targetSet) ; 
    kineticEval->setRelaxTime(100) ; 
    kineticEval->setRelaxDeltaT(1) ; 
    kineticEval->setRelaxTau(5) ; 

//    Matrix* weights = new Matrix(4,4) ; 
//    Matrix* weightMask = new Matrix(4,4) ; 
//    Vector* bias = new Vector(4) ; 
//    Vector* biasMask = new Vector(4) ; 
//    Vector* tau = new Vector(4) ; 
//    Vector* tauMask = new Vector(4) ; 
//    Vector* initNeuron = new Vector(4) ; 
//    Vector* initNeuronMask= new Vector(4) ; 
//    TextEvalTrace *tracer = new TextEvalTrace() ; 
//    tracer->setTimeDelimiter(",") ; 
    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,0,-10,0,  // the real answer
                  0,0,10,2,
                  0,0,0,-3,
                  0,0,0,-2;
    (*bias) = -5,-5,-5,-5 ;   // only the middle bias matters
    (*tau) = 30,30,30,30 ; 
    (*initNeuron) = 0.5,0.5,0.00669285 ,0.4098808 ;  // should be the final answer
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(kineticEval) ; 
    tracer->setEvaluator(kineticEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
//    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimLeft->getNumPoints():  " << stimLeft->getNumPoints() << endl ; 
    cout << "stimRight->getNumPoints():  " << stimRight->getNumPoints() << endl ; 
    cout << "targetSet->getNumPoints():  " << targetSet->getNumPoints() << endl ; 
//    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
//    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    cout << "lastneuronTrace: " << endl << tracer->lastNeuronTrace() << endl ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0)) < 0.000001) ; 
    return rendertests("test 9",status); 


}





/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    cout << "running tests: " << endl ; 
    test3cache *test = new test3cache() ; 
    test->runtests() ; 

    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--dev--1.4--patch-3/src/chemotestapps/test3cache.cpp"
// LAST MODIFICATION: "Tue, 22 Jun 2004 15:36:10 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: test3cache.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

