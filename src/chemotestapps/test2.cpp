

#ifdef DOMPI
    #include "mpi.h"
#endif

#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetPerturber.hpp" 
#include "BlitzEulerNetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 
#include "BlitzNetAnnealer.hpp"  
#include "PowerTempSchedule.hpp"  


#include "test2.hpp"

test2::test2(): testsPassed(0)  
    ,testsRun(0)  
{
    if(!initData()){
        cout << "could not initialize the data" << endl ; 
        exit(0) ; 
    }
}

inline bool test2::rendertests(string description, bool results) 
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


bool test2::initData() 
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
    annealer = new BlitzNetAnnealer() ; 
    tempSchedule= new PowerTempSchedule() ;
    perturber = new BlitzNetPerturber() ; 

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
    blitzNet->setPerturber(perturber) ; 

    tempSchedule->setNumPoints(1) ; 
    tempSchedule->setHighTemp(4.0) ; 
    tempSchedule->setLowTemp(0.001) ; 
    tempSchedule->setPower(3.0) ; 
    tempSchedule->initTemps() ; 
    annealer->setTempSchedule(tempSchedule) ; 
    annealer->setIterPerTemp(1) ; 
    annealer->setAnnealingTarget(blitzNet) ; 


    }
    catch(...){
        cout << "an error ? " << endl ; 
        return false ; 
    }

    return true ; 
}


int test2::runtests(){

    
    dotest1()  ;  
//    dotest2() ; 
//    dotest3() ; 

    cout << "-----------\n-----------" << endl ; 
    cout << "number of tests passed: "  << testsPassed   << endl ; 
    cout << "number of tests run: "  << testsRun  << endl ; 
    return testsPassed ; 
}

bool test2::dotest1() 
{
    cout << "----------\ntest 1\n-----------" << endl ; 
    cout << "tests the init neuron tests over annealing" << endl ; 
    bool status = false ; 

    blitzEval->setStimulus(stimA) ; 
    blitzEval->setTarget(targetA) ; 
    blitzNet->setEvaluator(blitzEval) ; 
    cout << "BlitzNet->eval(): " << endl << blitzNet->eval() << endl ; 
    cout << "BlitzNet->evalNorml(): " << endl << blitzNet->evalNorml() << endl ; 
    cout << "BlitzNet1: " << endl << blitzNet->render() << endl ; 
    cout << "BlitzNet2: " << endl << blitzNet->render() << endl ; 


    tempSchedule->setHighTemp(0.1) ; 
    blitzNet = (BlitzNet*) blitzNet->perturb(1.0) ; 
    cout << "A" << endl ; 
    cout << "B" << endl ; 
    annealer->setIterPerTemp(1000) ; 
    cout << "C" << endl ; 
    tempSchedule->setNumPoints(10) ; 
    cout << "D" << endl ; 
    BlitzNet* returnNet = (BlitzNet*) annealer->anneal() ; 
    cout << "E" << endl ; 
    cout << "returnNet: " << endl << returnNet->render() << endl ; 
    cout << "F" << endl ; 

    status = true ; 
    return rendertests("test 1",status); 
}


bool test2::dotest2() {
    cout << "----------\ntest 2\n-----------" << endl ; 
    cout << "test the net relaxation code" << endl ; 

    bool status =  false ; 
    return rendertests("test 2",status) ; 
} 
bool test2::dotest3() {
     
    cout << "----------\ntest 3\n-----------" << endl ; 
    cout << "set tau-test" << endl ; 
    bool status = false ; 
    return rendertests("test 3",status) ; 
} 


/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    #ifdef DOMPI
        MPI_Init(&argc,&argv) ; 
    #endif

    cout << "running tests: " << endl ; 
    test2 *test = new test2() ; 
    test->runtests() ; 

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
// FILE: "/home/ndunn/tla/auto3--dev--1.4--patch-3/src/chemotestapps/test2.cpp"
// LAST MODIFICATION: "Tue, 22 Jun 2004 15:24:43 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: test2.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

