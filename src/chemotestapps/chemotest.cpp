// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemotestapps/chemotest.cpp"
// LAST MODIFICATION: "Fri, 28 Nov 2003 23:43:38 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

#include <iostream>
using std::cout ; 
using std::endl ; 


#include "NeuralNetwork.hpp" 
#include "TextEvalTrace.hpp" 
#include "Annealer.hpp" 
#include "NetAnnealer.hpp" 
#include "AnnealingTarget.hpp" 
#include "TempSchedule.hpp" 
#include "PowerTempSchedule.hpp" 
#include "NetPerturber.hpp" 
#include "NetEvaluator.hpp" 
#include "BinNetEvaluator.hpp" 
#include "FileFeeder.hpp" 
#include "StepFeeder.hpp" 
#include "SetFeeder.hpp" 


NeuralNetwork* net  ; 
NetAnnealer*  annealer  ; 
NetPerturber* perturber  ; 
NetEvaluator* evaluator  ; 
TempSchedule* tempSchedule ;
Feeder* stimFeeder ; 
Feeder* targetFeeder ; 

bool test1() {

    try{
		net = new NeuralNetwork() ; 
		annealer = new NetAnnealer() ; 
        annealer->setAnnealingTarget(net) ; 
        annealer->setIterPerTemp(4) ; 
		perturber = new NetPerturber() ; 
		evaluator = new NetEvaluator() ; 
		tempSchedule= new PowerTempSchedule() ;
        tempSchedule->setNumPoints(5) ; 
        tempSchedule->setHighTemp(3.0) ; 
        tempSchedule->setLowTemp(0.001) ; 
        annealer->setTempSchedule(tempSchedule) ; 
        net->setPerturber(perturber) ; 
        stimFeeder = new FileFeeder() ; 
        targetFeeder = new FileFeeder() ; 

        ((FileFeeder*) stimFeeder)->setFile("../../DATA/TEST/shorttest.txt") ; 
        ((FileFeeder*) targetFeeder)->setFile("../../DATA/TEST/short2test.txt") ; 
        stimFeeder->setDeltaT(0.5) ; 

        evaluator->setStimulus(stimFeeder) ; 
        evaluator->setTarget(targetFeeder) ; 
        net->setEvaluator(evaluator) ; 

        try{
            cout << "start ANNEAL" << endl ; 
            annealer->anneal() ; 
            cout << "stop ANNEAL" << endl ; 
        }
        catch(const char* error){
            cout << "problem: " << error << endl ; 
            return false ; 
        }
        catch(...){
            cout << "error" << endl ; 
            return false ; 
        }
        return true; 
    }
    catch(...){

        cout << "error, test fail" << endl ; 
        return false ; 

    }
}  

