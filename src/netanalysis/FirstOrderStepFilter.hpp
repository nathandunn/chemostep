#ifndef FIRSTORDERSTEPFILTER_HPP_
#  define FIRSTORDERSTEPFILTER_HPP_

#include "FirstOrderFilter.hpp"

#include <vector>
using std::vector ; 

class StepSignal ; 

class FirstOrderStepFilter : public FirstOrderFilter {

public:
    FirstOrderStepFilter() ; 
    virtual DataFilter* extractData(StepSignal *newSignal) ; 


protected:
    virtual bool getFirstPeak( int stepAt,int neuronNum) ; 
    // input step values
    int mStepAt ; 
    int mTimePoints ; 
    

    // output value
    int mNumNeurons ; 
    Vector*  mAmplitudeFirstPeak ; 
    Vector*  mTimeToFirstPeak; 
    Vector*  mBaseline ; 
    Vector*  mSteadyState ; 
    Vector*  mTimeTo5PerSteadyState ; 
    

} ;

#endif /* ifndef FIRSTORDERstepFILTER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


