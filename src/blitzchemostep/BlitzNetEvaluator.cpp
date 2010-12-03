
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <float.h>

#include "blitzdefs.hpp" 
#include "BlitzNetEvaluator.hpp"
#include "BlitzReportNetRenderer.hpp" 
#include "BlitzNetRenderer.hpp" 
#include "SigLookup.hpp" 


BlitzNetEvaluator::BlitzNetEvaluator() : BinNetEvaluator() ,
    evalWeights(new Matrix(0,0,MEM_POLICY)) , 
    evalWeightMask(new Matrix(0,0,MEM_POLICY)) , 
    evalBias(new Vector(0,MEM_POLICY)) , 
    evalBiasMask(new Vector(0,MEM_POLICY)) , 
    evalTau(new Vector(0,MEM_POLICY)) , 
    evalTauMask(new Vector(0,MEM_POLICY)) , 
    evalGain(new Vector(0,MEM_POLICY)) , 
    evalGainMask(new Vector(0,MEM_POLICY)) , 
    evalInitNeuron(new Vector(0,MEM_POLICY)) , 
    evalNeurons(new Vector(0,MEM_POLICY)) , 
    relaxedNeurons(new Vector(0,MEM_POLICY)) , 
    defaultRenderer(new BlitzReportNetRenderer()) ,
    mRelaxTau(0)  ,
    mGlobalSigLimit(DBL_MAX)  ,
    mOriginalTau(NULL) 
{

}


bool BlitzNetEvaluator::resetRelax()  {
    if(relaxedNeurons==NULL || relaxedNeurons->size()!=numNeurons){
        relaxedNeurons = new Vector(evalInitNeuron->size()) ; 
    }
    *relaxedNeurons = *evalInitNeuron ; 
    return true ; 
}

bool BlitzNetEvaluator::resetNet(){
    (*evalNeurons) = (*relaxedNeurons) ; 
    return true ; 
}


void BlitzNetEvaluator::resetTrace(int totalPoints,int errorPoints) 
{
    outputVector->resize(numNeurons) ; 
    neuronTrace->resize(totalPoints) ; 
    errorTrace->resize(errorPoints) ; 
    for(int i = 0 ; i < totalPoints ; i++){
        // must do null-check, or else it won't work
        if( (*neuronTrace)[i]==NULL) {
           (*neuronTrace)[i] = new vector<double>(numNeurons) ; 
        }
    }
}


double BlitzNetEvaluator::getGlobalSigLimit() {
	return(mGlobalSigLimit);
}


void BlitzNetEvaluator::setGlobalSigLimit(double _mGlobalSigLimit) {
	mGlobalSigLimit = _mGlobalSigLimit;
	return;
}

/**  The general form of this equation is:  1/(1+exp(-* input)).  
 */
double BlitzNetEvaluator::sigLimit(double input,double limit) 
{
        if(input > fabs(limit)){
            return 1 ; 
        }
        else
        if(input < -fabs(limit)){
            return  0 ; 
        }
        else{
//            return   (1.0 / (1.0 + exp( -input )));
            return  SigLookup::sigLookup( input ) ; 
        }
}

/// Gets the average absolutte difference between the currentPoint and currentPoint-1, returning 0 if currentPoint = 0.
double BlitzNetEvaluator::getAvgLastNeuronChange(int currentPoint) 
{
    // handle the initial case
    if(currentPoint==0){
        return 0 ; 
    }

    return calcNetworkChange( getAllNeuronFinalTrace(currentPoint-1),getAllNeuronFinalTrace(currentPoint)) ; 
}



///  Takes the difference between two vectors of doubles.  Seems like this calculation should be done somewhere else.
double BlitzNetEvaluator::calcNetworkChange(vector<double>* set1,vector<double>* set2) 
{

    double diff = 0 ; 
    if(set1->size()!=set2->size()){
        return -1.0 ; 
    }

    for(int i = 0 ; i < set1->size() ; i++){
//        cout << i << ": (*set1)[i]:" << (*set1)[i] << " (*set2)[i]: " << (*set2)[i] << "=" << fabs( (*set1)[i] - (*set2)[i]) << endl ; 
        diff += fabs( (*set1)[i] - (*set2)[i]) ; 
    }
   
    return diff ; 
}



