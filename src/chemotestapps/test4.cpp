/*
 * $Id: test4.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $
 */


#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetPerturber.hpp" 
#include "BlitzEulerSigNetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 


#include "test4.hpp"


test4::test4(): testsPassed(0)  
    ,testsRun(0)  
{
    if(!initData()){
        cout << "could not initialize the data" << endl ; 
        exit(0) ; 
    }
}

inline bool test4::rendertests(string description, bool results) 
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


bool test4::initData() 
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
    blitzNet = new BlitzNet() ; 
    blitzNetEval = new BlitzEulerSigNetEvaluator() ; 
    netEval = new BinNetEvaluator() ; 
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
    blitzNet->setEvaluator(blitzNetEval) ; 




    }
    catch(...){
        cout << "an error ? " << endl ; 
        return false ; 
    }

    return true ; 
}


int test4::runtests(){


    dotest1() ; 
    dotest2() ; 
    dotest3() ; 
    dotest4() ; 
    dotest5() ; 
    dotest6() ; 
    dotest7() ; 
    dotest8() ;  // test gain on 2 inputs
    dotest9() ;  // test output sigmoid, non-1

    cout << "-----------\n-----------" << endl ; 
    cout << "number of tests passed: "  << testsPassed   << endl ; 
    cout << "number of tests run: "  << testsRun  << endl ; 
    return testsPassed ; 
}

bool test4::dotest1() 
{
    cout << "----------\ntest 1-BinNetEvaluator\n-----------" << endl ; 
    stimA->setDeltaT(1.0) ; 
    targetA->setDeltaT(1.0) ; 
    netEval->setStimulus(stimA) ; 
    netEval->setTarget(targetA) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 

    cout << "stimA->getNumPoints():  " << stimA->getNumPoints() << endl ; 
    cout << "targetA->getNumPoints():  " << targetA->getNumPoints() << endl ; 
    cout << "blitzNet->eval(): " << regNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // (4-2)^2 * 1 
    bool status = ( fabs(regNet->evalNorml()- (16.0/6.0)) < 0.001) ; 
    return rendertests("test 1",status); 
}

bool test4::dotest2() 
{
    cout << "----------\ntest 2-BlitzEulerSigNetEvaluator, 1 interneuron\n-----------" << endl ; 
    cout << "does this work for 1 input?" << endl ; 
    stimB->setDeltaT(1.0) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetD.txt") ; 
//    blitzNetEval->setGlobalSigLimit(6) ; 
    blitzNetEval->setStimulus(stimB) ; 
    blitzNetEval->setTarget(targetB) ; 
    (*weights) =  0,1,0,
    			  0,0,1,
    			  0,0,-1 ;
    (*bias) = -0.5,-0.5,0  ;   
    (*tau) = 5,5,5 ; 
    (*initNeuron) = 0.5,0.5 ,0.5 ;  
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimB->getNumPoints():  " << stimB->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl << endl  ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl << endl ; 
    // 0.04 + 0.04 + 0.0149963 + 0.09 = 0.1849963
    bool status = ( fabs(blitzNet->evalNorml()- (0.1849963/4.0)) < 0.000001) ; 
    return rendertests("test 2",status); 
}


