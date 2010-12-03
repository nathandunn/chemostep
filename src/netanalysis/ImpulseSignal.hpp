

#ifndef IMPULSESIGNAL_HPP_
#  define IMPULSESIGNAL_HPP_

#include <blitzdefs.hpp>

/**  Extends RawSignal into an ImpulseSignal, which has an impulse point, baseline, and amplitude.
 *
 */

#include "RawSignal.hpp"

class ImpulseSignal: public RawSignal{

public:
    ImpulseSignal(ImpulseSignal* newSignal) ; 
    ImpulseSignal(double newAmplitude,double newBaseline,double newImpulseTime, int numNeurons=0,int numTimePoints=0,double newTimeStep=1.0) ; 
    ImpulseSignal(StlSignal* newSignal, double newAmplitude,double newBaseline,double newImpulseTime,double newTimeStep=1.0) ; 
    virtual double getAmplitude() ; 
    virtual double getBaseline() ; 
    virtual double getImpulseTime() ; 


protected:
    double mAmplitude ; 
    double mBaseline ; 
    double mImpulseTime ;  /// This is the discrete time-point
    
   

} ;

#endif /* ifndef RAWSIGNAL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

