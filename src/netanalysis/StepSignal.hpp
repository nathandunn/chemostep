

#ifndef STEPSIGNAL_HPP_
#  define STEPSIGNAL_HPP_

#include <blitzdefs.hpp>

/**  Extends RawSignal into an StepSignal, which has an impulse point, baseline, and amplitude.
 *
 */

#include "RawSignal.hpp"

class StepSignal: public RawSignal{

public:
    StepSignal(StepSignal* newSignal) ; 
    StepSignal(double newAmplitude,double newBaseline,double newStepTime, int numNeurons=0,int numTimePoints=0,double newTimeStep=1.0) ; 
    StepSignal(StlSignal* newSignal, double newAmplitude,double newBaseline,double newStepTime,double newTimeStep=1.0) ; 
    virtual double getAmplitude() ; 
    virtual double getBaseline() ; 
    virtual double getStepTime() ; 


protected:
    double mAmplitude ; 
    double mBaseline ; 
    double mStepTime ;  /// This is the discrete time-point
    
   

} ;

#endif /* ifndef RAWSIGNAL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

