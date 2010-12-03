/*
 * $Id: BlitzEulerPerturber.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzEulerPerturber.hpp"
#include "BlitzNet.hpp"
#include "RNG.hpp"

/**  We want to return a pertubed COPY of the network we call with.
 *  
 */
NeuralNetwork* BlitzEulerPerturber::perturb(double temp,NeuralNetwork* newNet) 
{
    BlitzNet* blitzNet = (BlitzNet*) newNet ; 
    Matrix* weights = blitzNet->getWeights()  ; 
    Matrix* weightMask = blitzNet->getWeightMask()  ; 
    Vector* bias = blitzNet->getBias()  ; 
    Vector* biasMask = blitzNet->getBiasMask()  ; 
    Vector* taus = blitzNet->getTau()  ; 
    Vector* tauMask = blitzNet->getTauMask()  ; 
    Vector* initNeurons = blitzNet->getInitNeuron()  ; 
    Vector* initNeuronMask = blitzNet->getInitNeuronMask()  ; 

    double dt = blitzNet->getMinDeltaT() ; 
    TAU_MIN = dt*3.0 ; 
    
    int columnCount , rowCount ; 
    int matrixLength = (int) sqrt((double) weights->size()) ;
    
    for(columnCount = 0 ; columnCount < matrixLength; ++columnCount  ) {
	for( rowCount = 0  ;  rowCount < matrixLength ; ++rowCount ) {
	    double randomNum = RNG::normal() ;
	    (*weights)(rowCount,columnCount) += randomNum * temp * (*weightMask)(rowCount,columnCount) ; 
	}
	
	// Perturb the Tau and Bias according to the TauMask and BiasMask
	(*taus)(columnCount) += RNG::normal() * temp * (*tauMask)(columnCount); 
	(*bias)(columnCount) += RNG::normal() * temp * (*biasMask)(columnCount); 
//      (*initNeurons)(columnCount) += RNG::uniform() * temp * (*initNeuronMask)(columnCount);  // don't want to deal with these, as the range is limited to between 0 and 1
	
	// handle here, not in evaluator
	if((*taus)(columnCount) < dt*TAU_MIN) {
	    (*taus)(columnCount) = dt*TAU_MIN ;  
	}
	
    }
    return blitzNet ; 
}

void BlitzEulerPerturber::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<perturber type=\"blitzeulerperturber\">" << endl ;
  addSpacer(s,-1) ; 
  *s << "<taumin value=\"" << TAU_MIN  << "\" />" << endl ;
  // close the XML
  addSpacer(s) ; 
  *s << "</perturber>" << endl ;

}



double BlitzEulerPerturber::TAU_MIN = 0 ; 


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
// FILE: "/Users/nathandunn/svn/chemotrunk/src/blitzchemostep/BlitzEulerPerturber.cpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 12:43:51 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzEulerPerturber.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

