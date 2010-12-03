

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::cerr ; 
using std::cin ; 

#include <vector>
using std::vector ; 

#include "BlitzNet.hpp" 
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "BlitzEulerNetEvaluator.hpp"   
#include "BlitzNetAnnealer.hpp"   
#include "TempSchedule.hpp" 
#include "PowerTempSchedule.hpp" 
#include "NetPerturber.hpp" 


#ifdef DOMPI
    #include "mpi.h"
    int myid ; 
    int nprocs ; 
#endif 

bool test1(){


    try{
   BlitzNet *net = new BlitzNet() ; 
   net->setNumNeurons(3) ; 
//    net->setPerturber(new BlitzPerturbNet()) ;  // should register a default
  cout << "pre-perturb: " << net->render() << endl ; 
   net->perturb(4) ; 
//   cout << net->dump() << endl // should register a default
  cout << "post-perturb: " << net->render() << endl ; 
   return true ; 
    }
    catch(...){
        cerr << "error" << endl ; 
        return false ; 
    }
}


bool test2(){

    try{
   BlitzNet *net = new BlitzNet() ; 
   net->setNumNeurons(3) ; 
   Vector *newInit = new Vector(3)  ; 
   (*newInit) = 0.6 , 0.6, 0.4 ;
   net->setInitNeuron(newInit) ; 
   Vector *newBias = new Vector(3)  ; 
   (*newBias) = -0.5 , -0.5, 0.0 ;
   net->setBias(newBias) ; 
   Matrix *newWeights = new Matrix(3) ; 
   (*newWeights) = 0 , 1, 1 ,
                      0, 0, -1, 
                      0, 0, 0  ;
   net->setWeights(newWeights) ; 
//  cout << "pre-perturb: " << net->render() << endl ; 
//   (*newWeights) = 3 , 0, 1 ,
//                      0, 0, 0, 
//                      0, 0, 0  ;
//                   // SHOULD NOT CHANGE
//  cout << "pre2-perturb: " << net->render() << endl ; 
//  cout << "should be 0,0,1, 0,0,0  0,0,0 " << endl ; 

   StepFeeder *stimFeeder = new StepFeeder() ; 
   stimFeeder->setPreStepValue(0.4) ; 
   stimFeeder->setPostStepValue(0.5) ; 
   stimFeeder->setPreStepTime(20) ; 
   stimFeeder->setPostStepTime(20) ; 
   StepFeeder *targetFeeder = new StepFeeder() ; 
   targetFeeder->setPreStepValue(0.5) ; 
   targetFeeder->setPostStepValue(0.5) ; 
   targetFeeder->setPreStepTime(20) ; 
   targetFeeder->setPostStepTime(20) ; 
   BlitzEulerNetEvaluator* evaluator = new BlitzEulerNetEvaluator(); 
   evaluator->setStimulus(stimFeeder) ; 
   evaluator->setTarget(targetFeeder) ; 
   net->setEvaluator(evaluator) ; 
   cout << "A" << endl ; 
   // (DONE) need to confirm values (probably for more points) 
   // (DONE) need to confirm error for values (probably for more points)
   cout << net->eval() << endl  ;   
   // (DONE) need to add tracing for error 
   vector<double>* theError = evaluator->getLastErrorTrace() ; 
   cout << "errortrace: " ; 
   for(int i = 0 ; i < theError->size() ; i++){
       cout << (*theError)[i]  << " " ; 
   }
   cout << endl ; 
   //  (DONE) need to add tracing for neurons
   vector<double>* outputTrace = evaluator->getLastTrace(2) ; 
   cout << "outputTrace: " ; 
   for(int i = 0 ; i < outputTrace->size() ; i++){
       cout << (*outputTrace)[i]  << " " ; 
   }
   cout << endl ; 
   // (DONE) need to add resetting for larger sets  // pretty sure about this
   // (DONE) need to add relaxing for larger sets 
   cout << "set relax" << endl ; 
   evaluator->setRelaxTime(50) ; 
   evaluator->setRelaxDeltaT(1) ; 
   evaluator->setRelaxValue(0.5) ; 
   net->eval() ; 
   outputTrace = evaluator->getLastTrace(2) ; 
   cout << "RELAXED outputTrace: " ; 
   for(int i = 0 ; i < outputTrace->size() ; i++){
       cout << (*outputTrace)[i]  << " " ; 
   }
   cout << endl ; 

   // (DONE) test on sets of steps
   stimFeeder->setPreStepValue(0.5) ; 
   stimFeeder->setPostStepValue(2.0) ; 
   StepFeeder *stimFeeder1 = new StepFeeder() ; 
   stimFeeder1->setPreStepValue(0.5) ; 
   stimFeeder1->setPostStepValue(2.0) ; 
   stimFeeder1->setPreStepTime(20) ; 
   stimFeeder1->setPostStepTime(20) ; 

   targetFeeder->setPreStepValue(0.5) ; 
   targetFeeder->setPostStepValue(0.5) ; 
   StepFeeder *targetFeeder1 = new StepFeeder() ; 
   targetFeeder1->setPreStepValue(0.5) ; 
   targetFeeder1->setPostStepValue(0.5) ; 
   targetFeeder1->setPreStepTime(20) ; 
   targetFeeder1->setPostStepTime(20) ; 
   SetFeeder *setStim = new SetFeeder() ; 
   setStim->addFeeder(stimFeeder) ; 
   setStim->addFeeder(stimFeeder1) ; 
   SetFeeder *setTarget = new SetFeeder() ; 
   setTarget->addFeeder(targetFeeder) ; 
   setTarget->addFeeder(targetFeeder1) ; 
   evaluator->setStimulus(setStim) ; 
   evaluator->setTarget(setTarget) ; 
   net->setEvaluator(evaluator) ; 

   // (DONE) check to make sure its resetting and relaxing
   // definitely iterator over both the error and the values
   // first check the low-error (initially) 
   // first check the error-at later states (initially) 
   cout << "relaxed error for two sets: " << net->eval()  << endl ; 
   theError = evaluator->getLastErrorTrace() ; 
   cout << "relaxed twoset errortrace: " ; 
   for(int i = 0 ; i < theError->size() ; i++){
       cout << "(" << i << ") " << (*theError)[i]  << " " ; 
   }
   cout << endl ; 
   outputTrace = evaluator->getLastTrace(2) ; 
   cout << "relaxed twoset outputTrace: " ; 
   for(int i = 0 ; i < outputTrace->size() ; i++){
       cout << "(" << i << ") "<< (*outputTrace)[i]  << " " ; 
   }
   cout << endl ; 
   

   // test on step versus file
   SetFeeder *setTarget2 = new SetFeeder() ; 
   FileFeeder* targetFile1 = new FileFeeder() ; 
   FileFeeder* targetFile2 = new FileFeeder() ; 
   targetFile1->setFile("../../DATA/TEST/deltat.txt") ; 
   targetFile2->setFile("../../DATA/TEST/deltat.txt") ; 
   cout << "targetFile1: "<< targetFile1 << endl ; 
   cout << "targetFile2: "<< targetFile2 << endl ; 
   setTarget2->addFeeder(targetFile1) ; 
   setTarget2->addFeeder(targetFile2) ; 
   setTarget2->setDeltaT(1.0) ; 
   evaluator->setStimulus(setStim) ; 
   evaluator->setTarget(setTarget2) ; 
   cout << "preset" << endl ;
   net->setEvaluator(evaluator) ; 
   cout << "step v file error for two sets: " << net->eval()  << endl ; 
   cout << "postset" << endl ;
   theError = evaluator->getLastErrorTrace() ; 
   cout << "relaxed twoset errortrace: " ; 
   for(int i = 0 ; i < theError->size() ; i++){
       cout << "(" << i << ") " << (*theError)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 
   outputTrace = evaluator->getLastTrace(2) ; 
   cout << "step v file error twoset outputTrace: " ; 
   for(int i = 0 ; i < outputTrace->size() ; i++){
       cout << "(" << i << ") "<< (*outputTrace)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 


   // (DONE) test on step versus file for differing dt's (our real problem) 
   cout << "----------\nDELTA2T TESTS\n-------------" << endl ; 
   SetFeeder *setTarget3 = new SetFeeder() ; 
   targetFile1 = new FileFeeder() ; 
   targetFile2 = new FileFeeder() ; 
   targetFile1->setFile("../../DATA/TEST/delta2t.txt") ; 
   targetFile2->setFile("../../DATA/TEST/delta2t.txt") ; 
   setTarget3->addFeeder(targetFile1) ; 
   setTarget3->addFeeder(targetFile2) ; 
   setTarget3->setDeltaT(2.0) ; 
   evaluator->setTarget(setTarget3) ; 
   net->setEvaluator(evaluator) ; 
   cout << "delta2t step v file error for two sets: " << net->eval()  << endl ; 
   theError = evaluator->getLastErrorTrace() ; 
   cout << "delta2t SHOULD BE 40 relaxed twoset errortrace: " ; 
   for(int i = 0 ; i < theError->size() ; i++){
       cout << "(" << i << ") " << (*theError)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 
   outputTrace = evaluator->getLastTrace(2) ; 
   cout << "delta2t  SHOULD BE 80 step v file error twoset outputTrace: " ; 
   for(int i = 0 ; i < outputTrace->size() ; i++){
       cout << "(" << i << ") "<< (*outputTrace)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 


   // integrate with annealing 
  


   // setup very simple toy-problem (with original confirmed set, one-connection)
   // add MPI
   // redo very simple toy-problem (with original confirmed set, one-connection)
   // real data
   cout << "B" << endl ; 

//   vector<vector<double>*>*  fullTrace = net->getTrace() << endl // should register a default
//   vector<double>*  singleTrace = net->getTrace(3) << endl // should register a default
//   vector<vector<double>*>*  errorTrace = net->getErrorTrace() << endl // should register a default
//  cout << "post-eval: " << net->render() << endl ; 
   return true ; 
    }
    catch(...){
        cerr << "error" << endl ; 
        return false ; 
    }
}

bool test3(int newArgc, char** newArgv){

    // init 
    BlitzNet *net = new BlitzNet() ; 
    net->setNumNeurons(3) ; 
    BlitzNetAnnealer* annealer = new BlitzNetAnnealer() ; 
    PowerTempSchedule* tempSchedule = new PowerTempSchedule() ;  
    BlitzNetPerturber* perturber = new BlitzNetPerturber() ; 
    BlitzEulerNetEvaluator* evaluator = new BlitzEulerNetEvaluator() ;    

    cout << "A" << endl ; 
    // define tempoSchedule
    tempSchedule= new PowerTempSchedule() ;
//    tempSchedule->setNumPoints(50) ; 
    tempSchedule->setNumPoints(10) ; 
    tempSchedule->setHighTemp(1.0) ; 
    tempSchedule->setLowTemp(0.001) ; 
    tempSchedule->setPower(2.0) ; 
    tempSchedule->initTemps() ; 

    // fully define the net . . . offset the 
//   Matrix *newWeights = new Matrix(3) ;   // this is where this should be
//   (*newWeights) = 0 ;
//   (*newWeights) = 0 , 0, 1 ,
//                      0, 0, 0, 
//                      0, 0, 0  ;
//   (*newWeights) = 0 , 1, 1 ,
//                      0, 0, -2, 
//                      0, 0, 0  ;
//   net->setWeights(newWeights) ; 
   Matrix *newWeightMask = new Matrix(3) ;   // this is where this should be
   (*newWeightMask) = 0 , 1, 1 ,
                      0, 0, 1, 
                      0, 0, 0  ;
//    net->setWeightMask(newWeightMask) ; 
    Vector *newInit = new Vector(3)  ; 
    (*newInit) = 0.5 , 0.5, 0.5 ;  // should be the eventual value with 0.5 input
    net->setInitNeuron(newInit) ; 
    Vector *newBias = new Vector(3)  ; 
    (*newBias) = -0.5 , -0.5, 0.5 ;
    net->setBias(newBias) ; 
    Vector *newBiasMask = new Vector(3)  ; 
    (*newBiasMask) =  0 ; 
    net->setBiasMask(newBiasMask) ; 
    Vector *newTau = new Vector(3)  ; 
    (*newTau) = 5 , 5, 5 ;
    net->setTau(newTau) ; 
    Vector *newTauMask = new Vector(3)  ; 
    (*newTauMask) =  0 ; 
    net->setTauMask(newTauMask) ; 

    cout << "B" << endl ; 
   // set feedser
   StepFeeder *stimFeeder1 = new StepFeeder() ; 
   StepFeeder *stimFeeder2 = new StepFeeder() ; 
   FileFeeder* targetFile1 = new FileFeeder() ; 
   FileFeeder* targetFile2 = new FileFeeder() ; 
   SetFeeder *stimSet = new SetFeeder() ; 
   SetFeeder *targetSet = new SetFeeder() ; 
   stimFeeder1->setPreStepValue(0.5) ; 
   stimFeeder1->setPostStepValue(2.0) ; 
//   stimFeeder1->setPostStepValue(0.5) ; 
   stimFeeder1->setPreStepTime(20) ; 
   stimFeeder1->setPostStepTime(20) ; 
   stimFeeder2->setPreStepValue(0.5) ; 
//   stimFeeder2->setPostStepValue(0.2) ; 
   stimFeeder2->setPostStepValue(0.0) ; 
   stimFeeder2->setPreStepTime(20) ; 
   stimFeeder2->setPostStepTime(20) ; 
//   targetFile1->setFile("DATA/delta2t.txt") ; 
//   targetFile2->setFile("DATA/delta2t.txt") ; 


    cout << "C" << endl ; 
   targetFile1->setFile("../../DATA/TEST/upstep1.txt") ; 
   targetFile2->setFile("../../DATA/TEST/downstep1.txt") ; 
//   targetFile1->setFile("DATA/upstep2.txt") ; 
//   targetFile1->setDeltaT(2.0) ; 
//   targetFile2->setFile("DATA/downstep2.txt") ; 
//   targetFile2->setDeltaT(2.0) ; 
   stimSet->addFeeder(stimFeeder1) ; 
   stimSet->addFeeder(stimFeeder2) ; 
   targetSet->addFeeder(targetFile1) ; 
   targetSet->addFeeder(targetFile2) ; 
//   targetSet->setDeltaT(2.0) ; 

   evaluator->setStimulus(stimSet) ; 
   evaluator->setTarget(targetSet) ; 
   evaluator->setRelaxTime(30) ; 
   evaluator->setRelaxDeltaT(1) ; 
   evaluator->setRelaxValue(0.5) ; 

    cout << "E" << endl ; 

    net->setEvaluator(evaluator) ; 


    cout << "F" << endl ; 
    net->eval() ; 
   cout << "test3 withstep output list: " ; 
   vector<double>* lastNeuronTrace = evaluator->getLastTrace(2) ; 
   cout << "fullTrace list: " << lastNeuronTrace->size() << endl ; 
   for(int i = 0 ; i < lastNeuronTrace->size() ; i++){
       cout << "(" << i << ") "<< (*lastNeuronTrace)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 


    net->setPerturber(perturber) ; 

    annealer->setArguments(newArgc,newArgv) ; 
    annealer->setTempSchedule(tempSchedule) ; 
    annealer->setIterPerTemp(1000) ; 
//    annealer->setIterPerTemp(10000) ; 
    annealer->setAnnealingTarget(net) ; 

   cout << "test3 init: " << net->eval()  << endl ; 
   cout << "theWeightMaske: " << *(net->getWeightMask()) <<endl ; 
   vector<double>* theError = evaluator->getLastErrorTrace() ; 
   cout << "test3 error list: " ; 
   for(int i = 0 ; i < theError->size() ; i++){
       cout << "(" << i << ") " << (*theError)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 

   vector<vector<double>*>* theNeuronTrace = evaluator->getLastFullTrace() ; 
   cout << "test3 output list: " ; 
   cout << "neuronTrace list: " << theNeuronTrace->size() << endl ; 
   vector<double>* outputNeuronValues = (*theNeuronTrace)[theNeuronTrace->size()-1] ; 
   for(int i = 0 ; i < outputNeuronValues->size() ; i++){
       cout << "(" << i << ") "<< (*outputNeuronValues)[i]  << " " ; 
       if(i%4==0) cout << endl ; 
   }
   cout << endl ; 

    try{
        cout << "start ANNEAL" << endl ; 
        BlitzNet* greatNet = new BlitzNet((BlitzNet*) annealer->anneal()) ; 
        #ifdef DOMPI 
        MPI_Comm_rank(MPI_COMM_WORLD, &myid);
        MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
        if(myid==0){
        #endif
        cout << "the great net: " << greatNet->render() << endl ; 
        cout << "stop ANNEAL" << endl ; 
       cout << "test3 final: " << greatNet->eval()  << endl ; 
       BlitzEulerNetEvaluator* thisEvaluator = (BlitzEulerNetEvaluator*)greatNet->getEvaluator() ; 
       theError = thisEvaluator->getLastErrorTrace() ; 
       cout << "test3 final error list: " ; 
       for(int i = 0 ; i < theError->size() ; i++){
           cout << "(" << i << ") " << (*theError)[i]  << " " ; 
           if(i%4==0) cout << endl ; 
       }
       cout << endl ; 
       vector<double>* outputTrace = thisEvaluator->getLastTrace(2) ; 
       cout << "test3 final output list: " ; 
       for(int i = 0 ; i < outputTrace->size() ; i++){
           cout << "(" << i << ") "<< (*outputTrace)[i]  << " " ; 
           if(i%4==0) cout << endl ; 
       }
       cout << endl ; 


       vector<vector<double>*>* fullTrace = evaluator->getLastFullTrace() ; 
       cout << "test3 output list: " ; 
       cout << "fullTrace list: " << fullTrace->size() << endl ; 
       vector<double>* lastNeurons = (*fullTrace)[fullTrace->size()-1] ; 
       for(int i = 0 ; i < lastNeurons->size() ; i++){
           cout << "(" << i << ") "<< (*lastNeurons)[i]  << " " ; 
           if(i%4==0) cout << endl ; 
       }
       cout << endl ; 

       #ifdef DOMPI
        }
       #endif
    }
    catch(const char* error){
        cout << "problem: " << error << endl ; 
        return false ; 
    }
    catch(...){
        cout << "error" << endl ; 
        return false ; 
    }

//    char* inputText  ; 
//    cout << "press key to finish: " << endl ;
//    cin >> inputText ; 
//    cout << "finished: " << inputText << endl ; 

    return true ; 

}



/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    cout << "argc: " << argc << endl ; 
    for(int i = 0 ; i < argc ; i++){
        cout << "i: " << i << " " << argv[i] << endl ; 
    }

    cout << "begin test1" << endl ; 
    if(test1())
        cout << "pass test1" << endl ; 
    else
        cout << "fail test1" << endl ; 
    
    cout << "------------\nbegin test2\n------------" << endl ; 
    if(test2())
        cout << "pass test2" << endl ; 
    else
        cout << "fail test2" << endl ; 

    #ifdef DOMPI
        MPI_Init(&argc,&argv) ; 
        MPI_Comm_rank(MPI_COMM_WORLD,&myid) ; 
        MPI_Comm_size(MPI_COMM_WORLD,&nprocs) ; 
    #endif 

    cout << "------------\nbegin test3\n------------" << endl ; 
    if(test3(argc,argv))
        cout << "pass test3" << endl ; 
    else
        cout << "fail test3" << endl ; 

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

