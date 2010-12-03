
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream ; 


#include <vector>
using std::vector ; 

#include "BlitzNet.hpp" 
#include "RNG.hpp" 
#include "StepFeeder.hpp"   
#include "SetFeeder.hpp"   
#include "FileFeeder.hpp"   
#include "KineticBlitzEulerEval.hpp"   
#include "RNG.hpp" 
#include "TextEvalTrace.hpp" 
#include "BlitzXmlNetRenderer.hpp" 



bool runapp(int newArgc, char** newArgv){


    // init 
    BlitzNet *blitzNet = new BlitzNet() ; 
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
    
//    stimLeft1->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
//    stimRight1->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
    stimLeft1->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0bigstep.txt") ; 
    stimRight1->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1bigstep.txt") ; 
    targetSet1->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_150fwd.txt") ; 
//    targetSet1->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_150fwdsig.txt") ; 


//    stimLeft2->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
//    stimRight2->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
    stimLeft2->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1bigstep.txt") ; 
    stimRight2->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0bigstep.txt") ; 
    targetSet2->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e150_50fwd.txt") ; 
//    targetSet2->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e150_50fwdsig.txt") ; 


//    stimLeft3->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
//    stimRight3->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
    stimLeft3->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a0smallstep.txt") ; 
    stimRight3->setFile("../../DATA/CHEMOSTEP_DATA/stimDelta1/a1smallstep.txt") ; 
    targetSet3->setFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_100fwd.txt") ; 
//    targetSet3->loadSigFile("../../DATA/CHEMOSTEP_DATA/bin10sec/N2_e50_100fwdsig.txt") ; 



//    stimLeft4->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
//    stimRight4->setFile("../../DATA/CHEMOSTEP_DATA/nostim.txt") ; 
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
    *weights = 
         0 ,         0 ,  -55.9429 ,  -28.8012 ,  -14.2113 ,   19.1855 ,  -1.55262 , 7.82419 ,   29.5719 ,         0 , 
          0 ,         0 ,   17.3658 ,   1.97395 ,   42.8128 ,   1.17649 ,   8.93523 , 31.0959 ,   10.8128 ,         0 , 
          0 ,         0 ,  -4.06005 ,   21.5071 ,   19.0129 ,  -37.9486 ,   13.3154 , 1.418 ,  -15.7737 ,   29.1055 , 
          0 ,         0 ,   3.80175 ,  -30.4479 ,  -22.0954 ,   -13.186 ,  -23.6083 , -41.9427 ,    16.152 ,  -44.1546 , 
          0 ,         0 ,   3.15982 ,  -6.47401 ,  -4.20249 ,  -7.63252 ,   30.0747 , 5.43454 ,  -12.1145 ,   24.4638 , 
          0 ,         0 ,   8.60278 ,  -11.6099 ,   19.8678 ,   8.14652 , -0.553087 , -21.0857 ,  -19.2272 ,   -10.988 , 
          0 ,         0 ,  -19.3271 ,   5.04075 ,  -5.33504 ,   -10.801 ,  -16.1179 , -17.9923 ,   4.81329 ,  -16.9794 , 
          0 ,         0 ,   11.1559 ,   12.8585 ,  0.963537 ,   15.2865 ,  -6.03564 , 16.8056 ,  -2.47307 ,  -7.81154 , 
          0 ,         0 ,   5.49851 ,   7.73815 , -0.504299 ,  -18.2926 ,  -2.60346 , -1.03782 ,   1.66196 ,   13.8822 , 
          0 ,         0 ,         0 ,         0 ,         0 ,         0 ,         0 , 0 ,         0 ,  0.419676  ;
    *bias = 
   -6.30301 ,   2.18834 ,   16.3809 ,   16.2752 ,  -24.7972 ,    8.0932 ,   6.23546 , -16.0959 ,   10.6647 , -0.412287 ;
    *tau =   
    3.44021 ,    12.817 ,    3.0005 ,   15.3397 ,   23.9159 ,   7.23594 ,   7.42572 , 4.31661 ,   39.8897 ,   11.9097 ;

    blitzNet->setWeights(weights) ; 
    blitzNet->setBias(bias) ; 
    blitzNet->setTau(tau) ; 
    blitzNet->setInitNeuron(initNeuron) ; 
    blitzNet->setEvaluator(evaluator) ; 
    tracer->setEvaluator(evaluator) ; 


    cout << "original net: " << blitzNet->eval() << endl ; 
    BlitzXmlNetRenderer* renderer = new BlitzXmlNetRenderer() ; 

    ofstream xmlNet("testnet1.xml") ; 
    xmlNet << renderer->render(blitzNet) << endl ;  
    xmlNet.close() ; 


       cout << "stim trace: " << endl  << tracer->stimTrace() << endl ; 
       cout << "target trace: " << endl  << tracer->targetTrace() << endl ; 
       cout << "error trace: " << endl  << tracer->errorTrace() << endl ; 
       cout << "all neuron trace: " << endl  << tracer->allNeuronTrace() << endl ; 
       cout << "last neuron trace: " << endl  << tracer->lastNeuronTrace() << endl ; 


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


