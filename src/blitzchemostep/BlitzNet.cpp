
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string ; 

#include "BlitzNet.hpp"
#include "Note.hpp"


BlitzNet::BlitzNet(int newSize) :NeuralNetwork(), 
    mWeights(new Matrix(newSize,newSize,MEM_POLICY)),
    mWeightMask(new Matrix(newSize,newSize,MEM_POLICY)),
    mBias(new Vector(newSize,MEM_POLICY)),
    mBiasMask(new Vector(newSize,MEM_POLICY)),
    mTau(new Vector(newSize,MEM_POLICY)),
    mTauMask(new Vector(newSize,MEM_POLICY)),
    mGain(new Vector(newSize,MEM_POLICY)),
    mGainMask(new Vector(newSize,MEM_POLICY)),
    mInitNeuron(new Vector(newSize,MEM_POLICY)),
    mInitNeuronMask(new Vector(newSize,MEM_POLICY)),
    mNeurons(new Vector(newSize,MEM_POLICY)),
    mTrace(false)
{
    // cout << "BlitzNet constructor: mNeurons is: " << mNeurons << endl ; 
    // setPerturber(new BlitzNetPerturber()) ;
    // setEvaluator(new BlitzEulerNetEvaluator()) ;
    defaultRenderer = new BlitzReportNetRenderer() ;
}



BlitzNet::BlitzNet(BlitzNet* newNetwork) : NeuralNetwork() 
,mTrace(false)
{

    int newSize = newNetwork->getNumNeurons() ; 

    mWeights        = new Matrix(newSize,newSize,MEM_POLICY) ; 
    mWeightMask     = new Matrix(newSize,newSize,MEM_POLICY) ; 
    mBias           = new Vector(newSize,MEM_POLICY) ; 
    mBiasMask       = new Vector(newSize,MEM_POLICY) ; 
    mTau            = new Vector(newSize,MEM_POLICY) ; 
    mTauMask        = new Vector(newSize,MEM_POLICY) ; 
    mGain            = new Vector(newSize,MEM_POLICY) ; 
    mGainMask        = new Vector(newSize,MEM_POLICY) ; 
    mInitNeuron     = new Vector(newSize,MEM_POLICY) ; 
    mInitNeuronMask = new Vector(newSize,MEM_POLICY) ; 
    mNeurons        = new Vector(newSize,MEM_POLICY) ; 
  
    if(newSize!=mNeurons->size())  {
        setNumNeurons(newNetwork->getNumNeurons()) ; 
    }
    
    *mWeights        = *(((BlitzNet*) newNetwork)->getWeights()) ; 
    *mWeightMask     = *(((BlitzNet*) newNetwork)->getWeightMask()) ; 
    *mBias           = *(((BlitzNet*) newNetwork)->getBias()) ; 
    *mBiasMask       = *(((BlitzNet*) newNetwork)->getBiasMask()) ; 
    *mTau            = *(((BlitzNet*) newNetwork)->getTau()) ; 
    *mTauMask        = *(((BlitzNet*) newNetwork)->getTauMask()) ; 
    *mGain            = *(((BlitzNet*) newNetwork)->getGain()) ; 
    *mGainMask        = *(((BlitzNet*) newNetwork)->getGainMask()) ; 
    *mInitNeuron     = *(((BlitzNet*) newNetwork)->getInitNeuron()) ; 
    *mInitNeuronMask = *(((BlitzNet*) newNetwork)->getInitNeuronMask()) ; 
    *mNeurons        = *(((BlitzNet*) newNetwork)->getInitNeuron()) ; 
    setPerturber(newNetwork->getPerturber()  ) ;
    setEvaluator(newNetwork->getEvaluator()  ) ;
    setDefaultRenderer(newNetwork->getDefaultRenderer()) ;
    setNote(newNetwork->getNote()) ; 
    setTrace(newNetwork->getTrace()) ; 
    valid = false ; 
}


int BlitzNet::getNumNeurons() 
{
    if(mWeights==NULL){
        return 0 ;
    }
    return (int) sqrt((double) mWeights->size()) ;
}