bool test4::dotest3() 
{
    cout << "----------\ntest 3-BlitzEulerSigNetEvaluator, 3 interneuron\n-----------" << endl ; 
    cout << "does this work for 2 interneurons?" << endl ; 
    stimB->setDeltaT(1.0) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetD.txt") ; 
    blitzNetEval->setGlobalSigLimit(6) ; 
    blitzNetEval->setStimulus(stimB) ; 
    blitzNetEval->setTarget(targetB) ; 
    weights = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    tau = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,1,1,0,
    			  0,0,0,0.5,
    			  0,0,0,0.5,
    			  0,0,0,-1.244918;
    (*bias) = -0.5,0,0,0 ;   
    (*tau) = 5,5,5,5 ; 
    (*initNeuron) = 0.5,0.6225,0.6225,0.5 ; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
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

bool test4::dotest4() 
{
    cout << "----------\ntest 4-BlitzEulerSigNetEvaluator, 2 inputs\n-----------" << endl ; 
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
    blitzNetEval->setStimulus(stimC,0) ; 
    blitzNetEval->setStimulus(stimD,1) ; 
    blitzNetEval->setTarget(targetB) ; 
//    weights = new Matrix(4,4) ; 
//    bias = new Vector(4) ; 
//    tau = new Vector(4) ; 
//    initNeuron = new Vector(4) ; 
//    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,0,1,0,
    			  0,0,1,0,
    			  0,0,0,1,
    			  0,0,0,-1.244918;
    (*bias) = -1.1473 ,-1.5863,0,0 ;   
    (*tau) = 5,5,5,5 ; 
    (*initNeuron) = 0.3,0.2,0.62246,0.5 ; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
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

bool test4::dotest5() 
{
    cout << "----------\ntest 5-BlitzEulerSigNetEvaluator, 6 neurons, 2 inputs\n-----------" << endl ; 
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
//   blitzNetEval->setRelaxTime(50) ; 
//   blitzNetEval->setRelaxDeltaT(1) ; 
//   blitzNetEval->setRelaxValue(0.5) ; 
    blitzNetEval->setStimulus(stimC,0) ; 
    blitzNetEval->setStimulus(stimD,1) ; 
    blitzNetEval->setTarget(targetB) ; 
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
    (*bias) = -1.5863,-1.1473,-0.2,-0.5,0.2,0 ;   // only the middle bias matters
    (*tau) = 5,5,5,5,5,5 ; 
    (*initNeuron) = 0.2,0.3,0.5,0.5,0.5,0.5; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimB->getNumPoints():  " << stimB->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.184996/4.0)) < 0.000001) ; 
    return rendertests("test 5 (we don't care what the last neuron is)",status); 
}


bool test4::dotest6() 
{
    cout << "----------\ntest 6\n-----------" << endl ; 
    cout << "BlitzEulerSigNetEvaluator, relaxed, bad init, 2 inputs, 3 interneurons." << endl ; 
    blitzNetEval->setRelaxTime(100) ; 
    blitzNetEval->setRelaxDeltaT(1) ; 
    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.2 ; 
    (*relaxVector)[1] = 0.3 ; 
    blitzNetEval->setRelaxValue(relaxVector) ; 
    blitzNetEval->setStimulus(stimC,0) ; 
    blitzNetEval->setStimulus(stimD,1) ; 
    blitzNetEval->setTarget(targetB) ; 
    (*initNeuron) = 0.0,0.0,0.0,0.0,0.0,0.0; //  init at different level
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
//    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // 0.25 - 0.7, 0.3 - 0.25, 0.6224593 - 0.25, 0.8-0.25 = 1.4224593
    bool status = ( fabs(blitzNet->evalNorml()- (0.184996/4.0)) < 0.000001) ; 
    return rendertests("test 6",status); 
}


bool test4::dotest7() 
{
    cout << "----------\ntest 7-tests big weights\n-----------" << endl ; 
    weights = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    tau = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,0,-10,0,
    			  0,0,10,2,
    			  0,0,0,-3,
    			  0,0,0,-2;
    (*bias) = -0.5,-0.5,-5,0 ;   
    (*tau) = 30,30,30,30 ; 
    (*initNeuron) = 0.5,0.5,0.00669285 ,0.502746;  // should be the final answer
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
    stimC->setPreStepValue(0.5) ; 
    stimC->setPostStepValue(0.5) ; 
    stimD->setPreStepValue(0.5) ; 
    stimD->setPostStepValue(0.5) ; 
    blitzNetEval->setRelaxTime(0) ; // no relax time!!!
    blitzNetEval->setStimulus(stimC,0) ; 
    blitzNetEval->setStimulus(stimD,1) ; 
    blitzNetEval->setTarget(targetB) ; 
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
//    bool status = ( fabs(blitzNet->evalNorml()- (0.182029/4.0)) < 0.001) ; 
    // ?? 0.7 -0.49376, 0.3 - 0.498028, 0.6224593 - 0.496001, 0.8-0.496964= 0.816967
//    bool status = ( fabs(blitzNet->evalNorml()- (0.183468/4.0)) < 0.001) ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.1896792/4.0)) < 0.001) ; 
    return rendertests("test 7",status); 
}


bool test4::dotest8() 
{
    cout << "----------\ntest 8 - Test gain\n-----------" << endl ; 
    weights = new Matrix(4,4) ; 
    bias = new Vector(4) ; 
    tau = new Vector(4) ; 
    gain = new Vector(4) ; 
    initNeuron = new Vector(4) ; 
    blitzNet->setNumNeurons(4) ; 
    (*weights) =  0,0,1,0,
    			  0,0,1,0,
    			  0,0,0,1,
    			  0,0,0,0;
    (*bias) = -0.5,-0.5,0,0 ;   
    (*tau) = 3,3,3,3 ; 
    (*gain) = 2,-1,0,0 ; 
    (*initNeuron) = 0.6224593,0.2689414,0.7091792,0.670219757;  // should be the final answer
    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setGain(gain) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(blitzNetEval) ; 
    tracer->setEvaluator(blitzNetEval) ; 
    stimC->setPreStepValue(0.5) ; 
    stimC->setPostStepValue(0.5) ; 
    stimD->setPreStepValue(0.5) ; 
    stimD->setPostStepValue(0.5) ; 
    blitzNetEval->setRelaxTime(0) ; // no relax time!!!
    blitzNetEval->setStimulus(stimC,0) ; 
    blitzNetEval->setStimulus(stimD,1) ; 
    blitzNetEval->setTarget(targetB) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimC->getNumPoints():  " << stimC->getNumPoints() << endl ; 
    cout << "stimD->getNumPoints():  " << stimD->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    //  (0.670219757 - 0.7)^2, 0.3, 0.6224593, 0.8  // should be the final answer
    bool status = ( fabs(blitzNet->evalNorml()- (0.157074/4.0) ) < 0.001) ; 
    return rendertests("test 8",status); 
}

bool test4::dotest9() 
{
    cout << "----------\ntest 9 - output sigmoid 5\n-----------" << endl ; 
    blitzNetEval->setOutputSigmoid(5.0) ; 
    (*initNeuron) = 0.6224593,0.2689414,0.7091792,0.971965816 ;  // should be the final answer
    blitzNet->setInitNeuron(initNeuron) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimC->getNumPoints():  " << stimC->getNumPoints() << endl ; 
    cout << "stimD->getNumPoints():  " << stimD->getNumPoints() << endl ; 
    cout << "targetB->getNumPoints():  " << targetB->getNumPoints() << endl ; 
    cout << "stimTrace: " << endl << tracer->stimTrace() << endl ; 
    cout << "targetTrace: " << endl << tracer->targetTrace() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    // (0.971965816 - 0.7)^2, 0.3, 0.6224, 0.8
    bool status = ( fabs(blitzNet->evalNorml()- (0.677231 /4.0)) < 0.0001) ; 
    return rendertests("test 9",status); 


}





/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    cout << "running tests: " << endl ; 
    test4 *test = new test4() ; 
    test->runtests() ; 
    cout << "exiting main" << endl ; 

    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: test4.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

