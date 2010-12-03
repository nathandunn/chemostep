#ifndef BLITZEULERNOISESIGNETEVALUATOR_HPP_
#  define BLITZEULERNOISESIGNETEVALUATOR_HPP_

#include "BlitzEulerNoiseLiveNetEvaluator.hpp" 

class BlitzEulerNoiseSigNetEvaluator : public BlitzEulerNoiseLiveNetEvaluator {

public:
    BlitzEulerNoiseSigNetEvaluator(double newMinDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL,double newInputNoise=0.0,double newOutputNoise=0.0) ; 
    virtual double fixOutput(double outputNeuron) ; /// Fixes the output neuron. 
    virtual void toXML(ostream *s) ;
   
    const static float INVS_RAND_MAX ; 

} ;

#endif /* ifndef BLITZEULERSIGNETEVALUATOR_H */
// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