// add the fileFeeder
bool test2(){


    // init the pieces
		net = new NeuralNetwork() ; 
		annealer = new NetAnnealer() ; 
        annealer->setAnnealingTarget(net) ; 
		perturber = new NetPerturber() ; 
		evaluator = new NetEvaluator() ; 
        tempSchedule= new PowerTempSchedule() ;
        stimFeeder = new FileFeeder() ; 
        targetFeeder = new FileFeeder() ; 

        tempSchedule->setNumPoints(12) ; 
        tempSchedule->setHighTemp(3.0) ; 
        tempSchedule->setLowTemp(0.001) ; 
        annealer->setTempSchedule(tempSchedule) ; 
        net->setEvaluator(evaluator) ; 
        net->setPerturber(perturber) ; 

        ((FileFeeder*) stimFeeder)->setFile("../../DATA/TEST/shorttest.txt") ; 
        ((FileFeeder*) targetFeeder)->setFile("../../DATA/TEST/shorttest.txt") ; 


        while(stimFeeder->hasMorePoints()){
            cout << "hasMorePoints: " << stimFeeder->getNextPoint() << endl  ; 
        }
        cout << "no more points" << endl ; 
        cout << "reset MORE points" << endl ; 
        stimFeeder->reset() ; 
        while(stimFeeder->hasMorePoints()){
            cout << "hasMorePoints: " << stimFeeder->getNextPoint() << endl  ; 
        }
            

        while(targetFeeder->hasMorePoints()){
            cout << " valid " << targetFeeder->isTimePointValid() << " time: " << targetFeeder->getCurrentTime() << " "  << targetFeeder->getNextTimeStep(4) << endl  ; 
        }
        cout << "targetFeeder total time: " <<  targetFeeder->getTotalTime() << endl ; 
        cout << "reset MORE points" << targetFeeder->reset() << endl ; 
        while(targetFeeder->hasMorePoints()){
            cout << " valid " << targetFeeder->isTimePointValid() << " time: " << targetFeeder->getCurrentTime() << " "  << targetFeeder->getNextTimeStep(0.2) << endl  ; 
        }
        cout << "no more time points" << endl ; 

        StepFeeder* stepStim = new StepFeeder() ; 
        stepStim->setPreStepTime(5.0) ; 
        stepStim->setPreStepValue(1.0) ; 
        stepStim->setPostStepTime(3.0) ; 
        stepStim->setPostStepValue(0.5) ; 
        cout << "total time: " << stepStim->getTotalTime() << endl ; 
        cout << "number of points: " << stepStim->getNumPoints() << endl ; 
        stepStim->setDeltaT(0.5) ; 
        cout << "delta t to 0.5)" << endl  ; 
        cout << "total time: " << stepStim->getTotalTime() << endl ; 
        cout << "number of points: " << stepStim->getNumPoints() << endl ; 
        while(stepStim->hasMorePoints()){
            cout << "stepStim valid " << stepStim->isTimePointValid() << " time: " << stepStim->getCurrentTime() << " "  << stepStim->getNextTimeStep(0.5) << endl  ; 
        }
        stepStim->reset() ; 
        while(stepStim->hasMorePoints()){
            cout << "stepStim valid " << stepStim->isTimePointValid() << " time: " << stepStim->getCurrentTime() << " "  << stepStim->getNextTimeStep(2.0) << endl  ; 
        }

        // next, set up stepTarget
        FileFeeder* stepTarget = new FileFeeder() ; 
        stepTarget->setFile("../../DATA/TEST/short2test.txt") ; 

        stepStim->setDeltaT(1.0) ; 
        stepTarget->setDeltaT(2.0) ; 
        stepStim->reset() ; 
        stepTarget->reset() ; 
        tempSchedule->setNumPoints(1) ; 

        cout << "-------------------\n---------------------" << endl ; 
        while(stepStim->hasMorePoints()){
            cout << "stepStim valid " << stepStim->isTimePointValid() << " time: " << stepStim->getCurrentTime() << " "  << stepStim->getNextPoint() << endl  ; 
        }
        cout << "-------------------\n---------------------" << endl ; 
        while(stepTarget->hasMorePoints()){
            cout << "stepTarget valid " << stepTarget->isTimePointValid() << " time: " << stepTarget->getCurrentTime() << " "  << stepTarget->getNextPoint() << endl  ; 
        }
        cout << "-------------------\n---------------------" << endl ; 
        evaluator->setStimulus(stepStim) ; 
        evaluator->setTarget(stepTarget) ; 

        // run an annealing test for the different error
        try{
            NeuralNetwork* net = (NeuralNetwork*) annealer->anneal() ; 
            cout << "bestnet eval: " << net->eval() << endl ; 
        }
        catch(const char * error){
            cout << "error: " << error << endl ; 
        }
        catch(...){
            cout << "nasty error" << endl ; 
        }

        cout << "-------------------\n---------------------" << endl ; 

        SetFeeder* stimSetFeeder = new SetFeeder() ; 
        StepFeeder* feederA = new StepFeeder() ; 
                feederA->setPreStepTime(40.0) ; 
                feederA->setPreStepValue(1.0) ; 
                feederA->setPostStepTime(40.0) ; 
                feederA->setPostStepValue(0.5) ; 
                feederA->setDeltaT(1) ; 
                StepFeeder* feederB = new StepFeeder() ; 
                feederB->setPreStepTime(40.0) ; 
                feederB->setPreStepValue(1.0) ; 
                feederB->setPostStepTime(40.0) ; 
                feederB->setPostStepValue(1.2) ; 
                feederB->setDeltaT(1) ; 
                stimSetFeeder->addFeeder(feederA) ; 
                stimSetFeeder->addFeeder(feederB) ; 
                SetFeeder* targetSetFeeder = new SetFeeder() ; 
                FileFeeder* targetFeederA = new FileFeeder() ; 
                FileFeeder* targetFeederB = new FileFeeder() ; 
                targetFeederA->setFile("../../DATA/TEST/shorttest.txt") ; 
                targetFeederB->setFile("../../DATA/TEST/short2test.txt") ; 
                targetFeederA->setDeltaT(10) ; 
                targetFeederB->setDeltaT(10) ; 
                targetSetFeeder->addFeeder(targetFeederA) ; 
                targetSetFeeder->addFeeder(targetFeederB) ; 
                cout << "stimSetFeeder totalTime: " << stimSetFeeder->getTotalTime() << endl ; 
        cout << "targetSetFeeder totalTime: " << targetSetFeeder->getTotalTime() << endl ;

                evaluator->setStimulus(stimSetFeeder) ; 
            evaluator->setTarget(targetSetFeeder) ; 
        
        double netValue = net->eval() ; 
        cout  << "netValue: " << netValue << endl ; 
            

        return true ;

} 

