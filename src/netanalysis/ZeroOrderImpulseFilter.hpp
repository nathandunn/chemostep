#ifndef ZEROORDERIMPULSEFILTER_HPP_
#  define ZEROORDERIMPULSEFILTER_HPP_

#include "ZeroOrderFilter.hpp"

#include <vector>
using std::vector ; 

class ImpulseSignal ; 
class Peak ; 

class ZeroOrderImpulseFilter : public ZeroOrderFilter {

public:
    ZeroOrderImpulseFilter()   ; 
    ZeroOrderImpulseFilter(DataFilter* newDataFilter) ; 
    virtual DataFilter* extractData(RawSignal *newSignal) ; 
    virtual string getType() ; 
    virtual double getBaseline(int labelCounter) ; 
    virtual int getImpulseTime() ; 


protected:
    // input impulse values
    int mImpulseAt ; 
    int mTimePoints ; 
    

    // output value
    int mNumNeurons ; 
    Vector*  mBaseline ; 
    

} ;

#endif /* ifndef ZEROORDERIMPULSEFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


