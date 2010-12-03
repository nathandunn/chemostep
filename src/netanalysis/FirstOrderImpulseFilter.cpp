#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 




#include "Peak.hpp"
#include "FirstOrderImpulseFilter.hpp"

#include "ImpulseSignal.hpp"

FirstOrderImpulseFilter::FirstOrderImpulseFilter() : FirstOrderFilter()
,mAmplitudeFirstPeak(NULL)
,mTimeToFirstPeak(NULL)
,mBaseline(NULL)
,mSteadyState(NULL)
{
}

int FirstOrderImpulseFilter::getImpulseTime() 
{
    return mImpulseAt ; 
}


string FirstOrderImpulseFilter::getType() 
{
    return "FirstOrderImpulseFilter" ; 
}


FirstOrderImpulseFilter::FirstOrderImpulseFilter(DataFilter* newDataFilter) 
{
    setFilter(newDataFilter) ; 
}

/// Returns time it takes to get the first peak. 
double FirstOrderImpulseFilter::getTimeToFirstPeak(int labelCounter) 
{
    if(mTimeToFirstPeak==NULL){
        return -1 ; 
    }else{
        return (*mTimeToFirstPeak)(labelCounter) ; 
    }
}

double FirstOrderImpulseFilter::getBaseline(int labelCounter) 
{
    return (*mBaseline)(labelCounter) ; 
}

Peak FirstOrderImpulseFilter::getPeakPoint(int startingPoint,int neuronCounter) 
{
    double currentValue, prevValue ,  deltaValue ; 
    int sign  ; 

    // The first neuron count sees the input impulse first. 
    if(neuronCounter>0){
        ++startingPoint ; 
    }
    prevValue = (*mRawSignal)(startingPoint-1,neuronCounter) ; 
    currentValue = (*mRawSignal)(startingPoint,neuronCounter) ; 
    deltaValue = currentValue - prevValue ; 
    if(deltaValue<0){
        sign = -1; 
    }
    else{
        sign = 1; 
    }
//    cout << "counter: " << neuronCounter << " mRawSignal->rows(): " << mRawSignal->rows() << endl ; 
//    cout << "neuronCounter: " << neuronCounter << "  prevValue: " << prevValue << " currentValue: " << currentValue <<  "  deltaValue: " <<  deltaValue << " sign: " <<  sign << endl ; 


    double mDiffThresh = 0.00001 ; 
    int timeCounter = startingPoint ; 
    
     while (timeCounter  < mRawSignal->rows()  &&  ( sign* (deltaValue)> mDiffThresh ) ){
         // calculate sign for the PREVIOUS value
        if(deltaValue<0){
            sign = -1; 
        }
        else{
            sign = 1; 
        }
//        cout << "timeCounter< mRawSignal->rows(): " << (timeCounter < mRawSignal->rows()) << endl ; 
//        cout << "sign*(currentValue-prevValue): " << sign*(currentValue-prevValue) << endl ; 
//        cout << "PRE-neuronCounter: " << neuronCounter << "  timeCounter: " << timeCounter << " deltaValue: " << deltaValue << " sign: " << sign << endl ; 
        prevValue = currentValue ; 
        ++timeCounter ; 
        currentValue = (*mRawSignal)(timeCounter,neuronCounter) ; 
        deltaValue = currentValue - prevValue ; 
//        cout << "POST-neuronCounter: " << neuronCounter << "  timeCounter: " << timeCounter << " deltaValue: " << deltaValue << " sign: " << sign << endl ; 
    }

//        cout << "FIANL-neuronCounter: " << neuronCounter << "  timeCounter: " << timeCounter << " deltaValue: " << deltaValue << " sign: " << sign << endl ;

      return Peak( timeCounter-1,  prevValue - (*mSteadyState)(neuronCounter) )    ;
}




/**  This method sets mAmplitude, mBaseline, mSteadyState, mTimeToSteadyState.
 *
 */
