
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string ; 

#include "annealtest1.hpp"
#include "TextEvalTrace.hpp" 
#include "NeuralNetwork.hpp" 
#include "BlitzNet.hpp" 
#include "BlitzNetPerturber.hpp" 
#include "BlitzEulerNetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 

annealtest1::annealtest1()  
{
		net = new BlitzNet() ; 
		perturber = new BlitzNetPerturber() ; 
		evaluator = new BlitzEulerNetEvaluator() ; 
        stimFeeder = new FileFeeder() ; 
        targetFeeder = new FileFeeder() ; 
        tracer = new TextEvalTrace() ; 
}


// this is where we want to set up the EvaluatorTracer, which simply replaces the other methods
bool annealtest1::test1() 
{
    try{
//        ((FileFeeder*) stimFeeder)->setFile("../../DATA/shorttest.txt") ; 
        stimFeeder = new SetFeeder() ; 
        targetFeeder = new SetFeeder() ; 
        StepFeeder *stimFeeder1 = new StepFeeder() ; 
        StepFeeder *stimFeeder2 = new StepFeeder() ; 
//        targetFeeder = new StepFeeder() ; 
        FileFeeder *targetFeeder1 = new FileFeeder() ; 
        FileFeeder *targetFeeder2 = new FileFeeder() ; 
        ((FileFeeder*) targetFeeder1)->setFile("../../DATA/TEST/shorttest.txt") ; 
        ((FileFeeder*) targetFeeder1)->loadSigFile("../../DATA/TEST/shortsigtest.txt") ; 
        targetFeeder1->setDeltaT(2.0) ; 
        ((FileFeeder*) targetFeeder2)->setFile("../../DATA/TEST/shorttest2.txt") ; 
        ((FileFeeder*) targetFeeder2)->loadSigFile("../../DATA/TEST/shortsigtest2.txt") ; 
        targetFeeder2->setDeltaT(2.0) ; 

        ( (StepFeeder*)  stimFeeder1)->setPreStepTime(5.0) ; 
        ( (StepFeeder*)  stimFeeder1)->setPreStepValue(1.0) ; 
        ( (StepFeeder*)  stimFeeder1)->setPostStepTime(5.0) ; 
        ( (StepFeeder*)  stimFeeder1)->setPostStepValue(0.5) ; 
        stimFeeder1->setDeltaT(0.1) ; 

        ( (StepFeeder*)  stimFeeder2)->setPreStepTime(1.0) ; 
        ( (StepFeeder*)  stimFeeder2)->setPreStepValue(1.0) ; 
        ( (StepFeeder*)  stimFeeder2)->setPostStepTime(9.0) ; 
        ( (StepFeeder*)  stimFeeder2)->setPostStepValue(0.5) ; 
        stimFeeder2->setDeltaT(0.1) ; 


        ( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder1) ; 
        ( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder2) ; 
        stimFeeder->setDeltaT(0.1) ; 

        ( (SetFeeder*) targetFeeder)->addFeeder(targetFeeder1) ; 
        ( (SetFeeder*) targetFeeder)->addFeeder(targetFeeder2) ; 


        evaluator = new BinNetEvaluator() ; 
        evaluator->setStimulus(stimFeeder) ; 
        evaluator->setTarget(targetFeeder) ; 
//        net->setNumNeurons(4) ; 
        net->setEvaluator(evaluator) ; 
        cout << "1 eval: " << net->eval() << endl ;  

        net->setPerturber(perturber) ; 

        net->perturb(1.0) ; 
        cout << "eval: " << net->eval() << endl ;  
        cout << "norml eval: " << net->evalNorml() << endl ;  

        cout << "A" <<  endl ; 
//        TextEvalTrace *tracer = new TextEvalTrace() ; 
        cout << "B" <<  endl ; 
//        tracer->setTimeDelimiter("\n") ; 
        cout << "C" <<  endl ; 
//        tracer->setValueDelimiter(" ") ; 
        cout << "D" <<  endl ; 
        tracer->setEvaluator(evaluator) ;   // definitely want this to be a 
                                            // memory set
        cout << "E" <<  endl ; 
        
        cout << "allNeuronTrace: " << tracer->allNeuronTrace() << endl ; 
        cout << "F" <<  endl ; 
        cout << "lastNeuronTrace: " << tracer->lastNeuronTrace() << endl ; 
        cout << "G" <<  endl ; 
        cout << "neuronTrace(2): " << tracer->neuronTrace(2) << endl ; 
        cout << "H" <<  endl ; 
        cout << "errorTrace: " << tracer->errorTrace() << endl ; 
        cout << "I" <<  endl ; 
        cout << "targetTimeTrace: " << tracer->targetTimeTrace() << endl ; 
        cout << "J" <<  endl ; 
        cout << "stimTimeTrace: " << tracer->stimTimeTrace() << endl ; 
        cout << "K" <<  endl ; 
        cout << "targetTrace: " << tracer->targetTrace() << endl ; 
        cout << "L" <<  endl ; 
        cout << "stimTrace: " << tracer->stimTrace() << endl ; 
        cout << "M" <<  endl ; 
        cout << "lastTimeStepNeurons: " << tracer->lastTimeStepNeurons() << endl ; 
        cout << "N" <<  endl ; 
        cout << "neuronsAtTargetPoint(2): " << tracer->neuronsAtTargetPoint(2) << endl ; 
        cout << "O" <<  endl ; 
        cout << "combineTrace: " << tracer->combineTrace(tracer->stimTrace(),tracer->targetTrace()) << endl ; 
        cout << "P" <<  endl ; 
    }
    catch(string errorString){
        cout << "caught error: " << errorString << endl ; 
        return false ; 
    }
    catch(...){
        cout << "generic error" << endl ; 
        return false ; 
    }

    return true ; 
}


