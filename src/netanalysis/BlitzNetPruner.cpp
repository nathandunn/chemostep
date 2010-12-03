
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "TextEvalTrace.hpp" 
#include "BlitzNet.hpp"  
#include "BlitzNetPruner.hpp"
#include <Note.hpp>

BlitzNetPruner::BlitzNetPruner() 
{
}

void BlitzNetPruner::printActiveNeurons( vector<double>* activities) 
{
    cout << "num activities: " << activities->size() << endl  ; 
    
    // just iterate to see what the active neurons are:
    for(int i = 0 ; i < activities->size() ; i++){
        cout << (*activities)[i] << " " ; 
    }
    cout << endl ; 
}


vector<double>* BlitzNetPruner::getActiveSet( vector<double>* activities,double threshold) 
{
    vector<double>* returnNeurons = new vector<double>() ; 
    returnNeurons->push_back(0) ; 
    for(int i = 1 ; i < activities->size()-1 ; i++){
        if(  fabs( (*activities)[i]) > threshold){
            returnNeurons->push_back(i) ; 
        }
    }
    returnNeurons->push_back(activities->size()-1) ; 
    return returnNeurons ; 
}


/** This method prunes network (except for input and output) based on given activities.  Get thresholds to determine active neurons.  Next, add neurons based on activity. 
 *  
 */
BlitzNet* BlitzNetPruner::prune(BlitzNet* origNet, vector<double>* activities, double threshold) 
{
    vector<double>* activeNeurons = getActiveSet(activities,threshold) ; 
    printActiveNeurons(activeNeurons) ; 
    return strip(origNet,activeNeurons) ; 
}


BlitzNet* BlitzNetPruner::strip( BlitzNet* origNet, vector<double>* activeNeurons) 
{
    int newSize = activeNeurons->size() ; 
    int oldSize = origNet->getNumNeurons() ; 
    origNet->eval() ; 

    vector<double>* avgOutput= (origNet->getEvaluator())->getAllNeuronFinalTrace() ; 

    for(int i = 0 ; i < avgOutput->size() ; i++){
        cout << (*avgOutput)[i] << " " ; 
    }
    cout << endl ; 


    // get old parameters
    Vector *oldBias = origNet->getBias() ; 
    Vector *oldTau = origNet->getTau() ; 
    Vector *oldGain = origNet->getGain() ; 
    Vector *oldVinit = origNet->getInitNeuron() ; 
    Matrix *oldWeight = origNet->getWeights() ; 

    // create new parameters
    Vector *newBias = new Vector(newSize) ;
    Vector *newTau= new Vector(newSize) ;
    Vector *newGain = new Vector(newSize) ;
    Vector *newVinit = new Vector(newSize) ; 
    Matrix *newWeight = new Matrix(newSize,newSize) ;

    (*newBias) = 0 ; 
    (*newTau) = 0 ; 
    (*newGain) = 0 ; 
    (*newVinit) = 0 ; 
    (*newWeight) = 0 ; 


    // create new network
    BlitzNet* returnNet = new BlitzNet(origNet) ; 
    returnNet->setNumNeurons(newSize) ; 
    (returnNet->getNote())->setNote("stripped","yes") ; 

    // the mapping from old to new is:
    //   oldNeuronCounter = activeNeurons[newNeuronCounter] 

    // copy each one over
    int currentOldNeuron, currentNewNeuron ; 
    int newConnectionMapping ; 
    for(currentOldNeuron = 0 , currentNewNeuron = 0  ; currentOldNeuron < oldSize ; currentOldNeuron++){
        if(  currentOldNeuron == (*activeNeurons)[currentNewNeuron] ){
            // copy the old bias, tau, and vinit
            // these are inited to 0, and += because they may be added to from other "cut" neurons prior to receiving their actual bias from the old "alive" neuron, if that makes any sense.
            (*newBias)(currentNewNeuron) += (*oldBias)(currentOldNeuron) ; 
            (*newTau)(currentNewNeuron) += (*oldTau)(currentOldNeuron) ; 
            (*newGain)(currentNewNeuron) += (*oldGain)(currentOldNeuron) ; 
            (*newVinit)(currentNewNeuron) += (*oldVinit)(currentOldNeuron) ; 

            // copy the network connections, only setting outward connections to active neurons
            for(int i = 0 ; i < oldSize ; i++){  // loop thorugh all but the last
                if( connectionIsActive(activeNeurons,i)==true){  
                    (*newWeight)(currentNewNeuron, getNewConnectionMapping(activeNeurons,i) ) = (*oldWeight)( currentOldNeuron,i) ; 
                }
                // else if if the downstream neuron is not active, we don't care
            }
        	++currentNewNeuron ; 
        }
        else{
            // copy average network activity * downstream conections = downstream bias
            // but only for currentOldNeuron
            for(int i = 0 ; i < oldSize; i++){
                if( connectionIsActive(activeNeurons,i)==true){  
                     (*newBias)(getNewConnectionMapping(activeNeurons,i)) += ((*oldWeight) (currentOldNeuron,i) )  *  (*avgOutput)[currentOldNeuron]  ;    
                }
                // else . . . don't need to distrubte bias to inactive neurons
            }
        }
    }

   
    returnNet->setBias(newBias) ; 
    returnNet->setTau(newTau) ; 
    returnNet->setGain(newGain) ; 
    returnNet->setInitNeuron(newVinit) ; 
    returnNet->setWeights(newWeight) ; 
    
    return returnNet ; 
}

/// Returns true if the neuron is active in the stripped network.
bool BlitzNetPruner::connectionIsActive(vector<double>* activeNeurons,int testNeuron) 
{
    vector<double>::iterator iter = activeNeurons->begin() ; 
    while( iter != activeNeurons->end() ){
        if( (*iter)==testNeuron){
            return true ; 
        }
        ++iter ; 
    }
    return false ; 
}

/// Returns the neuron number of the neuron in the stripped network or -1.
int BlitzNetPruner::getNewConnectionMapping(vector<double>* activeNeurons,int testNeuron) 
{
    vector<double>::iterator iter = activeNeurons->begin() ; 
    int counter = 0 ; 
    while( iter != activeNeurons->end() ){
        if( (*iter)==testNeuron){
            return counter ; 
        }
        ++iter ; 
        ++counter ; 
    }
    return -1 ; 
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
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

