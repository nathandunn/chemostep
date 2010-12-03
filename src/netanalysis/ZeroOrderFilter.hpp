#ifndef ZEROORDERFILTER_HPP_
#  define ZEROORDERFILTER_HPP_

#include "DataFilter.hpp"
#include "RawSignal.hpp"

/** This is a decorator class for zero-order models, as well as any variables they may contain.
 *
 */
class ZeroOrderFilter : public DataFilter{

public:
    ZeroOrderFilter() ; 
    virtual double getBaseline(int signalNumber) ; 

protected:
    Vector* mZeroOrderBaseline ; 

} ;

#endif /* ifndef ZEROORDERFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