// add the average error 
bool annealtest1::test3() 
{
    try{
        stimFeeder = new SetFeeder() ; 
        targetFeeder = new SetFeeder() ; 
        StepFeeder *stimFeeder1 = new StepFeeder() ; 
        StepFeeder *stimFeeder2 = new StepFeeder() ; 
        FileFeeder* targetFile1 = new FileFeeder() ; 
        FileFeeder* targetFile2 = new FileFeeder() ; 
       stimFeeder1->setPreStepValue(40.0) ; 
       stimFeeder1->setPostStepValue(50.0) ; 
       stimFeeder1->setPreStepTime(120) ; 
       stimFeeder1->setPostStepTime(180) ; 
       stimFeeder2->setPreStepValue(50.0) ; 
       stimFeeder2->setPostStepValue(60.0) ; 
       stimFeeder2->setPreStepTime(120) ; 
       stimFeeder2->setPostStepTime(180) ; 
       targetFile1->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e40_50fwd.txt") ; 
       targetFile2->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_60fwd.txt") ; 

       ( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder1) ; 
       ( (SetFeeder*) stimFeeder)->addFeeder(stimFeeder2) ; 
       ( (SetFeeder*) targetFeeder)->addFeeder(targetFile1) ; 
       ( (SetFeeder*) targetFeeder)->addFeeder(targetFile2) ; 
       stimFeeder->setDeltaT(1.0) ; 
       targetFeeder->setDeltaT(10.0) ; 
       evaluator->setStimulus(stimFeeder) ; 
       evaluator->setTarget(targetFeeder) ; 
       net->setEvaluator(evaluator) ; 

        net->setNumNeurons(2) ;  // resets everything
        net->setNumNeurons(4) ;  // resets everything
        cout << "------------\n-------------" << endl ; 
        cout << net->eval() << endl ;  
        cout << net->evalNorml() << endl ;  
        cout << "------------\n-------------" << endl ; 
       stimFeeder->setDeltaT(0.1) ; 
        cout << net->eval() << endl ;  
        cout << net->evalNorml() << endl ;  
        cout << "------------\n-------------" << endl ; 
//        cout << "A" <<  endl ; 
//        cout << "allNeuronTrace: " << tracer->allNeuronTrace() << endl ; 
//        cout << "B" <<  endl ; 
//        cout << "lastNeuronTrace: " << tracer->lastNeuronTrace() << endl ; 
//        cout << "C" <<  endl ; 
//        cout << "neuronTrace(2): " << tracer->neuronTrace(2) << endl ; 
//        cout << "D" <<  endl ; 
//        cout << "errorTrace: " << tracer->errorTrace() << endl ; 
//        cout << "E" <<  endl ; 
//        cout << "stimTrace: " << tracer->stimTrace() << endl ; 
//        cout << "F" <<  endl ; 
//        cout << "stimulusSize: " << ((net->getEvaluator())->getStimulus())->getNumPoints() << endl ; 
//        cout << "targetSize: " << ((net->getEvaluator())->getTarget())->getNumPoints() << endl ; 

//        Feeder* feederTarget = (net->getEvaluator())->getTarget()  ; 
//        feederTarget->reset() ; 
//        for(int i = 0 ; i < feederTarget->size() ; i++){
//                 cout << feeder->getNextPoint() << timeDelimiter ;  
//         }
//        cout << "targetTrace: " << tracer->targetTrace() << endl ; 
//        cout << "G" <<  endl ; 
//        cout << "render: " << net->render() << endl ; 

    }
    catch(string errorString){
        cout << "caught error: " << errorString << endl ; 
        return false ; 
    }
    catch(...){
        cout << "generic error" << endl ; 
        return false ; 
    }

    return true ; 
}


