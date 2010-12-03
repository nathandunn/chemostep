#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 
using std::pair ; 


#include <blitzdefs.hpp>
#include "Peak.hpp"

#include "SecondOrderImpulseFilter.hpp"

#include "ImpulseSignal.hpp"

//  \todo  Fix amplitude calculations
/// \todo  Fix/verify 'getSecondPeak'

SecondOrderImpulseFilter::SecondOrderImpulseFilter() : SecondOrderFilter()
,mAmplitudeFirstPeak(NULL)
,mTimeToFirstPeak(NULL)
,mBaseline(NULL)
,mSteadyState(NULL)
{
}

string SecondOrderImpulseFilter::getType() 
{
    return "SecondOrderImpulseFilter" ; 
}


SecondOrderImpulseFilter::SecondOrderImpulseFilter(DataFilter* newDataFilter) 
{
    setFilter(newDataFilter) ; 
}

/// Returns time it takes to get the first peak. 
double SecondOrderImpulseFilter::getTimeToFirstPeak(int labelCounter) 
{
    if(mTimeToFirstPeak==NULL){
        return -1 ; 
    }else{
        return (*mTimeToFirstPeak)(labelCounter) ; 
    }
}

double SecondOrderImpulseFilter::getBaseline(int labelCounter) 
{
    return (*mBaseline)(labelCounter) ; 
}





/**  This method sets mAmplitude, mBaseline, mSteadyState, mTimeToSteadyState.
 *
 */
