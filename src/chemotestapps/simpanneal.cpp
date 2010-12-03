
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
#include "BlitzEulerNetEvaluator.hpp"   
#include "BlitzNetAnnealer.hpp"   
#include "TempSchedule.hpp" 
#include "PowerTempSchedule.hpp" 
#include "NetPerturber.hpp" 
#include "RNG.hpp" 


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
    BlitzNet *net = new BlitzNet() ; 
    BlitzNetAnnealer* annealer = new BlitzNetAnnealer() ; 
    PowerTempSchedule* tempSchedule = new PowerTempSchedule() ;  
    BlitzNetPerturber* perturber = new BlitzNetPerturber() ; 
    BlitzEulerNetEvaluator* evaluator = new BlitzEulerNetEvaluator() ;    
    // set feeders
    SetFeeder *stimSet = new SetFeeder() ; 
    SetFeeder *targetSet = new SetFeeder() ; 
    // stim feeders
   StepFeeder *stimFeeder1 = new StepFeeder() ; 
   StepFeeder *stimFeeder2 = new StepFeeder() ; 
   StepFeeder *stimFeeder3 = new StepFeeder() ; 
   StepFeeder *stimFeeder4 = new StepFeeder() ; 
   StepFeeder *stimFeeder5 = new StepFeeder() ; 
   StepFeeder *stimFeeder6 = new StepFeeder() ; 
   StepFeeder *stimFeeder7 = new StepFeeder() ; 
   StepFeeder *stimFeeder8 = new StepFeeder() ; 
   StepFeeder *stimFeeder9 = new StepFeeder() ; 
   StepFeeder *stimFeeder10 = new StepFeeder() ; 
   StepFeeder *stimFeeder11 = new StepFeeder() ; 
   StepFeeder *stimFeeder12 = new StepFeeder() ; 
   StepFeeder *stimFeeder13 = new StepFeeder() ; 
   StepFeeder *stimFeeder14 = new StepFeeder() ; 
   StepFeeder *stimFeeder15 = new StepFeeder() ; 
   StepFeeder *stimFeeder16 = new StepFeeder() ; 
   // target feeders
   FileFeeder* targetFile1 = new FileFeeder() ; 
   FileFeeder* targetFile2 = new FileFeeder() ; 
   FileFeeder* targetFile3 = new FileFeeder() ; 
   FileFeeder* targetFile4 = new FileFeeder() ; 
   FileFeeder* targetFile5 = new FileFeeder() ; 
   FileFeeder* targetFile6 = new FileFeeder() ; 
   FileFeeder* targetFile7 = new FileFeeder() ; 
   FileFeeder* targetFile8 = new FileFeeder() ; 
   FileFeeder* targetFile9 = new FileFeeder() ; 
   FileFeeder* targetFile10 = new FileFeeder() ; 
   FileFeeder* targetFile11 = new FileFeeder() ; 
   FileFeeder* targetFile12 = new FileFeeder() ; 
   FileFeeder* targetFile13 = new FileFeeder() ; 
   FileFeeder* targetFile14 = new FileFeeder() ; 
   FileFeeder* targetFile15 = new FileFeeder() ; 
   FileFeeder* targetFile16 = new FileFeeder() ; 



    // define tempoSchedule
    tempSchedule= new PowerTempSchedule() ;
    tempSchedule->setNumPoints(50) ; 
    tempSchedule->setHighTemp(4.0) ; 
    tempSchedule->setLowTemp(0.001) ; 
    tempSchedule->setPower(3.0) ; 
    tempSchedule->initTemps() ; 

   

    // set feeders
   stimFeeder1->setPreStepValue(40.0) ; 
   stimFeeder1->setPostStepValue(50.0) ; 
   stimFeeder1->setPreStepTime(120) ; 
   stimFeeder1->setPostStepTime(180) ; 
   targetFile1->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e40_50fwd.txt") ; 
   targetFile1->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e40_50fwdsig.txt") ; 
   stimFeeder2->setPreStepValue(50.0) ; 
   stimFeeder2->setPostStepValue(60.0) ; 
   stimFeeder2->setPreStepTime(120) ; 
   stimFeeder2->setPostStepTime(180) ; 
   targetFile2->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_60fwd.txt") ; 
   targetFile2->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_60fwdsig.txt") ; 
   stimFeeder3->setPreStepValue(0.0) ; 
   stimFeeder3->setPostStepValue(50.0) ; 
   stimFeeder3->setPreStepTime(120) ; 
   stimFeeder3->setPostStepTime(180) ; 
   targetFile3->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e0_50fwd.txt") ; 
   targetFile3->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e0_50fwdsig.txt") ; 
   stimFeeder4->setPreStepValue(50.0) ; 
   stimFeeder4->setPostStepValue(100.0) ; 
   stimFeeder4->setPreStepTime(120) ; 
   stimFeeder4->setPostStepTime(180) ; 
   targetFile4->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_100fwd.txt") ; 
   targetFile4->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_100fwdsig.txt") ; 
   stimFeeder5->setPreStepValue(50.0) ; 
   stimFeeder5->setPostStepValue(150.0) ; 
   stimFeeder5->setPreStepTime(120) ; 
   stimFeeder5->setPostStepTime(180) ; 
   targetFile5->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_150fwd.txt") ; 
   targetFile5->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_150fwdsig.txt") ; 
   stimFeeder6->setPreStepValue(50.0) ; 
   stimFeeder6->setPostStepValue(40.0) ; 
   stimFeeder6->setPreStepTime(120) ; 
   stimFeeder6->setPostStepTime(180) ; 
   targetFile6->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_40fwd.txt") ; 
   targetFile6->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_40fwdsig.txt") ; 
   stimFeeder7->setPreStepValue(60.0) ; 
   stimFeeder7->setPostStepValue(50.0) ; 
   stimFeeder7->setPreStepTime(120) ; 
   stimFeeder7->setPostStepTime(180) ; 
   targetFile7->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e60_50fwd.txt") ; 
   targetFile7->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e60_50fwdsig.txt") ; 
   stimFeeder8->setPreStepValue(50.0) ; 
   stimFeeder8->setPostStepValue(0.0) ; 
   stimFeeder8->setPreStepTime(120) ; 
   stimFeeder8->setPostStepTime(180) ; 
   targetFile8->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_0fwd.txt") ; 
   targetFile8->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_0fwdsig.txt") ; 
   stimFeeder9->setPreStepValue(100.0) ; 
   stimFeeder9->setPostStepValue(50.0) ; 
   stimFeeder9->setPreStepTime(120) ; 
   stimFeeder9->setPostStepTime(180) ; 
   targetFile9->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e100_50fwd.txt") ; 
   targetFile9->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e100_50fwdsig.txt") ; 
   stimFeeder10->setPreStepValue(150.0) ; 
   stimFeeder10->setPostStepValue(50.0) ; 
   stimFeeder10->setPreStepTime(120) ; 
   stimFeeder10->setPostStepTime(180) ; 
   targetFile10->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e150_50fwd.txt") ; 
   targetFile10->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e150_50fwdsig.txt") ; 
   stimFeeder11->setPreStepValue(0.0) ; 
   stimFeeder11->setPostStepValue(0.0) ; 
   stimFeeder11->setPreStepTime(120) ; 
   stimFeeder11->setPostStepTime(180) ; 
   targetFile11->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_c0_0fwd.txt") ; 
   stimFeeder12->setPreStepValue(40.0) ; 
   stimFeeder12->setPostStepValue(40.0) ; 
   stimFeeder12->setPreStepTime(120) ; 
   stimFeeder12->setPostStepTime(180) ; 
   targetFile12->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_c40_40fwd.txt") ; 
   stimFeeder13->setPreStepValue(50.0) ; 
   stimFeeder13->setPostStepValue(50.0) ; 
   stimFeeder13->setPreStepTime(120) ; 
   stimFeeder13->setPostStepTime(180) ; 
   targetFile13->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_c50_50fwd.txt") ; 
   stimFeeder14->setPreStepValue(60.0) ; 
   stimFeeder14->setPostStepValue(60.0) ; 
   stimFeeder14->setPreStepTime(120) ; 
   stimFeeder14->setPostStepTime(180) ; 
   targetFile14->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_c60_60fwd.txt") ; 
   stimFeeder15->setPreStepValue(100.0) ; 
   stimFeeder15->setPostStepValue(100.0) ; 
   stimFeeder15->setPreStepTime(120) ; 
   stimFeeder15->setPostStepTime(180) ; 
   targetFile15->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_c100_100fwd.txt") ; 
   stimFeeder16->setPreStepValue(150.0) ; 
   stimFeeder16->setPostStepValue(150.0) ; 
   stimFeeder16->setPreStepTime(120) ; 
   stimFeeder16->setPostStepTime(180) ; 
   targetFile16->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_c150_150fwd.txt") ; 






   // add feeders to the stimulus
   stimSet->addFeeder(stimFeeder1) ; 
   stimSet->addFeeder(stimFeeder2) ; 
   stimSet->addFeeder(stimFeeder3) ; 
   stimSet->addFeeder(stimFeeder4) ; 
   stimSet->addFeeder(stimFeeder5) ; 
   stimSet->addFeeder(stimFeeder6) ; 
   stimSet->addFeeder(stimFeeder7) ; 
   stimSet->addFeeder(stimFeeder8) ; 
   stimSet->addFeeder(stimFeeder9) ; 
   stimSet->addFeeder(stimFeeder10) ; 
