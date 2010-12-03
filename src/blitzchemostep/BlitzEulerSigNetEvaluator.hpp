#ifndef BLITZEULERSIGNETEVALUATOR_HPP_
#  define BLITZEULERSIGNETEVALUATOR_HPP_

#include "BlitzEulerLiveNetEvaluator.hpp" 

class BlitzEulerSigNetEvaluator : public BlitzEulerLiveNetEvaluator {

public:
    BlitzEulerSigNetEvaluator(double newMinDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL) ; 
    virtual double fixOutput(double outputNeuron) ; /// Fixes the output neuron. 
    virtual void toXML(ostream *s) ;
   
    const static float INVS_RAND_MAX ; 

} ;

#endif /* ifndef BLITZEULERSIGNETEVALUATOR_H */
// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


