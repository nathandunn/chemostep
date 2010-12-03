#ifndef BLITZMIDPOINTLIVENETEVALUATOR_HPP_
#  define BLITZMIDPOINTLIVENETEVALUATOR_HPP_

#include "BlitzMidPointNetEvaluator.hpp"

/**
 *  This class is the same
 *
 */ 
class BlitzMidPointLiveNetEvaluator : public BlitzMidPointNetEvaluator {

public:
    BlitzMidPointLiveNetEvaluator(double newMinDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL) ; 
    virtual double fixOutput(double outputNeuron) ; /// Fixes the output neuron. 
    virtual void toXML(ostream *s) ;

} ;

#endif /* ifndef BLITZMIDPOINTLIVENETEVALUATOR_H */
// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