//   stimSet->addFeeder(stimFeeder11) ; 
//   stimSet->addFeeder(stimFeeder12) ; 
//   stimSet->addFeeder(stimFeeder13) ; 
//   stimSet->addFeeder(stimFeeder14) ; 
//   stimSet->addFeeder(stimFeeder15) ; 
//   stimSet->addFeeder(stimFeeder16) ; 
   stimSet->setDeltaT(0.1) ; 
   stimSet->setScale(0.02) ;  // divide by 50
   
   
   // add feeders to the target
   targetSet->addFeeder(targetFile1) ; 
   targetSet->addFeeder(targetFile2) ; 
   targetSet->addFeeder(targetFile3) ; 
   targetSet->addFeeder(targetFile4) ; 
   targetSet->addFeeder(targetFile5) ; 
   targetSet->addFeeder(targetFile6) ; 
   targetSet->addFeeder(targetFile7) ; 
   targetSet->addFeeder(targetFile8) ; 
   targetSet->addFeeder(targetFile9) ; 
   targetSet->addFeeder(targetFile10) ; 
//   targetSet->addFeeder(targetFile11) ; 
//   targetSet->addFeeder(targetFile12) ; 
//   targetSet->addFeeder(targetFile13) ; 
//   targetSet->addFeeder(targetFile14) ; 
//   targetSet->addFeeder(targetFile15) ; 
//   targetSet->addFeeder(targetFile16) ; 
   targetSet->setDeltaT(10) ; 


   // set evaluator
   evaluator->setStimulus(stimSet) ; 
   evaluator->setTarget(targetSet) ; 
   evaluator->setRelaxTime(30) ; 
   evaluator->setRelaxDeltaT(1.0) ; 
   evaluator->setRelaxValue(0.0) ; 


    // define network
    net->setNumNeurons(8) ;   // this is the default, everything is on, nothing is off
    net->setEvaluator(evaluator) ; 
    net->setPerturber(perturber) ; 

    annealer->setTempSchedule(tempSchedule) ; 
