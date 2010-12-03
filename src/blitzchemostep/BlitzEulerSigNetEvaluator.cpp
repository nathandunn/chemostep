/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzEulerLiveNetEvaluator.hpp" 

#include "BlitzEulerSigNetEvaluator.hpp"

BlitzEulerSigNetEvaluator::BlitzEulerSigNetEvaluator(double newMinDeltaT,double newOutputSigmoid,NeuralNetwork* refNet) : BlitzEulerLiveNetEvaluator(newMinDeltaT,newOutputSigmoid,refNet)
{
}

double BlitzEulerSigNetEvaluator::fixOutput(double outputNeuron) 
{
    return  outputNeuron ; 
}



void BlitzEulerSigNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzeulersignetevaluator\">" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\"" << mOutputSigmoid << "\"/>" << endl ; 
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}




const float BlitzEulerSigNetEvaluator::INVS_RAND_MAX = 1.0 / (float) RAND_MAX ; 


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

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