// add the significance finder
bool annealtest1::test2() 
{
    try{
        StepFeeder *stepFeeder1 = new StepFeeder() ; 
        StepFeeder *stepFeeder2 = new StepFeeder() ; 
       stepFeeder1->setPreStepValue(40.0) ; 
       stepFeeder1->setPostStepValue(50.0) ; 
       stepFeeder1->setPreStepTime(120) ; 
       stepFeeder1->setPostStepTime(180) ; 
       stepFeeder2->setPreStepValue(40.0) ; 
       stepFeeder2->setPostStepValue(60.0) ; 
       stepFeeder2->setPreStepTime(120) ; 
       stepFeeder2->setPostStepTime(180) ; 

       stepFeeder1->setDeltaT(1.0) ; 
       stepFeeder2->setDeltaT(10.0) ; 
       evaluator->setStimulus(stepFeeder1) ; 
       evaluator->setTarget(stepFeeder2) ; 

       net->setEvaluator(evaluator) ; 
       net->setNumNeurons(2) ; 
       net->setNumNeurons(4) ; 
        cout << "------------\n-------------" << endl ; 
        cout  << "eval: " << net->eval() << endl; 
        cout << "evalNorml: " << net->evalNorml() << endl ; 
        cout << "------------\n-------------" << endl ; 
       stepFeeder1->setDeltaT(0.1) ; 
        cout  << "eval: " << net->eval() << endl; 
        cout << "evalNorml: " << net->evalNorml() << endl ; 
        cout << "------------\n-------------" << endl ; 
        FileFeeder *fileFeeder1 = new FileFeeder() ; 
        FileFeeder *fileFeeder2 = new FileFeeder() ; 
       fileFeeder1->setDeltaT(1.0) ; 
       fileFeeder2->setDeltaT(1.0) ; 
       evaluator->setStimulus(fileFeeder1) ; 
       evaluator->setTarget(fileFeeder2) ; 
       net->setEvaluator(evaluator) ; 
//        fileFeeder2->loadFile("somefile.txt") ;  // load a similar file to file output
        // do the same thing, but try with differing files, should be the same
        // alter the dt on the stimulus and see what occurs
//        cout  << "eval: " << net->eval() << endl; 
//        cout << "evalNorml: " << net->evalNorml() << endl ; 
//        cout << "------------\n-------------" << endl ; 
//        fileFeeder1->setDeltaT(0.1) ;  // 
//        cout  << "eval: " << net->eval() << endl; 
//        cout << "evalNorml: " << net->evalNorml() << endl ; 
//        cout << "------------\n-------------" << endl ; 
       

    }
    catch(string errorString){
        cout << "caught error: " << errorString << endl ; 
        return false ; 
    }
    catch(...){
        cout << "generic error" << endl ; 
        return false ; 
    }

    return true ; 
}

// add a network reader in tinyxml
bool annealtest1::test4() 
{
    try{

    }
    catch(string errorString){
        cout << "caught error: " << errorString << endl ; 
        return false ; 
    }
    catch(...){
        cout << "generic error" << endl ; 
        return false ; 
    }

    return true ; 
}

// try small deltaT
bool annealtest1::test5() 
{
    try{


    }
    catch(string errorString){
        cout << "caught error: " << errorString << endl ; 
        return false ; 
    }
    catch(...){
        cout << "generic error" << endl ; 
        return false ; 
    }

    return true ; 
}





/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    annealtest1 *test = new annealtest1() ; 
//    if(test->test1()){
//       cout << "passed " ; 
//    }else{
//       cout << "failed " ; 
//    }
//    cout << "test1" << endl ; 

    if(test->test2()){
       cout << "passed " << endl; 
    }else{
       cout << "failed " << endl; 
    }
    cout << "test2" << endl ; 
         


    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemotestapps/annealtest1.cpp"
// LAST MODIFICATION: "Fri, 28 Nov 2003 23:43:14 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

