
#include <iostream>
using std::cout ; 
using std::endl ; 


#include "BlitzEulerWrapPerturber.hpp"
#include "BlitzGainNet.hpp"

#include "BlitzGainWrapPerturber.hpp"

BlitzGainWrapPerturber::BlitzGainWrapPerturber(double newWrapValue) : BlitzEulerWrapPerturber(newWrapValue)  
{
    mWrapValue = newWrapValue ; 
}// the first call, calls initSeed() 

void BlitzGainWrapPerturber::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<perturber type=\"blitzgainwrapperturber\">" << endl ;
  addSpacer(s) ; 
  *s << "<taumin value=\"" << TAU_MIN  << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<wrap value=\"" << mWrapValue << "\" />" << endl ;
  // close the XML
  addSpacer(s) ; 
  *s << "</perturber>" << endl ;
}



/**  We want to return a pertubed COPY of the network we call with.  However, we are working on the same memory, so the network ends up being implicitly changed.
 *  
 */
NeuralNetwork* BlitzGainWrapPerturber::perturb(double temp,NeuralNetwork* newNet) 
{
    BlitzGainNet* blitzNet = (BlitzGainNet*) newNet ; 
    Matrix* weights = blitzNet->getWeights()  ; 
    Matrix* weightMask = blitzNet->getWeightMask()  ; 
    Vector* bias = blitzNet->getBias()  ; 
    Vector* biasMask = blitzNet->getBiasMask()  ; 
    Vector* taus = blitzNet->getTau()  ; 
    Vector* tauMask = blitzNet->getTauMask()  ; 
    Vector* initNeurons = blitzNet->getInitNeuron()  ; 
    Vector* initNeuronMask = blitzNet->getInitNeuronMask()  ; 
    Vector* gain = blitzNet->getGain()  ; 
    Vector* gainMask = blitzNet->getGainMask()  ; 

    double dt = blitzNet->getMinDeltaT() ; 
    TAU_MIN = dt*3.0 ; 
    
    int columnCount , rowCount ; 
    int matrixLength = (int) sqrt((double) weights->size()) ;
    
    for(columnCount = 0 ; columnCount < matrixLength; ++columnCount  ) {
        for( rowCount = 0  ;  rowCount < matrixLength ; ++rowCount ) {
            (*weights)(rowCount,columnCount) = checkValue ( (*weights)(rowCount,columnCount) + RNG::normal() * temp * (*weightMask)(rowCount,columnCount) ) ; 
        }
	
        // Perturb the Tau and Bias according to the TauMask and BiasMask
        (*taus)(columnCount) = checkValue ( (*taus)(columnCount) + RNG::normal() * temp * (*tauMask)(columnCount)  ) ; 
        (*bias)(columnCount) = checkValue (  (*bias)(columnCount) + RNG::normal() * temp * (*biasMask)(columnCount) ) ; 

        // handle here, not in evaluator
        if((*taus)(columnCount) < dt*TAU_MIN) {
            (*taus)(columnCount) = dt*TAU_MIN ;  
        }
	
    }

    for(int i = 0  ; (gain!=NULL) && i < gain->size() ; i++){
        (*gain)(i) = checkValue (  (*gain)(i) + RNG::normal() * temp * (*gainMask)(i) ) ; 
    }

    return blitzNet ; 
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
// $Id: BlitzGainWrapPerturber.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

