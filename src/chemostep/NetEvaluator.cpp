


#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include <float.h>
#include <math.h>

#include <vector>
using std::vector ; 

using std::max ; 
using std::min ; 

#include "NetEvaluator.hpp"
#include "NeuralNetwork.hpp"
#include "Feeder.hpp"
#include "FeederSet.hpp"
#include "SetFeeder.hpp"

NetEvaluator::NetEvaluator():
    neuronTrace(new vector<vector<double>*>() ),
    errorTrace(new vector<double>() ),
    outputVector(new vector<double>() ),
    mRelaxTime(0),
    mRelaxDeltaT(0)  ,
    mRelaxTau(0) , 
    mRelaxValueVector(NULL)  ,
    numNeurons(0) ,
    numStimulus(0) ,
    numTargets(0) ,
    numSets(0) ,
    neuronCounter(0) ,
    inputVector(NULL) ,
    stimulus(NULL) ,
    target(NULL),
    currentErrorPoint(0),
    currentNeuronPoint(0),
    tempVector(NULL)
//    mRelaxLimit(0)  

{
}

vector<double>* NetEvaluator::getAllNeuronFinalTrace(int timePoint)  
{
    if(timePoint==-1){
        timePoint = neuronTrace->size()-1 ; 
    }
    return (*neuronTrace)[timePoint] ; 
}


/// Rotate neuron trace so that it can be sliced via neuron slices.  
vector<vector<double>*>* NetEvaluator::getLastFullTraceAsSeries()  
{
    vector<vector<double>*>* returnTrace = new vector<vector<double>*>() ; 

    // get number of points assuming isometric
    int numNeurons = ((*neuronTrace)[0])->size() ; // each neuron at time-point 0
    int numPoints = neuronTrace->size() ; 
    
    for(int i = 0 ; i < numNeurons ; i++){
        vector<double>* timeVec = new vector<double>() ; 
        for(int j = 0 ; j < numPoints  ; j++){
            timeVec->push_back (   (*((*neuronTrace)[j]))[i] ) ; 
        }
        returnTrace->push_back( timeVec) ; 
    }

    return returnTrace ; 
}


void NetEvaluator::setRelaxTau(double newRelaxTau) {
   mRelaxTau = newRelaxTau ; 
}

void NetEvaluator::setRelaxValue(double newRelaxValue) 
{
    // get the correct sizes
    if(mRelaxValueVector==NULL){
        if(stimulus==NULL){
            mRelaxValueVector = new vector<double>(1) ; 
        }
        else{
            mRelaxValueVector = new vector<double>(stimulus->getNumInputs()) ; 
        }
    }
    if(stimulus!=NULL && (mRelaxValueVector->size()!=stimulus->getNumInputs())   ){
        mRelaxValueVector = NULL ; 
        mRelaxValueVector = new vector<double>(stimulus->getNumInputs() ) ; 
    }

    // assign the values, here
    for(int i = 0 ; i < mRelaxValueVector->size() ; i++){
        (*mRelaxValueVector)[i] = newRelaxValue ; 
    }
}


Feeder* NetEvaluator::getStimulus(int inputNum)
{ 
    stimulus->getFeeder(inputNum) ; 
}

vector<Feeder*>* NetEvaluator::getFullStimulus()
{ 
    stimulus->getFeederVector() ; 
}


vector<Feeder*>* NetEvaluator::getFullTarget()
{ 
    target->getFeederVector() ; 
}


Feeder* NetEvaluator::getTarget(int inputNum)
{ 
    target->getFeeder(inputNum) ; 
}


NetEvaluator::~NetEvaluator() 
{
    delete neuronTrace ; 
    delete errorTrace ;
    delete outputVector ; 
}


void NetEvaluator::relaxNet(bool doTrace) 
{
//    cout << "---------\nBegin relaxing net\n-----------" << endl ; 
    double oldLocalDeltaT = localDt; 
    int relaxPoints = (int) (mRelaxTime/mRelaxDeltaT) ; 
    localDt = mRelaxDeltaT ;
    for(int i = 0 ; i < relaxPoints ; i++){
        evalPoint(mRelaxValueVector,doTrace) ; 
    }
    localDt = oldLocalDeltaT ; 
//    cout << "---------\nFinished relaxing net, begin eval\n-----------" << endl ; 
}




void NetEvaluator::addErrorTrace(double newError)  
{
    (*errorTrace)[currentErrorPoint] = (newError) ; 
    ++currentErrorPoint ; 
}

