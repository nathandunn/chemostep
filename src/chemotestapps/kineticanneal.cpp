
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
#include "KineticBlitzEulerEval.hpp"   
#include "AutoWKineticBlitzEulerEval.hpp"   
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
//    KineticBlitzEulerEval* evaluator = new AutoWKineticBlitzEulerEval() ;    
    KineticBlitzEulerEval* evaluator = new KineticBlitzEulerEval() ;    
    // set feeders
    SetFeeder *stimLeft = new SetFeeder() ; 
    FileFeeder *stimLeft1 = new FileFeeder() ; 
    FileFeeder *stimLeft2 = new FileFeeder() ; 
    FileFeeder *stimLeft3 = new FileFeeder() ; 
    FileFeeder *stimLeft4 = new FileFeeder() ; 
    FileFeeder *stimLeft5 = new FileFeeder() ; 
    FileFeeder *stimLeft6 = new FileFeeder() ; 
    SetFeeder *stimRight = new SetFeeder() ; 
    FileFeeder *stimRight1 = new FileFeeder() ; 
    FileFeeder *stimRight2 = new FileFeeder() ; 
    FileFeeder *stimRight3 = new FileFeeder() ; 
    FileFeeder *stimRight4 = new FileFeeder() ; 
    FileFeeder *stimRight5 = new FileFeeder() ; 
    FileFeeder *stimRight6 = new FileFeeder() ; 
    SetFeeder *targetSet = new SetFeeder() ; 
    FileFeeder *targetSet1 = new FileFeeder() ; 
    FileFeeder *targetSet2 = new FileFeeder() ; 
    FileFeeder *targetSet3 = new FileFeeder() ; 
    FileFeeder *targetSet4 = new FileFeeder() ; 
    FileFeeder *targetSet5 = new FileFeeder() ; 
    FileFeeder *targetSet6 = new FileFeeder() ; 

    // stim feeders
    stimLeft1->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0bigstep.txt") ; 
    stimRight1->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1bigstep.txt") ; 
    targetSet1->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_150fwd.txt") ; 
//    targetSet1->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_150fwdsig.txt") ; 


    stimLeft2->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1bigstep.txt") ; 
    stimRight2->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0bigstep.txt") ; 
    targetSet2->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e150_50fwd.txt") ; 
//    targetSet2->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e150_50fwdsig.txt") ; 


    stimLeft3->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0smallstep.txt") ; 
    stimRight3->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1smallstep.txt") ; 
    targetSet3->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_100fwd.txt") ; 
//    targetSet3->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_100fwdsig.txt") ; 



    stimLeft4->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1smallstep.txt") ; 
    stimRight4->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0smallstep.txt") ; 
    targetSet4->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e100_50fwd.txt") ; 
//    targetSet4->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e100_50fwdsig.txt") ; 


    stimLeft5->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0smallest.txt") ; 
    stimRight5->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1smallest.txt") ; 
    targetSet5->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_60fwd.txt") ; 


    stimLeft6->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1smallest.txt") ; 
    stimRight6->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0smallest.txt") ; 
    targetSet6->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e60_50fwd.txt") ; 




    stimLeft->addFeeder(stimLeft1) ; 
    stimLeft->addFeeder(stimLeft2) ; 
    stimLeft->addFeeder(stimLeft3) ; 
    stimLeft->addFeeder(stimLeft4) ; 
    stimLeft->addFeeder(stimLeft5) ; 
    stimLeft->addFeeder(stimLeft6) ; 
    stimRight->addFeeder(stimRight1) ; 
    stimRight->addFeeder(stimRight2) ; 
    stimRight->addFeeder(stimRight3) ; 
    stimRight->addFeeder(stimRight4) ; 
    stimRight->addFeeder(stimRight5) ; 
    stimRight->addFeeder(stimRight6) ; 
    targetSet->addFeeder(targetSet1) ; 
    targetSet->addFeeder(targetSet2) ; 
    targetSet->addFeeder(targetSet3) ; 
    targetSet->addFeeder(targetSet4) ; 
    targetSet->addFeeder(targetSet5) ; 
    targetSet->addFeeder(targetSet6) ; 

    stimLeft->setDeltaT(1.0) ; 
    stimRight->setDeltaT(1.0) ; 
    targetSet->setDeltaT(10.0) ; 

    vector<double>* relaxVector = new vector<double>(2) ; 
    (*relaxVector)[0] = 0.5 ; 
    (*relaxVector)[1] = 0.5 ; 
    evaluator->setRelaxValue(relaxVector) ; 
