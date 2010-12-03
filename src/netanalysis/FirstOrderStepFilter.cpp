#include <iostream>
using std::cout ; 
using std::endl ; 

#include "FirstOrderStepFilter.hpp"

#include "StepSignal.hpp"

FirstOrderStepFilter::FirstOrderStepFilter() : FirstOrderFilter()
,mAmplitudeFirstPeak(NULL)
,mTimeToFirstPeak(NULL)
,mBaseline(NULL)
,mSteadyState(NULL)
,mTimeTo5PerSteadyState(NULL)
{
}

/**  This method sets mAmplitude, mBaseline, mSteadyState, mTimeToSteadyState.
 *
 */
// todo: HERE
DataFilter* FirstOrderStepFilter::extractData(StepSignal* newSignal) 
{
    mRawSignal = new Matrix(  *(newSignal->getData()) ) ; 
    mNumNeurons = mRawSignal->columns() ; 
    mTimePoints = mRawSignal->rows() ; 
    cout << "mTimePoints: " << mTimePoints << endl ; 
    cout << "mTimePoints signal: " << (*mRawSignal)(mTimePoints-1,0) << endl ; 
    mStepAt = (int) newSignal->getStepTime() ; 

    
    // init vectors
    mAmplitudeFirstPeak = new Vector(mNumNeurons) ; 
    mTimeToFirstPeak = new Vector(mNumNeurons) ; 
    mBaseline = new Vector(mNumNeurons) ; 
    mSteadyState = new Vector(mNumNeurons) ; 
    mTimeTo5PerSteadyState = new Vector(mNumNeurons) ; 

    cout << "mStepAt: " << mStepAt << endl ; 

    // calculate our values
    for(int neuronCounter = 0 ; neuronCounter < mNumNeurons ; neuronCounter++){
        (*mBaseline)(neuronCounter) = (*mRawSignal)(mStepAt-1,neuronCounter) ; 
        (*mSteadyState)(neuronCounter) = (*mRawSignal)(mTimePoints-1,neuronCounter) ; 
        getFirstPeak(  mStepAt ,neuronCounter ) ;  // sets mTimeToFirstPeak and mAmplitudeFirstPeak
//        (*mTimeTo5PerSteadyState)(neuronCounter) = (*mRawSignal)(

    }

    // check our values
    cout << "baseline:  " << *mBaseline <<  endl ; 
    cout << "steadystate:  " << *mSteadyState <<  endl ; 
    cout << "amplitude first peak:  " << *mAmplitudeFirstPeak <<  endl ; 
    cout << "time to first peak:  " << *mTimeToFirstPeak <<  endl ; 
    cout << "time to 5 per steadystate:  " << *mTimeTo5PerSteadyState <<  endl ; 

    
    return this ; 
}

/**  Return a positive or negative peak relative to the original baseline.
 *
 *
 */
bool FirstOrderStepFilter::getFirstPeak( int stepAt,int neuronCounter) 
{
    double currentValue, prevValue ,  deltaValue ; 
    int sign  ; 
    cout <<"A" << endl ; 
    prevValue = (*mRawSignal)(stepAt,neuronCounter) ; 
    cout <<"B" << endl ; 
    currentValue = (*mRawSignal)(stepAt+1,neuronCounter) ; 
    cout <<"C" << endl ; 
    if(deltaValue<0){
        sign = -1; 
    }
    else{
        sign = 1; 
    }


    int timeCounter = stepAt+1 ; 
    if(neuronCounter==0){  // ignore any blips from the step on the input neuron
        ++timeCounter ; 
    }
    cout << "mRawSignal->rows(): " << mRawSignal->rows() << endl ; 
    cout << "currentValue-prevValue: " <<  currentValue-prevValue << endl ; 
    cout << "sign: " <<  sign << endl ; 

    double mDiffThresh = 0.00001 ; 
    
    for( ; timeCounter  < mRawSignal->rows()  &&  ( sign* (currentValue-prevValue)> mDiffThresh ) ;  timeCounter++){
        cout << "timeCounter< mRawSignal->rows(): " << (timeCounter < mRawSignal->rows()) << endl ; 
        cout << "sign*(currentValue-prevValue): " << sign*(currentValue-prevValue) << endl ; 
        prevValue = currentValue ; 
        currentValue = (*mRawSignal)(timeCounter,neuronCounter) ; 
        cout << "neuronCounter: " << neuronCounter << "  timeCounter: " << timeCounter << " deltaValue: " << currentValue- prevValue << endl ; 
    }

    (*mAmplitudeFirstPeak)(neuronCounter) = prevValue - (*mSteadyState)(neuronCounter) ; 
    (*mTimeToFirstPeak)(neuronCounter) = timeCounter - 1 ;
    
    
    
    return true  ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