void NetEvaluator::addNeuronTrace(vector<double>* newPoint) 
{
//    cout << "currentNeuronPoint: " << currentNeuronPoint << endl ; 
//    cout << "neuronTrace->size(): " << neuronTrace->size() << endl ; 
//    cout << "newPoint->size(): " << newPoint->size() << endl ; 
//    cout << "((*neuronTrace)[0])->size(): " << ((*neuronTrace)[0])->size() << endl ; 
    *((*neuronTrace)[currentNeuronPoint]) =  (*newPoint) ; 
    ++currentNeuronPoint ; 
}

vector<double>* NetEvaluator::getLastTrace(int neuronNum) 
{
    numNeurons =  network->getNumNeurons() ;
    if(neuronNum < 0 || neuronNum >= numNeurons  ){
        neuronNum = numNeurons-1 ;  // just give the last neuron
    }
    vector<double>* oneNeuron = new vector<double>(neuronTrace->size()) ; 
    for(int i = 0 ; i < neuronTrace->size() ; i++){
        (*oneNeuron)[i] = (*(*neuronTrace)[i])[neuronNum] ;
    }
    return oneNeuron ; 
}



void NetEvaluator::setNetwork(NeuralNetwork* newNetwork) 
{
    cout << "NetEvaluator setting network " <<  endl ; 
    network = newNetwork ; 
}



void NetEvaluator::setStimulus(Feeder* newStimulus,int inputNum) {  
    if(stimulus==NULL){
        stimulus = new FeederSet() ; 
    }
    stimulus->setFeeder(newStimulus,inputNum) ; 
    numStimulus = stimulus->getNumInputs() ; 
    return ; 
}  

void NetEvaluator::setTarget(Feeder* newTarget, int inputNum) 
{
    if(target==NULL){
        target = new FeederSet() ; 
    }
    target->setFeeder(newTarget,inputNum) ; 
    numTargets = target->getNumInputs() ; 
    return ; 
}


void NetEvaluator::resetTrace(int neuronPoints, int errorPoints) 
{
    cout <<  "resetTrace neuronPoints[" << neuronPoints << "] errorPoints[" << errorPoints << "]" << endl ; 
//    outputVector = new vector<double>(1) ;
//    neuronTrace = new vector<vector<double>*>(neuronPoints) ; 
//    errorTrace = new vector<double>(errorPoints) ; 
	outputVector->clear() ; 
	neuronTrace->clear() ; 
	errorTrace->clear() ; 
    outputVector->resize(1) ; 
    neuronTrace->resize(neuronPoints) ; 
    errorTrace->resize(errorPoints) ; 
    for(int i = 0 ; i < neuronPoints ; i++){
       (*neuronTrace)[i] = new vector<double>(1) ; 
    }
}


double NetEvaluator::evalNorml(NeuralNetwork* network) 
{
    if(stimulus==NULL || target==NULL){
        // throw "stimulus or target not set" ; 
        return 0 ;
    }
    return (eval(network) / ( (double) target->getTotalTime()) ) ; 
}