// todo: HERE
DataFilter* FirstOrderImpulseFilter::extractData(RawSignal* newSignal) 
{
    mRawSignal = new Matrix(  *(newSignal->getData()) ) ; 
    mNumNeurons = mRawSignal->columns() ; 
    mTimePoints = mRawSignal->rows() ; 
    cout << "mTimePoints: " << mTimePoints << endl ; 
    cout << "mTimePoints signal: " << (*mRawSignal)(mTimePoints-1,0) << endl ; 
    mImpulseAt = (int) ((ImpulseSignal*) newSignal)->getImpulseTime() ; 

    
    // init vectors
    mAmplitudeFirstPeak = new Vector(mNumNeurons) ; 
    mTimeToFirstPeak = new Vector(mNumNeurons) ; 
    mBaseline = new Vector(mNumNeurons) ; 
    mSteadyState = new Vector(mNumNeurons) ; 
//    mTimeTo5PerSteadyState = new Vector(mNumNeurons) ; 
    mFirstOrderAmplitude = new Vector(mNumNeurons) ; 
    mFirstOrderTau = new Vector(mNumNeurons) ; 
    Peak peakPair(0,0.0) ; 

    // calculate our values
    for(int neuronCounter = 0 ; neuronCounter < mNumNeurons ; neuronCounter++){
        (*mBaseline)(neuronCounter) = (*mRawSignal)(mImpulseAt-1,neuronCounter) ; 
        (*mSteadyState)(neuronCounter) = (*mRawSignal)(mTimePoints-1,neuronCounter) ; 
//        getFirstPeak(  mImpulseAt ,neuronCounter ) ;  // sets mTimeToFirstPeak and mAmplitudeFirstPeak
        peakPair = getPeakPoint(mImpulseAt,neuronCounter) ;
        (*mTimeToFirstPeak)(neuronCounter) = peakPair.getPeakTime() - mImpulseAt ;
        (*mAmplitudeFirstPeak)(neuronCounter) = peakPair.getPeakValue() ; 
        getDecay(neuronCounter) ; // specifies mFirstOrderTau 
    }


    *mFirstOrderAmplitude = (*mAmplitudeFirstPeak)  * (*mFirstOrderTau)  ; 

    // check our values
    cout << "baseline:  " << *mBaseline <<  endl ; 
    cout << "steadystate:  " << *mSteadyState <<  endl ; 
    cout << "amplitude first peak:  " << *mAmplitudeFirstPeak <<  endl ; 
    cout << "time to first peak:  " << *mTimeToFirstPeak <<  endl ; 
    cout << "firstordertau:  " << *mFirstOrderTau<<  endl ; 
    cout << "firstorderampltidue:  " << *mFirstOrderAmplitude<<  endl ; 

    
    return this ; 
}

/// Populate variable sized vector from the first-peak until below the threshold value  The thresholds will be variable sized.  The tau is the first peak to go below 0.368 (exp(-1)). The value is y(t)=M/tau * exp(-t/tau)
bool FirstOrderImpulseFilter::getDecay( int neuronNum) 
{
    vector<double>* decayVector = new vector<double>() ; 
    double decayThreshold = fabs( exp(-1) * (*mAmplitudeFirstPeak)(neuronNum)) ;
    double baseline =  (*mBaseline)(neuronNum) ;
    bool isFinished= false ; 

    double currentValue , prevValue ; 
    double avgTau ; 
    int startingPoint =  (int) (*mTimeToFirstPeak)(neuronNum) + mImpulseAt  ;

    for(int i = startingPoint ; i < mTimePoints &&  isFinished!=true ; i++ ){
        //  if( difference from baseline in value at i for neuron is below threshold ){ keep going }  else {  isFinished= true ; tau = time-avg ; }

//    cout << "(*mRawSignal)(i,neuronNum): " << (*mRawSignal)(neuronNum,i) << endl ; 
//    cout << "(*mBaseline)(i,neuronNum): " << (*mBaseline)(neuronNum) << endl ; 
        prevValue = currentValue ; 
        currentValue = fabs( (*mRawSignal)(i,neuronNum) - (*mBaseline)(neuronNum)  ) ; 
        if(currentValue < decayThreshold){
            isFinished = true ; 
//            (*mFirstOrderTau)(neuronNum) = (double) i - (*mTimeToFirstPeak)(neuronNum) ;  // should take avg, but lazy right now.
            avgTau = (decayThreshold - prevValue) / (currentValue - prevValue)  ; 
//            cout << "decayThreshold: " << decayThreshold << " currentValue: " << currentValue << " prevValue: " << prevValue << " avgTau: " << avgTau << endl ; 
            (*mFirstOrderTau)(neuronNum) = (double) avgTau + (double) (i-1) -(*mTimeToFirstPeak)(neuronNum) - mImpulseAt   ; 
//            cout << "i: " << i << " mTimeToFirstPeak: " << (*mTimeToFirstPeak)(neuronNum) << " avgTau: " << avgTau << endl ; 
        }
    }


    return isFinished ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


