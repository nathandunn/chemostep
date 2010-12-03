

#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetPerturber.hpp" 
#include "BlitzEulerNetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 


#include "test1.hpp"


test1::test1(): testsPassed(0)  
,testsRun(0)  
{
    if(!initData()){
        cout << "could not initialize the data" << endl ; 
        exit(0) ; 
    }
}

inline bool test1::rendertests(string description, bool results) 
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


bool test1::initData() 
{
    try{
        
    tracer = new TextEvalTrace() ; 
    stimA = new StepFeeder() ; 
    targetA = new FileFeeder() ; 
    stimB = new StepFeeder() ; 
    targetB = new FileFeeder() ; 
    stimC = new StepFeeder() ; 
    targetC = new FileFeeder() ; 
    regNet = new NeuralNetwork() ; 
    netEval = new BinNetEvaluator() ; 
    blitzNet = new BlitzNet() ; 
    blitzEval = new BlitzEulerNetEvaluator() ; 
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
    stimB->setPreStepTime(0.5) ; 
    stimB->setPostStepTime(5.5) ; 
    stimB->setPreStepValue(3.0) ; 
    stimB->setPostStepValue(7.0) ; 
    targetB->setFile("../../DATA/TEST/testsetB.txt") ; 
    targetB->loadSigFile("../../DATA/TEST/testsetsigB.txt") ; 
    stimC->setPreStepTime(2) ; 
    stimC->setPostStepTime(4) ; 
    stimC->setPreStepValue(1.0) ; 
    stimC->setPostStepValue(0.5) ; 
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
    blitzNet->setEvaluator(blitzEval) ; 



    }
    catch(...){
        cout << "an error ? " << endl ; 
        return false ; 
    }

    return true ; 
}


int test1::runtests(){


    dotest1()  ;  
    dotest2() ; 
    dotest3() ; 
    dotest4() ; 
    dotest5() ; 
    dotest6() ; 
    dotest7() ; 
    dotest8() ; 
    dotest9() ; 
    dotest10() ; 
    dotest11() ; 
    dotest12() ; 
    dotest13() ; 
    dotest14() ; 
    dotest15() ; 
    dotest16() ; 
//    dotest17() ; 
//    dotest18() ; 

    cout << "-----------\n-----------" << endl ; 
    cout << "number of tests passed: "  << testsPassed   << endl ; 
    cout << "number of tests run: "  << testsRun  << endl ; 
    return testsPassed ; 
}

bool test1::dotest1() 
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
    bool status = ( fabs(regNet->evalNorml()- (16.0/6.0)) < 0.001) ; 
    return rendertests("test 1",status); 
}


