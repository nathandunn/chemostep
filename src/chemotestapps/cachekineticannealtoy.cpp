
#include <iostream>
using std::cout ; 
using std::endl ; 


#include <vector>
using std::vector ; 

#include "BlitzNet.hpp" 
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "CachedKineticBlitzEulerEval.hpp"   
#include "BlitzNetAnnealer.hpp"   
#include "TempSchedule.hpp" 
#include "PowerTempSchedule.hpp" 
#include "NetPerturber.hpp" 
#include "RNG.hpp" 
#include "TextEvalTrace.hpp" 


#ifdef DOMPI
    #include "mpi.h"
    int myid ; 
    int nprocs ; 
#endif 

bool runapp(int newArgc, char** newArgv){

    #ifdef DOMPI
        MPI_Init(&newArgc,&newArgv) ; 
        MPI_Comm_rank(MPI_COMM_WORLD,&myid) ; 
        MPI_Comm_size(MPI_COMM_WORLD,&nprocs) ; 
      
        int seed ; 
        if(myid==0){
         seed = RNG::initSeed() ; 
        }
        MPI_Bcast(&seed, 1, MPI_INT, 0, MPI_COMM_WORLD);
        RNG::setSeed(seed+myid);
    #endif 

    #ifndef DOMPI
    RNG::initSeed() ; 
    #endif 

    // init 
    BlitzNet *blitzNet = new BlitzNet() ; 
    BlitzNetAnnealer* annealer = new BlitzNetAnnealer() ; 
    PowerTempSchedule* tempSchedule = new PowerTempSchedule() ;  
    BlitzEulerPerturber* perturber = new BlitzEulerPerturber() ; 
    CachedKineticBlitzEulerEval* evaluator = new CachedKineticBlitzEulerEval() ;    
    // set feeders
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
    evaluator->setRelaxValue(relaxVector) ; 
//    evaluator->setK10(0.7351243) ; 
//    evaluator->setK01( 0.727093 ) ; 
    evaluator->setStimulus(stimLeft,0) ; 
    evaluator->setStimulus(stimRight,1) ; 
    evaluator->setTarget(targetSet) ; 
    evaluator->setRelaxTime(100) ; 
    evaluator->setRelaxDeltaT(1) ; 
    evaluator->setRelaxTau(3) ; 

    int NET_SIZE=15 ; 
    Matrix* weights = new Matrix(NET_SIZE,NET_SIZE) ; 
    Matrix* weightMask = new Matrix(NET_SIZE,NET_SIZE) ; 
    Vector* bias = new Vector(NET_SIZE) ; 
    Vector* biasMask = new Vector(NET_SIZE) ; 
    Vector* tau = new Vector(NET_SIZE) ; 
    Vector* tauMask = new Vector(NET_SIZE) ; 
    Vector* initNeuron = new Vector(NET_SIZE) ; 
    Vector* initNeuronMask= new Vector(NET_SIZE) ; 
    TextEvalTrace *tracer = new TextEvalTrace() ; 
    tracer->setTimeDelimiter(",") ; 
    blitzNet->setNumNeurons(NET_SIZE) ; 
    *weights = 0 ; 
    *bias = 0 ; 
    *tau = 5 ; 
    *initNeuron = 0.5 ; 
    *biasMask = 1 ; 
    *tauMask = 1 ; 
    *initNeuronMask = 0 ; 
    (*weightMask) = 1 ; 
//    (*weightMask) =  0,1,1,1,
//                     0,1,1,1,
//                     0,1,1,1,
//                     0,0,0,1;
//    (*weightMask) =  0,0,1,0,
//                     0,0,0,0,
//                     0,0,0,0,
//                     0,0,0,0;
//    (*weightMask) =  0,0,1,0,
//                     0,0,1,1,
//                     0,0,0,1,
//                     0,0,0,1;
//    (*weightMask) =  0,1,1,1,1,1,1,1,
//                     0,1,1,1,1,1,1,1,
//                     0,1,1,1,1,1,1,1,
//                     0,1,1,1,1,1,1,1,
//                     0,1,1,1,1,1,1,1,
//                     0,1,1,1,1,1,1,1,
//                     0,1,1,1,1,1,1,1,
//                     0,0,0,0,0,0,0,1;
//    (*weights) =  0,0,0,0,  // the real answer
//                  0,0,10,2,
//                  0,0,0,-3,
//                  0,0,0,-2;
//    (*weights) =  0,0,-10,0,  // the real answer
//                  0,0,10,2,
//                  0,0,0,-3,
//                  0,0,0,-2;
//    (*bias) = -5,-5,-5,-5 ;   // only the middle bias matters
//    (*tau) = 30,30,30,30 ; 
//    (*initNeuron) = 0.5,0.5,0.00669285 ,0.4098808 ;  // should be the final answer
//    (*initNeuron) = 0.5,0.5,0.5,0.5; 
    blitzNet->setWeights(weights) ; 
    blitzNet->setWeightMask(weightMask) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setBiasMask(biasMask) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setTauMask(tauMask) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setInitNeuronMask(initNeuronMask) ; 
    blitzNet->setEvaluator(evaluator) ; 
    blitzNet->setPerturber(perturber) ; 
    tracer->setEvaluator(evaluator) ; 

    // define tempoSchedule
    tempSchedule= new PowerTempSchedule() ;
    tempSchedule->setNumPoints(50) ; 
    tempSchedule->setHighTemp(5.0) ; 
    tempSchedule->setLowTemp(0.01) ; 
    tempSchedule->setPower(3.0) ; 
    tempSchedule->initTemps() ; 


//    annealer->setSetBack(20) ; 
//    annealer->setSetBack(200) ; 
//    annealer->setBackStep(1) ; 
    annealer->setTempSchedule(tempSchedule) ; 
    annealer->setIterPerTemp(1000) ; 
//    annealer->setIterPerTemp(2000) ; 
    annealer->setAnnealingTarget(blitzNet) ; 
    #ifdef DOMPI
    if(myid==0)
    #endif 
    cout << "original net: " << blitzNet->eval() << endl ; 
    BlitzNet* greatNet = new BlitzNet((BlitzNet*) annealer->anneal()) ; 

    #ifdef DOMPI
    if(myid==0){
    #endif 
        cout << "final network error: " << greatNet->eval() << endl ;
        cout << "final network " << greatNet->render() << endl ;
    #ifdef DOMPI
    }
    if(myid==0){
    #endif 

//       cout << "kineticanneal LAST TIME-STEP output list: " ; 
//       vector<vector<double>*>* fullTrace = (greatNet->getEvaluator())->getLastFullTrace(); 
//       cout << "fullTrace list: " << fullTrace->size() << endl ; 
//       vector<double>* lastNeurons = (*fullTrace)[fullTrace->size()-1] ; 
//       for(int i = 0 ; i < lastNeurons->size() ; i++){
//           cout << "(" << i << ") "<< (*lastNeurons)[i]  << " " ; 
//           if(i%4==0) cout << endl ; 
//       }
//       cout << endl ; 


       cout << "error trace: " << endl  << tracer->errorTrace() << endl ; 
       cout << "all neuron trace: " << endl  << tracer->allNeuronTrace() << endl ; 
       cout << "last neuron trace: " << endl  << tracer->lastNeuronTrace() << endl ; 


    #ifdef DOMPI
    }
    MPI_Finalize() ; 
    #endif 
}

    
/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    cout << "this is the simple annealer class to be populated with real data" << endl ; 



    try{
        runapp(argc,argv) ; 
    }
    catch(string theErrorString){
        cout << "theErrorString: " << theErrorString << endl ; 
    }
    catch(const char* errorString){
        cout << "error: " << errorString << endl ; 
    }
    catch(...){
        cout << "general error" << endl ; 
    }
    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-


