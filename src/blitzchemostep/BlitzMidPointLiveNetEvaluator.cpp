#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzMidPointLiveNetEvaluator.hpp"
#include "BlitzMidPointNetEvaluator.hpp"

BlitzMidPointLiveNetEvaluator::BlitzMidPointLiveNetEvaluator(double newMinDeltaT,double newOutputSigmoid,NeuralNetwork* refNet) : BlitzMidPointNetEvaluator(newMinDeltaT,newOutputSigmoid,refNet)
{
}

double BlitzMidPointLiveNetEvaluator::fixOutput(double outputNeuron) 
{
    if( (rand()/(float) RAND_MAX) > outputNeuron ){
        return 0.0 ; 
    }
    else{
        return  1.0 ; 
    }
}


void BlitzMidPointLiveNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzmidpointliveneteval\">" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\"" << mOutputSigmoid << "\"/>" << endl ; 
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



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


