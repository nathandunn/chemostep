#ifndef SECONDORDERIMPULSEFILTER_HPP_
#  define SECONDORDERIMPULSEFILTER_HPP_

#include "SecondOrderFilter.hpp"

#include <vector>
using std::vector ; 
using std::pair ; 


class ImpulseSignal ; 
class Peak ; 

class SecondOrderImpulseFilter : public SecondOrderFilter {

public:
    SecondOrderImpulseFilter() ; 
    SecondOrderImpulseFilter(DataFilter* newDataFilter) ; 
    virtual DataFilter* extractData(RawSignal *newSignal) ; 
    virtual string getType() ; 
    virtual double getTimeToFirstPeak(int labelCounter) ; 
    virtual double getBaseline(int labelCounter) ; 
    virtual int getImpulseTime() ; 


protected:
    virtual Peak getPeakPoint(int startingPoint,int neuronCounter) ; 
    // input impulse values
    int mImpulseAt ; 
    int mTimePoints ; 
    

    // output value
    int mNumNeurons ; 
    Vector*  mAmplitudeFirstPeak ; 
    Vector*  mTimeToFirstPeak; 
    Vector*  mAmplitudeSecondPeak; 
    Vector*  mTimeToSecondPeak; 
    Vector*  mBaseline ; 
    Vector*  mSteadyState ; 

    

} ;

#endif /* ifndef SECONDORDERIMPULSEFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


