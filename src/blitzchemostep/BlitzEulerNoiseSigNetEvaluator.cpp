/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzEulerNoiseLiveNetEvaluator.hpp" 

#include "BlitzEulerNoiseSigNetEvaluator.hpp"

BlitzEulerNoiseSigNetEvaluator::BlitzEulerNoiseSigNetEvaluator(double newMinDeltaT,double newOutputSigmoid,NeuralNetwork* refNet,double newInputNoise,double newOutputNoise) : BlitzEulerNoiseLiveNetEvaluator(newMinDeltaT,newOutputSigmoid,refNet,newInputNoise,newOutputNoise)
{
}

double BlitzEulerNoiseSigNetEvaluator::fixOutput(double outputNeuron) 
{
    return  outputNeuron ; 
}



void BlitzEulerNoiseSigNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzeulersignetevaluator\">" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\"" << mOutputSigmoid << "\"/>" << endl ; 
  addSpacer(s) ; 
  *s << "<inputnoise value=\"" << mInputNoise << "\"/>" << endl ; 
  addSpacer(s) ; 
  *s << "<outputnoise value=\"" << mOutputNoise << "\"/>" << endl ; 
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}




const float BlitzEulerNoiseSigNetEvaluator::INVS_RAND_MAX = 1.0 / (float) RAND_MAX ; 


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