double NetEvaluator::eval(NeuralNetwork* newNetwork) 
{
    if(newNetwork->getValid()==true){
        return newNetwork->getValue(); 
    }

//    cout << "evaluating in NetEvaluator" << endl ; 
    if(stimulus==NULL || target==NULL){
        // throw "stimulus or target not set" ; 
        return 0 ;
    }
    setNetwork(newNetwork)  ; 
   
    // since we don't know what to do with networks, yet, just
    // compare the difference between two inputs and use that
    maxTime = min(target->getTotalTime(),stimulus->getTotalTime()) ; 
    mMinDeltaT= min(target->getDeltaT(),stimulus->getDeltaT()) ; 
    totalPoints = (int)  (maxTime/mMinDeltaT) ; 
    theErrorPoints = (int)  (maxTime/target->getDeltaT()) ; 
    resetTrace(totalPoints,theErrorPoints) ; 
    numStimulus = stimulus->getNumInputs() ; 

    double timeCounter = 0 ; 
    double error = 0 ; 
//    double stimPoint = 0 ; 
    double targetPoint = 0 ; 
    double targetSig = 1 ; 

    stimulus->reset() ; 
    target->reset() ; 
    initEvaluator() ; 

    double localError ; 
    bool validStim; 
    bool validTarget; 

    currentNeuronPoint = 0 ; 
    currentErrorPoint = 0 ; 
    initEvaluator()  ; 
    inputVector = new vector<double>(numStimulus) ; 

    while(timeCounter < maxTime && stimulus->hasMorePoints() && target->hasMorePoints() ){
        if(stimulus->isNewSet() || target->isNewSet()){
            // reset the network
            initEvaluator()  ; 
            resetNet()  ; 
            relaxNet() ;    
            initEvaluator()  ; 
            // relax the network
        }
        validStim = stimulus->isTimePointValid() ; 
        validTarget = target->isTimePointValid() ; 
//        stimPoint = stimulus->getNextTimeStep(mMinDeltaT) ; 
        inputVector = stimulus->getNextTimeStepVector(mMinDeltaT) ; 
        targetPoint = target->getNextTimeStep(mMinDeltaT) ; 
       
        if(validStim){
            netOutput = evalPoint(inputVector) ; 
            if(validTarget){
                // assume that we always do a sum, here
//                localError = targetSig * fabs(netOutput-targetPoint) ; 
                localError = targetSig * pow( (netOutput-targetPoint),2.0)  ; 
                addErrorTrace(localError); 
                error += localError ; 
            }
        }
        timeCounter+= mMinDeltaT ;
    }
    newNetwork->setValue(error) ; 
    newNetwork->setValid(true) ; 

    return error ; 
}

double NetEvaluator::getMinDeltaT(){
    mMinDeltaT= min(target->getDeltaT(),stimulus->getDeltaT()) ; 
    return mMinDeltaT ; 
}

// should be using network output, not the stimulus, but . . . 
double NetEvaluator::evalPoint(vector<double>* stimVector, bool doTrace) 
{
    // this should be the network stimulus fed into the network and then calculated but . . . 
    // for simplicity
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*outputVector)[i] =  (*stimVector)[i] ; 
    }
    
    if(doTrace){
        addNeuronTrace( outputVector ) ; 
    }

    return (*outputVector)[0] ; 
//    return fabs(stimPoint-targetPoint) ; 
}

void NetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"netevaluator\">" << endl ;
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s,-1) ; 
  *s << "</evaluator>" << endl ;
}

//double NetEvaluator::getRelaxLimit() {
//    return(mRelaxLimit);
//}


//void NetEvaluator::setRelaxLimit(double _mRelaxLimit) {
//    mRelaxLimit = _mRelaxLimit;
//    return;
//}

void NetEvaluator::doBaseXML(ostream *s) 
{
  // output information about the left stimulus
  if(stimulus!=NULL){
      addSpacer(s,1) ; 
      *s << "<stimulus>" << endl ;
      for(int i = 0 ; i < stimulus->getNumInputs() ; i++){
          ((SetFeeder *) getStimulus(i))->toXML(s);
      }
      addSpacer(s,-1) ; 
      *s << "</stimulus>" << endl ;
  }
//  ((SetFeeder *) getStimulus(LEFT))->toXML(s);

  // output information about the target
  if(target!=NULL){
      addSpacer(s,1) ; 
      *s << "<target>" << endl ;
      for(int i = 0 ; i < target->getNumInputs() ; i++){
      // *s << "causes segmentation fault" << endl;
          ((SetFeeder *) getTarget(i))->toXML(s);
      }
      addSpacer(s,-1) ; 
      *s << "</target>" << endl ;
  }

  // output information about the relax time
  addSpacer(s) ; 
  *s << "<relaxtime value=\"" << getRelaxTime() << "\" />" << endl;

  // output information about the relax deltaT
  addSpacer(s) ; 
  *s << "<relaxdeltat value=\"" << getRelaxDeltaT() << "\" />" << endl;

  // output information about the relax deltaT
  addSpacer(s) ; 
  *s << "<mindeltat value=\"" << getMinDeltaT() << "\" />" << endl;

  // output information about the relax Tau
  addSpacer(s,-1) ; 
  *s << "<relaxtau value=\"" << mRelaxTau << "\" />" << endl;

}

double NetEvaluator::evalPoint(double newPoint,bool doTrace) 
{
    if(tempVector == NULL || tempVector->size()==0){
        tempVector = new vector<double>() ; 
        tempVector->push_back(newPoint) ; 
    }
    else{
        (*tempVector)[0] = newPoint ; 
    }
    return evalPoint(tempVector,doTrace) ; 
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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