int test3(){

    cout << "-------------------\n---------------------" << endl ; 
    cout << "test3, does the feeder scale and offset" << endl ; 
  
    StepFeeder* stepStim = new StepFeeder() ; 
    stepStim->setPreStepTime(5.0) ; 
    stepStim->setPreStepValue(100.0) ; 
    stepStim->setPostStepTime(3.0) ; 
    stepStim->setPostStepValue(-100.0) ; 


    stepStim->reset() ; 
    cout << "default: " << endl ; 
    while(stepStim->hasMorePoints()){
        cout << stepStim->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    stepStim->setScale(0.05) ; 
    stepStim->reset() ; 
    cout << "scale by 0.05: " << endl ; 
    while(stepStim->hasMorePoints()){
        cout << stepStim->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    stepStim->setOffset(-2) ; 
    stepStim->reset() ; 
    cout << "offset by -2: " << endl ; 
    while(stepStim->hasMorePoints()){
        cout << stepStim->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 


    // do file scale
    cout << "File feeder" << endl ;
    FileFeeder *fileFeeder = new FileFeeder() ; 
    fileFeeder->setFile("../../DATA/TEST/shorttest.txt") ; 
    fileFeeder->reset() ; 
    cout << "default: " << endl ; 
    while(fileFeeder->hasMorePoints()){
        cout << fileFeeder->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    fileFeeder->setScale(0.05) ; 
    fileFeeder->reset() ; 
    cout << "scale by 0.05: " << endl ; 
    while(fileFeeder->hasMorePoints()){
        cout << fileFeeder->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    fileFeeder->setOffset(-2) ; 
    fileFeeder->reset() ; 
    cout << "offset by -2: " << endl ; 
    while(fileFeeder->hasMorePoints()){
        cout << fileFeeder->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 


   

    // do SetFeeder
    SetFeeder *setFeeder = new SetFeeder() ; 
    setFeeder->addFeeder(stepStim) ; 
    setFeeder->addFeeder(fileFeeder) ; 
    setFeeder->setOffset(0.0) ; 
    setFeeder->setScale(1.0) ; 

    cout << "Set feeder" << endl ;
    setFeeder->reset() ; 
    cout << "default: " << endl ; 
    while(setFeeder->hasMorePoints()){
        cout << setFeeder->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    setFeeder->setScale(0.05) ; 
    setFeeder->reset() ; 
    cout << "scale by 0.05: " << endl ; 
    while(setFeeder->hasMorePoints()){
        cout << setFeeder->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    setFeeder->setOffset(-2) ; 
    setFeeder->reset() ; 
    cout << "offset by -2: " << endl ; 
    while(setFeeder->hasMorePoints()){
        cout << setFeeder->getNextTimeStep(1.0) << " " ; 
    }
    cout << endl ; 

    return true ; 

}

int test4(){


    cout << "-------------------\n---------------------" << endl ; 
    cout << "test4: test the evaluations of timesteps" << endl ; 
    cout << "test4: using a consistent target larget than 1, error should remain" << endl ; 
    cout << "test4: the same, regardless of timesteps, for all 3 feeder varieties" << endl ; 

    net = new NeuralNetwork() ; 
    evaluator = new BinNetEvaluator() ; 

    StepFeeder* stim1 = new StepFeeder() ; 
    StepFeeder* target1 = new StepFeeder() ; 
    stim1->setPreStepTime(1.0) ; 
    stim1->setPreStepValue(1.0) ; 
    stim1->setPostStepTime(9.0) ; 
    stim1->setPostStepValue(0.5) ; 

    target1->setPreStepTime(0.0) ; 
    target1->setPreStepValue(1.0) ; 
    target1->setPostStepTime(10.0) ; 
    target1->setPostStepValue(0.5) ; 

    stim1->setDeltaT(1.0) ; 
    target1->setDeltaT(1.0) ; 


    evaluator->setStimulus(stim1) ; 
    evaluator->setTarget(target1) ; 
    net->setEvaluator(evaluator) ; 

    cout << "deltaT = 1.0 for both: net->eval():" << net->eval() << endl ; 
    TextEvalTrace* tracer = new TextEvalTrace() ; 
    tracer->setEvaluator(evaluator) ;   // definitely want this to be a 
    cout << "errorTrace: " << endl << tracer->errorTrace() << endl ; 
    cout << "allNeuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 

    stim1->setDeltaT(0.1) ; 
    target1->setDeltaT(1.0) ; 
    evaluator->setStimulus(stim1) ; 
    evaluator->setTarget(target1) ; 
    net->setEvaluator(evaluator) ; 
    net->reset() ; 
    cout << "stim deltaT = 0.1 : net->eval():" << net->eval() << endl ; 

    tracer->setEvaluator(evaluator) ;   // definitely want this to be a 
    cout << "errorTrace: " << tracer->errorTrace() << endl ; 
//    cout << "allNeuronTrace: " << endl << tracer->allNeuronTrace() << endl ; 


//    cout << "total time: " << stepStim->getTotalTime() << endl ; 
//    cout << "number of points: " << stepStim->getNumPoints() << endl ; 



    return true ; 

}


int main(){

    cout << "BEGIN tests" << endl ; 

    if( test1()){
        cout << "PASS test1" << endl ; 
    }
    else{
        cout << "FAIL test1" << endl ; 
    }

    try{
        if( test2()){
            cout << "PASS test2" << endl ; 
        }
        else{
            cout << "FAIL test2" << endl ; 
        }
    }
    catch(const char * error){
        cout << "the error: " << error  << endl ; 
        cout << "FAIL test2" << endl ; 

    }
    catch(...){
        cout << "error " << endl ; 
        cout << "FAIL test2" << endl ; 
    }
    if( test3()){
        cout << "PASS test3" << endl ; 
    }
    else{
        cout << "FAIL test3" << endl ; 
    }


    if( test4()){
        cout << "PASS test4" << endl ; 
    }
    else{
        cout << "FAIL test4" << endl ; 
    }


    cout << "END tests" << endl ; 

}