//    annealer->setIterPerTemp(10000) ; 
//    annealer->setIterPerTemp(1000) ; 
    annealer->setIterPerTemp(10) ; 
    annealer->setAnnealingTarget(net) ; 
    #ifdef DOMPI
    if(myid==0)
    #endif 
    cout << "original net: " << net->eval() << endl ; 
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

       cout << "simpanneal LAST TIME-STEP output list: " ; 
       vector<vector<double>*>* fullTrace = (greatNet->getEvaluator())->getLastFullTrace(); 
       cout << "fullTrace list: " << fullTrace->size() << endl ; 
       vector<double>* lastNeurons = (*fullTrace)[fullTrace->size()-1] ; 
       for(int i = 0 ; i < lastNeurons->size() ; i++){
           cout << "(" << i << ") "<< (*lastNeurons)[i]  << " " ; 
           if(i%4==0) cout << endl ; 
       }
       cout << endl ; 

       vector<double>* theError = evaluator->getLastErrorTrace() ; 
       cout << "test3 final error list: " ; 
       for(int i = 0 ; i < theError->size() ; i++){
           cout << "(" << i << ") " << (*theError)[i]  << " " ; 
           if(i%4==0) cout << endl ; 
       }
       cout << endl ; 
       vector<double>* outputTrace = evaluator->getLastTrace(7) ; 
       cout << "test3 final output list: " ; 
       for(int i = 0 ; i < outputTrace->size() ; i++){
          if(i%10==0){ 
           cout << "(" << i << ") "<< (*outputTrace)[i]  << " " ; 
           if(i%4==0) cout << endl ; 
          }
       }
       cout << endl ; 



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

