#ifndef FIRSTORDERFILTER_HPP_
#  define FIRSTORDERFILTER_HPP_

#include "DataFilter.hpp"
#include "RawSignal.hpp"

/** This is a decorator class for first-order models, as well as any variables they may contain.
 *
 */
class FirstOrderFilter : public DataFilter{

public:
    FirstOrderFilter() ; 
    virtual double getAmplitude(int signalNumber) ; 
    virtual double getTau(int signalNumber) ; 

protected:
    Vector* mFirstOrderAmplitude ; 
    Vector* mFirstOrderTau ; 

} ;

#endif /* ifndef FIRSTORDERFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


