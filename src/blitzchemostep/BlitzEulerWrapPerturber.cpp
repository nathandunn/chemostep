
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzEulerPerturber.hpp"
#include "BlitzNet.hpp"

#include "BlitzEulerWrapPerturber.hpp"

BlitzEulerWrapPerturber::BlitzEulerWrapPerturber(double newWrapValue) : BlitzEulerPerturber()  
{
    mWrapValue = newWrapValue ; 
}// the first call, calls initSeed() 

void BlitzEulerWrapPerturber::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<perturber type=\"blitzeulerwrapperturber\">" << endl ;
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
NeuralNetwork* BlitzEulerWrapPerturber::perturb(double temp,NeuralNetwork* newNet) 
{
    BlitzNet* blitzNet = (BlitzNet*) newNet ; 
    Matrix* weights = blitzNet->getWeights()  ; 
    Matrix* weightMask = blitzNet->getWeightMask()  ; 
    Vector* bias = blitzNet->getBias()  ; 
    Vector* biasMask = blitzNet->getBiasMask()  ; 
    Vector* taus = blitzNet->getTau()  ; 
    Vector* tauMask = blitzNet->getTauMask()  ; 
    Vector* gain = blitzNet->getGain()  ; 
    Vector* gainMask = blitzNet->getGainMask()  ; 
    Vector* initNeurons = blitzNet->getInitNeuron()  ; 
    Vector* initNeuronMask = blitzNet->getInitNeuronMask()  ; 

    double dt = blitzNet->getMinDeltaT() ; 
    TAU_MIN = dt*3.0 ; 
    
    int columnCount , rowCount ; 
    int matrixLength = (int) sqrt((double) weights->size()) ;
    
    for(columnCount = 0 ; columnCount < matrixLength; ++columnCount  ) {
        for( rowCount = 0  ;  rowCount < matrixLength ; ++rowCount ) {
            double randomNum = RNG::normal() ;
            (*weights)(rowCount,columnCount) = checkValue ( (*weights)(rowCount,columnCount) + randomNum * temp * (*weightMask)(rowCount,columnCount) ) ; 
        }
	
        // Perturb the Tau and Bias according to the TauMask and BiasMask
        (*taus)(columnCount) = checkValue ( (*taus)(columnCount) + RNG::normal() * temp * (*tauMask)(columnCount)  ) ; 
        (*bias)(columnCount) = checkValue (  (*bias)(columnCount) + RNG::normal() * temp * (*biasMask)(columnCount) ) ; 
        (*gain)(columnCount) = checkValue (  (*gain)(columnCount) + RNG::normal() * temp * (*gainMask)(columnCount) ) ; 

        // handle here, not in evaluator
        if((*taus)(columnCount) < dt*TAU_MIN) {
            (*taus)(columnCount) = dt*TAU_MIN ;  
        }
	
    }

    return blitzNet ; 
}


double BlitzEulerWrapPerturber::checkValue(double newCheckValue) 
{
        if( newCheckValue > mWrapValue){
            newCheckValue =  newCheckValue - 2.0 *mWrapValue ;   // wrap to the negative side
        }
        else 
        if( newCheckValue < -mWrapValue){
            newCheckValue =  newCheckValue + 2.0 *mWrapValue ;   // wrap to the negative side
        }
        return newCheckValue ; 
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
// $Id: BlitzEulerWrapPerturber.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