Vector* BlitzNetEvaluator::sigLimitVector( Vector *v,double limit){
    int vSize = v->size() ; 
    for(int i = 0 ; i < vSize ; i++){
        if((*v)(i)> fabs(limit)){
            (*v)(i) = 1 ; 
        }
        else
        if((*v)(i)< -fabs(limit)){
            (*v)(i) = 0 ; 
        }
        else{
//            (*v)(i) = (1.0 / (1.0 + exp( -(*v)(i) )));
            (*v)(i) = SigLookup::sigLookup( (*v)(i) ) ; 
        }
    }

    return v ; 
}


BlitzNetEvaluator::~BlitzNetEvaluator() 
{
    delete evalWeights ;  
    delete evalWeightMask ;  
    delete evalBias ;  
    delete evalBiasMask ;  
    delete evalTau ;  
    delete evalTauMask ;  
    delete evalGain ;  
    delete evalGainMask ;  
    delete evalInitNeuron ;  
    delete evalNeurons ;  
    delete defaultRenderer ; 
}



/// Relaxes based on the evaluated network value. 
void BlitzNetEvaluator::relaxNet(bool doTrace) 
{
    if(mRelaxTime==0) {
        return ; 
    }


    if(mRelaxTau!=0){
        mOriginalTau = new Vector(evalTau->size()) ; 
        *evalTau = mRelaxTau ; 
    }
//    cout << "---------\nBegin relaxing net\n-----------" << endl ; 

    
    oldLocalDeltaT = localDt; 
    currentRelaxValue = DBL_MAX  ; 
    prevRelaxValue = DBL_MAX ; 
    relaxDelta = fabs(currentRelaxValue-prevRelaxValue) ; 
	relaxCounter = 0 ; 
    relaxPoints = (int) (mRelaxTime/mRelaxDeltaT) ; 
    localDt = mRelaxDeltaT ;


//    relaxCounter = 1 ;
////    currentRelaxValue = evalPoint(mRelaxValueVector,true) ; 
//    currentRelaxValue = evalPoint(mRelaxValueVector,false) ; 
//    relaxDelta = getAvgLastNeuronChange(relaxCounter) ; 
//    ++relaxCounter
    currentRelaxValue = evalPoint(mRelaxValueVector,false) ; 
    relaxDelta = fabs(currentRelaxValue-prevRelaxValue) ; 
    ++relaxCounter ;


//    cout << "relaxDelta: " << relaxDelta << " mRelaxLimit: " << mRelaxLimit << " relaxCounter: " << relaxCounter << " relaxPoints: " << relaxPoints << endl ; 


//    while( relaxDelta > mRelaxLimit &&  relaxCounter < relaxPoints ){
    while(  relaxCounter < relaxPoints ){
        prevRelaxValue = currentRelaxValue ; 
////        currentRelaxValue = evalPoint(mRelaxValueVector,true) ; 
//        currentRelaxValue = evalPoint(mRelaxValueVector,false) ; 
//        relaxDelta = getAvgLastNeuronChange(relaxCounter) ; 
//        ++relaxCounter ; 
        currentRelaxValue = evalPoint(mRelaxValueVector,false) ; 
        relaxDelta = fabs(currentRelaxValue - prevRelaxValue) ; 
        ++relaxCounter ; 
    }
    *relaxedNeurons = *evalNeurons ; 

//    cout << "finishing at " << relaxCounter  << " with relaxDelta: " << relaxDelta <<  endl ; 

    localDt = oldLocalDeltaT ; 
    if(mRelaxTau!=0){
        *evalTau = *mOriginalTau ; 
        mOriginalTau = NULL ; 
    }
//    cout << "---------\nFinished relaxing net, begin eval\n-----------" << endl ; 
}

Vector* BlitzNetEvaluator::getNetworkValues() 
{
    cout << "why network values" << endl ; 
    return evalNeurons ; 
}

void BlitzNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitznetevaluator\">" << endl ;
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
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