//    evaluator->setK10(0.7351243) ; 
//    evaluator->setK01(0.727093 ) ; 
    evaluator->setStimulus(stimLeft,0) ; 
    evaluator->setStimulus(stimRight,1) ; 
    evaluator->setTarget(targetSet) ; 
    evaluator->setRelaxTime(200) ; 
    evaluator->setRelaxDeltaT(1) ; 
    evaluator->setRelaxTau(3) ; 

    int numNeurons = 10 ; 
    Matrix* weights = new Matrix(numNeurons,numNeurons) ; 
    Matrix* weightMask = new Matrix(numNeurons,numNeurons) ; 
    Vector* bias = new Vector(numNeurons) ; 
    Vector* biasMask = new Vector(numNeurons) ; 
    Vector* tau = new Vector(numNeurons) ; 
    Vector* tauMask = new Vector(numNeurons) ; 
    Vector* initNeuron = new Vector(numNeurons) ; 
    Vector* initNeuronMask= new Vector(numNeurons) ; 
    TextEvalTrace *tracer = new TextEvalTrace() ; 
    tracer->setTimeDelimiter(",") ; 
    blitzNet->setNumNeurons(numNeurons) ; 
    *initNeuron = 0.5 ; 
//    *bias = 0 ; 
//    *tau = 5 ; 
//    *weights = 0 ; 
    *bias = 
   -6.06957 ,  2.44072 ,  12.8892 ,  14.2468 , -23.1133 ,  9.48002 ,  7.19826 ,-15.7505 ,  10.6398 ,-0.622337 ;
    *tau = 
    3.54519 ,  12.5422 ,        3 ,  17.2934 ,  22.6822 ,  18.0261 ,  11.6996 ,4.30674 ,  35.5898 ,  12.0234 ;
    *weights = 
         0 ,        0 , -43.8524 , -23.4626 , -13.1033 ,  20.0098 , -5.61688 ,7.55036 ,  29.2396 ,        0 ,
          0 ,        0 ,  13.8266 ,  6.50619 ,  39.6656 , -1.79581 ,  13.7502 ,30.8831 ,  10.4948 ,        0 ,
          0 ,        0 , -18.3661 ,  18.7372 ,  16.8255 , -36.9945 ,  5.55839 ,1.48053 , -15.7608 ,  22.2747 ,
          0 ,        0 ,  21.5471 , -31.2263 , -24.3745 , -11.8141 , -23.2423 ,-42.2149 ,    16.23 , -34.6923 ,
          0 ,        0 ,  3.59731 , -6.59101 , -1.52685 , -7.46456 ,   28.488 ,5.11229 , -11.8738 ,  19.0558 ,
          0 ,        0 ,  8.39436 , -11.2732 ,  23.5922 ,  7.14364 , -7.46212 ,-20.8224 , -18.9703 , -11.4199 ,
          0 ,        0 , -16.1588 ,  2.44336 ,-0.895329 , -11.5231 , -19.5521 ,-18.158 ,  4.90187 , -15.8648 ,
          0 ,        0 ,  11.4485 ,  12.8742 , 0.889564 ,  15.5733 , -6.10084 ,16.449 , -2.68845 , -7.93988 ,
          0 ,        0 , 0.712915 ,  8.55742 ,  1.15211 , -17.1737 ,0.0849971 ,-0.905422 ,  1.46881 ,  10.3734 ,
          0 ,        0 ,        0 ,        0 ,        0 ,        0 ,        0 ,0 ,        0 ,  1.64606  ; 


    (*weightMask) =  
        0,0,1,1,1,1,1,1,1,0,  // no direct I/O connection
        0,0,1,1,1,1,1,1,1,0,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,1,1,1,1,1,1,1,1,
        0,0,0,0,0,0,0,0,0,1;
//        0,0,1,1,1,1,1,1,1,0,  // no direct I/O connection
//        0,0,1,1,1,1,1,1,1,0,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,1,1,1,1,1,1,1,1,
//        0,0,0,0,0,0,0,0,0,1;
    *biasMask = 1 ; 
    *tauMask = 1 ; 
    *initNeuronMask = 0 ; 


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
    tempSchedule->setNumPoints(150) ; 
//    tempSchedule->setNumPoints(30) ; 
    tempSchedule->setHighTemp(1.0) ; 
    tempSchedule->setLowTemp(0.001) ; 
    tempSchedule->setPower(3.0) ; 
    tempSchedule->initTemps() ; 


    annealer->setSetBack(100) ; 
    annealer->setBackStep(1) ; 
    annealer->setTempSchedule(tempSchedule) ; 
    annealer->setIterPerTemp(1000) ; 
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


//       cout << "stim trace: " << endl  << tracer->stimTrace() << endl ; 
       cout << "target trace: " << endl  << tracer->targetTrace() << endl ; 
       cout << "error trace: " << endl  << tracer->errorTrace() << endl ; 
//       cout << "all neuron trace: " << endl  << tracer->allNeuronTrace() << endl ; 
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