// todo: HERE
DataFilter* SecondOrderImpulseFilter::extractData(RawSignal* newSignal) 
{
    mRawSignal = new Matrix(  *(newSignal->getData()) ) ; 
    mNumNeurons = mRawSignal->columns() ; 
    mTimePoints = mRawSignal->rows() ; 
    cout << "mTimePoints: " << mTimePoints << endl ; 
    cout << "mTimePoints signal: " << (*mRawSignal)(mTimePoints-1,0) << endl ; 
    mImpulseAt = (int) ((ImpulseSignal*) newSignal)->getImpulseTime() ; 

    
    // init vectors
    // Measured values
    mAmplitudeFirstPeak = new Vector(mNumNeurons) ; 
    mTimeToFirstPeak = new Vector(mNumNeurons) ; 
    mAmplitudeSecondPeak = new Vector(mNumNeurons) ; 
    mTimeToSecondPeak = new Vector(mNumNeurons) ; 

    // Derived values
    mBaseline = new Vector(mNumNeurons) ; 
    mSteadyState = new Vector(mNumNeurons) ; 
    mSecondOrderAmplitude = new Vector(mNumNeurons) ; 
    mSecondOrderDecay = new Vector(mNumNeurons) ; 
    mSecondOrderPeriod = new Vector(mNumNeurons) ; 
    mSecondOrderPhaseShift = new Vector(mNumNeurons) ; 

    Peak currentPeak(0,0.0) ; 

    // calculate our values
    for(int neuronCounter = 0 ; neuronCounter < mNumNeurons ; neuronCounter++){
        (*mBaseline)(neuronCounter) = (*mRawSignal)(mImpulseAt-1,neuronCounter) ; 
        (*mSteadyState)(neuronCounter) = (*mRawSignal)(mTimePoints-1,neuronCounter) ;
        currentPeak = getPeakPoint( mImpulseAt+1,neuronCounter) ; 
        cout << neuronCounter << " 0 time[" << currentPeak.getPeakTime() << "] value[" << currentPeak.getPeakValue() << "]" <<  endl ; 
        (*mAmplitudeFirstPeak)(neuronCounter) = currentPeak.getPeakValue()  ;
        (*mTimeToFirstPeak)(neuronCounter) = currentPeak.getPeakTime() - mImpulseAt  ; 
        currentPeak = getPeakPoint( currentPeak.getPeakTime()+1 ,neuronCounter) ; 
        cout << neuronCounter << " 1 time[" << currentPeak.getPeakTime() << "] value[" << currentPeak.getPeakValue() << "]" <<  endl ; 
        currentPeak = getPeakPoint( currentPeak.getPeakTime()+1 ,neuronCounter) ; 
        cout << neuronCounter << " 2 time[" << currentPeak.getPeakTime() << "] value[" << currentPeak.getPeakValue() << "]" <<  endl ; 
        (*mTimeToSecondPeak)(neuronCounter) = currentPeak.getPeakTime()  - mImpulseAt  ;
        (*mAmplitudeSecondPeak)(neuronCounter) = currentPeak.getPeakValue()   ; 
        
        /// b = - ln(A2/A1)/(t2-t1)  // could do in one sweep, but not sure how to unfold function
        (*mSecondOrderDecay) (neuronCounter) = -1.0 * log( (*mAmplitudeSecondPeak)(neuronCounter)/(*mAmplitudeFirstPeak)(neuronCounter)) / ( (*mTimeToSecondPeak)(neuronCounter)-(*mTimeToFirstPeak)(neuronCounter) )   ; 
        /// b = -ln(y2)/t2 = - ln(y1)/t1 
//        (*mSecondOrderDecay) (neuronCounter) = -1.0 * log( fabs( (*mAmplitudeFirstPeak)(neuronCounter) )  ) / ( (*mTimeToFirstPeak)(neuronCounter) )   ; 
    //    /// P = 2*PI*(t2-t1)
    //    //  could be done in one shot, but needed for amplitude calculation
        (*mSecondOrderPeriod)(neuronCounter) =  (2.0 * M_PI ) / ((*mTimeToSecondPeak)(neuronCounter) - (*mTimeToFirstPeak)(neuronCounter) )    ; 
        /// Phi = t1 - period/4
        (*mSecondOrderPhaseShift)(neuronCounter) = (*mTimeToFirstPeak)(neuronCounter) - ((* mSecondOrderPeriod)(neuronCounter)/4.0)   ;  // assume sine function, and period, then calculate backwards
    //    /// M = sin(P*t1+phi)/(exp(-b*t1) = sin(P*t1+phi)*(exp( b*t1 ) // can substitute t1 for t2 and will still work
    //    // could be done in one shot, but no funciton for sin via blitz
//        (*mSecondOrderAmplitude)(neuronCounter) = sin ( (*mSecondOrderPeriod)(neuronCounter) * (*mTimeToFirstPeak)(neuronCounter) + (*mSecondOrderPhaseShift)(neuronCounter) )  * exp (  (*mSecondOrderDecay)(neuronCounter) * (*mTimeToFirstPeak )(neuronCounter)  ) ;  // 
    //    /// M = A1 /(exp( -b*t1 ) // can substitute t1 for t2 and will still work
        (*mSecondOrderAmplitude)(neuronCounter) =  (*mAmplitudeFirstPeak)(neuronCounter) / exp ( - (*mSecondOrderDecay)(neuronCounter) * (*mTimeToFirstPeak )(neuronCounter)  ) ;  // 
    }



    // check our values
    cout << "baseline:  " << *mBaseline <<  endl ; 
    cout << "steadystate:  " << *mSteadyState <<  endl ; 
    cout << "amplitude first peak:  " << *mAmplitudeFirstPeak <<  endl ; 
    cout << "time to first peak:  " << *mTimeToFirstPeak <<  endl ; 
    cout << "amplitude Second peak:  " << *mAmplitudeSecondPeak <<  endl ; 
    cout << "time to Second peak:  " << *mTimeToSecondPeak <<  endl ; 
    cout << "secondorderdecay:  " << *mSecondOrderDecay <<  endl ; 
    cout << "secondorderperiod:  " << *mSecondOrderPeriod <<  endl ; 
    cout << "secondorderampltidue:  " << *mSecondOrderAmplitude<<  endl ; 
    cout << "secondorderphaseshift:  " << *mSecondOrderPhaseShift<<  endl ; 

    
    return this ; 
}

int SecondOrderImpulseFilter::getImpulseTime() 
{
    return mImpulseAt ; 
}



Peak SecondOrderImpulseFilter::getPeakPoint( int startingPoint,int neuronCounter) 
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
        prevValue = currentValue ; 
        ++timeCounter ; 
        currentValue = (*mRawSignal)(timeCounter,neuronCounter) ; 
        deltaValue = currentValue - prevValue ; 
    }

     return Peak(  timeCounter-1,   ( prevValue - (*mSteadyState)(neuronCounter)) )   ;

}







/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


