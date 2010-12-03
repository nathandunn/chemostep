#ifndef SECONDORDERFILTER_HPP_
#  define SECONDORDERFILTER_HPP_

#include "DataFilter.hpp"
#include "RawSignal.hpp"

/** This is a decorator class for first-order models, as well as any variables they may contain.
 *
 */
class SecondOrderFilter : public DataFilter{

public:
    SecondOrderFilter() ; 
    virtual double getAmplitude(int signalNumber) ; 
    virtual double getDecay(int signalNumber) ; 
    virtual double getPeriod(int signalNumber) ; 
    virtual double getPhaseShift(int signalNumber) ; 

protected:
    Vector* mSecondOrderDecay ; 
    Vector* mSecondOrderAmplitude ; 
    Vector* mSecondOrderPeriod ; 
    Vector* mSecondOrderPhaseShift; 

} ;

#endif /* ifndef SECONDORDERFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


