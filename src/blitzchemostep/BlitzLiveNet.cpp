
#include <iostream>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

//#include "ErrorModel.hpp"
#include <BlitzLiveNet.hpp>
#include <blitzdefs.hpp>
 

/*  ***********************************************************************************
    Default Constructor */
   
//! Uses default size and initial array contents used by calls to static class interface
/*  *********************************************************************************** */
BlitzLiveNet::BlitzLiveNet(): BlitzNet()
,concentrationPoint(NULL)
{
}


/** Copy constructor and assignment operator */
   
//! Empty body. Make sure the Blitz vectors are copied correctly
/*  *********************************************************************************** */
BlitzLiveNet::BlitzLiveNet(BlitzLiveNet* newNetwork): BlitzNet( (BlitzNet*)newNetwork)
,concentrationPoint(NULL)
{
}


/*  ***********************************************************************************
    Copy constructor and assignment operator */
   
//! Empty body. Make sure the Blitz vectors are copied correctly
/*  *********************************************************************************** */
BlitzLiveNet::BlitzLiveNet(BlitzNet* newNetwork): BlitzNet(newNetwork)
,concentrationPoint(NULL)
{
}


/*  ***********************************************************************************
    Operator override (= BlitzNet) */
   
//! Description here
/*  *********************************************************************************** */
BlitzLiveNet& BlitzLiveNet::operator=(BlitzNet &net){
  setNumNeurons(net.getNumNeurons()) ; 
  setWeights(net.getWeights()) ; 
  setWeightMask(net.getWeightMask()) ; 
  setBias(net.getBias()) ; 
  setBiasMask(net.getBiasMask()) ; 
  setTau(net.getTau()) ; 
  setTauMask(net.getTauMask()) ; 
  setGain(net.getGain()) ; 
  setGainMask(net.getGainMask()) ; 
  setInitNeuron(net.getInitNeuron()) ; 
  setInitNeuronMask(net.getInitNeuronMask()) ; 
  setNeurons(net.getNeurons()) ; 
  setEvaluator(net.getEvaluator()) ; 
  setDefaultRenderer(net.getDefaultRenderer()) ; 
  setNote(net.getNote()) ; 
  valid = false ; 
  setTrace(net.getTrace()) ; 
}


/*  ***********************************************************************************
    Operator override (= BlitzNet) */
   
//! Description here
/*  *********************************************************************************** */
BlitzLiveNet& BlitzLiveNet::operator=(BlitzLiveNet &net){
  setNumNeurons(net.getNumNeurons()) ; 
  setWeights(net.getWeights()) ; 
  setWeightMask(net.getWeightMask()) ; 
  setBias(net.getBias()) ; 
  setBiasMask(net.getBiasMask()) ; 
  setTau(net.getTau()) ; 
  setTauMask(net.getTauMask()) ; 
  setGain(net.getGain()) ; 
  setGainMask(net.getGainMask()) ; 
  setInitNeuron(net.getInitNeuron()) ; 
  setInitNeuronMask(net.getInitNeuronMask()) ; 
  setNeurons(net.getNeurons()) ; 
  setEvaluator(net.getEvaluator()) ; 
  setDefaultRenderer(net.getDefaultRenderer()) ; 
  setNote(net.getNote()) ; 
  valid = false ; 
  setTrace(net.getTrace()) ; 
}


/*  ***********************************************************************************
    EvalPoint */
   
//! Description here.
/*  *********************************************************************************** */
double BlitzLiveNet::evalPoint(double conc,int numInputs) {
//  cout << "evalPoint: " << conc << endl ; 

    if(concentrationPoint==NULL || concentrationPoint->size()==0){
        concentrationPoint = new vector<double>(numInputs) ; 
    } 

//    for(int i = 0 ; i < concentrationPoint->size() ; i++){
////         (*concentrationPoint)[i] = conc * (*mGain)(i) ; 
//         (*concentrationPoint)[i] = conc  ; 
//    }

    fill(concentrationPoint->begin(),concentrationPoint->end(),conc) ; 
    return evaluator->evalPoint( concentrationPoint,mTrace) ; 
} 