bool test1::dotest2() {
    cout << "----------\ntest 2\n-----------" << endl ; 
    stimA->setDeltaT(0.1) ; 
    targetA->setDeltaT(1.0) ; 
    netEval->setStimulus(stimA) ; 
    netEval->setTarget(targetA) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "stimA->getNumPoints():  " << stimA->getNumPoints() << endl ; 
    cout << "targetA->getNumPoints():  " << targetA->getNumPoints() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    bool status = ( fabs(regNet->evalNorml()- (16.0/6.0)) < 0.00001) ; 
    return rendertests("test 2",status) ; 
} 
bool test1::dotest3() {
     
    cout << "----------\ntest 3\n-----------" << endl ; 
    stimA->setDeltaT(1.0) ; 
    targetA->setDeltaT(2.0) ; 
    targetA->setFile("../../DATA/TEST/testsetAdelta2.txt") ; 
    netEval->setStimulus(stimA) ; 
    netEval->setTarget(targetA) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    bool status = ( fabs(regNet->evalNorml()- (16.0/6.0)) < 0.00001) ; 
    return rendertests("test 3",status) ; 
} 
bool test1::dotest4() {
     
    cout << "----------\ntest 4\n-----------" << endl ; 
    stimA->setDeltaT(0.1) ; 
    targetA->setDeltaT(2.0) ; 
    targetA->setFile("../../DATA/TEST/testsetAdelta2.txt") ; 
    netEval->setStimulus(stimA) ; 
    netEval->setTarget(targetA) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    bool status = ( fabs(regNet->evalNorml()- (16.0/6.0)) < 0.00001) ; 
    return rendertests("test 4",status) ; 
} 
bool test1::dotest5() {
     
    cout << "----------\ntest 5\n-----------" << endl ; 
    stimB->setDeltaT(0.5) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetB.txt") ; 
    targetB->loadSigFile("../../DATA/TEST/testsetsigB.txt") ; 
    netEval->setStimulus(stimB) ; 
    netEval->setTarget(targetB) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    // 2^2 * 1 +  2^2 *4 = 68 
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    bool status = ( fabs(regNet->evalNorml()- (68.0/6.0)) < 0.001) ; 
    cout << "error trace: " << tracer->errorTrace() << endl ; 
    cout << "all neuron trace: " << tracer->allNeuronTrace() << endl ; 
    return rendertests("test 5",status) ; 
} 
bool test1::dotest6() {
     
    cout << "----------\ntest 6\n-----------" << endl ; 
    stimB->setDeltaT(0.1) ; 
    targetB->setDeltaT(1.0) ; 
    targetB->setFile("../../DATA/TEST/testsetB.txt") ; 
    targetB->loadSigFile("../../DATA/TEST/testsetsigB.txt") ; 
    netEval->setStimulus(stimB) ; 
    netEval->setTarget(targetB) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    // 2^2 *1  + 4^2 * 4 = 68
    bool status = ( fabs(regNet->evalNorml()- (68.0/6.0)) < 0.001) ; 
    return rendertests("test 6",status) ; 
} 
bool test1::dotest7() {
     
    cout << "----------\ntest 7\n-----------" << endl ; 
    stimB->setDeltaT(0.5) ; 
    targetB->setFile("../../DATA/TEST/testsetBdt2.txt") ; 
    targetB->loadSigFile("../../DATA/TEST/testsetsigBdt2.txt") ; 
    targetB->setDeltaT(2.0) ; 
    netEval->setStimulus(stimB) ; 
    netEval->setTarget(targetB) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    // (6- 7)^2 *1  + (5-7)^2*4 = 1 + 16  = 17  
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    bool status = ( fabs(regNet->evalNorml()- (17.0/6.0)) < 0.001) ; 
    return rendertests("test 7",status) ; 
} 
bool test1::dotest8() {
     
    cout << "----------\ntest 8\n-----------" << endl ; 
    stimB->setDeltaT(0.1) ; 
    targetB->setDeltaT(2.0) ; 
    targetB->setFile("../../DATA/TEST/testsetBdt2.txt") ; 
    targetB->loadSigFile("../../DATA/TEST/testsetsigBdt2.txt") ; 
    netEval->setStimulus(stimB) ; 
    netEval->setTarget(targetB) ; 
    regNet->setEvaluator(netEval) ; 
    tracer->setEvaluator(netEval) ; 
    // (6- 7)^2 *1  + (5-7)^2*4 = 1 + 16  = 17  
    cout << "regNet->eval(): " << regNet->eval() << endl ; 
    cout << "regNet->evalNorml(): " << regNet->evalNorml() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    bool status = ( fabs(regNet->evalNorml()- (17.0/6.0)) < 0.001) ; 
    return rendertests("test 8",status) ; 
} 
bool test1::dotest9() {
     
    cout << "----------\ntest 9\n-----------" << endl ; 
    stimC->setDeltaT(1.0) ; 
    targetC->setDeltaT(1.0) ; 
    targetC->setFile("../../DATA/TEST/testsetC.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
    cout << "stimC->getNumPoints():  " << stimC->getNumPoints() << endl ; 
    cout << "targetC->getNumPoints():  " << targetC->getNumPoints() << endl ; 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.000011345)) < 0.00000001) ; 
    return rendertests("test 9",status) ; 
} 
bool test1::dotest10() {
    
    cout << "----------\ntest 10\n-----------" << endl ; 
    stimC->setDeltaT(  0.1) ; 
    targetC->setDeltaT(  1.0) ; 
    targetC->setFile("../../DATA/TEST/testsetC.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.0000504314/6.0)) < 0.000000001) ; 
    return rendertests("test 10",status) ; 
} 
bool test1::dotest11() {
    cout << "----------\ntest 11\n-----------" << endl ; 
    stimC->setDeltaT(1.0) ; 
    targetC->setFile("../../DATA/TEST/testsetCdt2.txt") ; 
    targetC->setDeltaT(2.0) ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.0000334203/6.0)) < 0.00000001) ; 
    return rendertests("test 11",status) ; 
} 
bool test1::dotest12() {
    cout << "----------\ntest 12\n-----------" << endl ; 
    stimC->setDeltaT(0.1) ; 
    targetC->setDeltaT(2.0) ; 
    targetC->setFile("../../DATA/TEST/testsetCdt2.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.0000247718/6.0)) < 0.00000001) ; 
    return rendertests("test 12",status) ; 
} 
bool test1::dotest13() {
    cout << "----------\ntest 13\n-----------" << endl ; 
    stimC->setDeltaT(1.0) ; 
    targetC->setDeltaT(1.0) ; 
    targetC->setFile("../../DATA/TEST/testsetC.txt") ; 
    targetC->loadSigFile("../../DATA/TEST/testsetsigC.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.000238536/6.0)) < 0.0000001) ; 
    return rendertests("test 13",status) ; 
} 
bool test1::dotest14() {
    cout << "----------\ntest 14\n-----------" << endl ; 
    stimC->setDeltaT(0.1) ; 
    targetC->setDeltaT(1.0) ; 
    targetC->setFile("../../DATA/TEST/testsetC.txt") ; 
    targetC->loadSigFile("../../DATA/TEST/testsetsigC.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.000178489/6.0)) < 0.0001) ; 
    return rendertests("test 14",status) ; 
} 
bool test1::dotest15() {
    cout << "----------\ntest 15\n-----------" << endl ; 
    stimC->setDeltaT(1.0) ; 
    targetC->setDeltaT(2.0) ; 
    targetC->setFile("../../DATA/TEST/testsetCdt2.txt") ; 
    targetC->loadSigFile("../../DATA/TEST/testsetsigCdt2.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.000132557/6.0)) < 0.00000001) ; 
    return rendertests("test 15",status) ; 
} 
bool test1::dotest16() {
    cout << "----------\ntest 16\n-----------" << endl ; 
    stimC->setDeltaT(0.1) ; 
    targetC->setDeltaT(2.0) ; 
    targetC->setFile("../../DATA/TEST/testsetCdt2.txt") ; 
    targetC->loadSigFile("../../DATA/TEST/testsetsigCdt2.txt") ; 
    blitzEval->setStimulus(stimC) ; 
    blitzEval->setTarget(targetC) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    tracer->setEvaluator(blitzEval) ; 
    cout << "blitzNet->eval(): " << blitzNet->eval() << endl ; 
    cout << "blitzNet->evalNorml(): " << blitzNet->evalNorml() << endl ; 
//    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
//    tracer->setTimeDelimiter("\n") ; 
//    cout << "neuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 
//    tracer->setTimeDelimiter(",") ; 
    bool status = ( fabs(blitzNet->evalNorml()- (0.0000977538/6.0)) < 0.00001) ; 
    return rendertests("test 16",status) ; 
} 
bool test1::dotest17() {
 	return false ; 
} 
bool test1::dotest18() {
 	return false ; 
} 


/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    cout << "running tests: " << endl ; 
    test1 *test = new test1() ; 
    test->runtests() ; 

    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-