// assume this the si
void BlitzNet::setNumNeurons(int newSize) {

    // correct version
  if(newSize!=mNeurons->size())  {
    mWeights->resize(newSize,newSize) ; 
    mWeightMask->resize(newSize,newSize) ; 
    mBias->resize(newSize) ;  
    mBiasMask->resize(newSize) ;  
    mTau->resize(newSize) ;  
    mTauMask->resize(newSize) ;  
    mGain->resize(newSize) ;  
    mGainMask->resize(newSize) ;  
    mInitNeuron->resize(newSize) ;  
    mInitNeuronMask->resize(newSize) ;  
    mNeurons->resize(newSize) ;  
  }

  (*mWeights) = 0 ; 
  (*mWeightMask) = 1 ; 
  (*mBias) = 0 ; 
  (*mBiasMask) = 1 ; 
  (*mTau) = 0 ; 
  (*mTauMask) = 1 ; 
  (*mGain) = 1 ;  // the default is that they are on, but do nothing
  (*mGainMask) = 0 ; // the default is that they don't change
  (*mInitNeuron) = 0 ; 
  (*mInitNeuronMask) = 1 ; 
  (*mNeurons) = 0 ; 

  valid = false ; 
}

string BlitzNet::render() {
  //    cout << "defaultRenderer: " << defaultRenderer << endl ; 
  return defaultRenderer->render(this) ; 
}

BlitzNet::~BlitzNet() 
{
     delete mWeights ; 
     delete mWeightMask ; 
     delete mBias  ; 
     delete mBiasMask  ; 
     delete mTau  ; 
     delete mTauMask  ; 
     delete mGain  ; 
     delete mGainMask  ; 
     delete mInitNeuron  ; 
     delete mInitNeuronMask  ; 
     delete mNeurons ; 
     delete mRelaxTauVector ; 
}


bool BlitzNet::reset() 
{
  (*mNeurons) = (*mInitNeuron) ; 
  valid = false ; 
  return true ; 
}

void  BlitzNet::setWeights(Matrix* newSet ) {  
  *mWeights = *(newSet) ; 
  valid = false ; 
}   

void  BlitzNet::setWeightMask(Matrix* newSet )   
{
  *mWeightMask = *(newSet) ; 
  valid = false ; 
}

void  BlitzNet::setBias(Vector* newSet )   
{
  *mBias = *(newSet) ;
  valid = false ; 
}

void  BlitzNet::setBiasMask(Vector* newSet )   
{
  *mBiasMask = *(newSet) ;
  valid = false ; 
}

void  BlitzNet::setTau(Vector* newSet )   
{
  *mTau = *(newSet) ;
  valid = false ; 
}


void BlitzNet::setGain(Vector* newVector) 
{
    *mGain = *newVector ; 
    valid = false ; 
}


void BlitzNet::setGainMask(Vector* newVector) 
{
    *mGainMask = *newVector ; 
    valid = false ; 
}


void  BlitzNet::setTauMask(Vector* newSet )   
{
  *mTauMask = *(newSet) ;
  valid = false ; 
}

void  BlitzNet::setInitNeuron(Vector* newSet )   
{
  *mInitNeuron = *(newSet) ; 
  valid = false ; 
}

void  BlitzNet::setInitNeuronMask(Vector* newSet )   
{
  mInitNeuronMask = newSet ; 
  valid = false ; 
}


void  BlitzNet::setNeurons(Vector* newSet) 
{
  *mNeurons = *(newSet) ; 
  valid = false ; 
}




BlitzNet& BlitzNet::operator=(BlitzNet &net){
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
  setTrace(net.getTrace()) ; 
  valid = false ; 
}




double BlitzNet::getMinDeltaT() 
{
    if(evaluator==NULL){
        return 0 ; 
    }

    return evaluator->getMinDeltaT() ; 
}



void BlitzNet::setTrace(double newTrace) 
{
    mTrace = newTrace ; 
}

double BlitzNet::getTrace() 
{
    return mTrace ; 
}








/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-

