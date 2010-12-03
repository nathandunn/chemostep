#ifndef FIRSTORDERIMPULSEFILTER_HPP_
#  define FIRSTORDERIMPULSEFILTER_HPP_

#include "FirstOrderFilter.hpp"

#include <vector>
using std::vector ; 

class ImpulseSignal ; 
class Peak ; 

class FirstOrderImpulseFilter : public FirstOrderFilter {

public:
    FirstOrderImpulseFilter() ; 
    FirstOrderImpulseFilter(DataFilter* newDataFilter) ; 
    virtual DataFilter* extractData(RawSignal *newSignal) ; 
    virtual string getType() ; 
    virtual double getTimeToFirstPeak(int labelCounter) ; 
    virtual double getBaseline(int labelCounter) ; 
    virtual int getImpulseTime() ; 


protected:
    virtual Peak getPeakPoint(int startingPoint,int neuronCounter) ; 
    virtual bool getDecay( int neuronNum) ; 
    // input impulse values
    int mImpulseAt ; 
    int mTimePoints ; 
    

    // output value
    int mNumNeurons ; 
    Vector*  mAmplitudeFirstPeak ; 
    Vector*  mTimeToFirstPeak; 
    Vector*  mBaseline ; 
    Vector*  mSteadyState ; 
    

} ;

#endif /* ifndef FIRSTORDERIMPULSEFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


