#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 




#include "Peak.hpp"
#include "ZeroOrderImpulseFilter.hpp"
#include "ZeroOrderFilter.hpp"

#include "ImpulseSignal.hpp"

ZeroOrderImpulseFilter::ZeroOrderImpulseFilter(DataFilter* newDataFilter) : ZeroOrderFilter() 
{
    setFilter(newDataFilter) ; 
}


ZeroOrderImpulseFilter::ZeroOrderImpulseFilter() : ZeroOrderFilter()
,mBaseline(NULL)
{
}

double ZeroOrderImpulseFilter::getBaseline(int labelCounter) 
{
    return (*mBaseline)(labelCounter) ; 
}


int ZeroOrderImpulseFilter::getImpulseTime() 
{
    return mImpulseAt ; 
}


string ZeroOrderImpulseFilter::getType() 
{
    return "ZeroOrderImpulseFilter" ; 
}




/**  This method sets mAmplitude, mBaseline, mSteadyState, mTimeToSteadyState.
 *
 */
DataFilter* ZeroOrderImpulseFilter::extractData(RawSignal* newSignal) 
{
    mRawSignal = new Matrix(  *(newSignal->getData()) ) ; 
    mNumNeurons = mRawSignal->columns() ; 
    mTimePoints = mRawSignal->rows() ; 
    mImpulseAt = (int) ((ImpulseSignal*) newSignal)->getImpulseTime() ; 

    
    // init vectors
    mBaseline = new Vector(mNumNeurons) ; 

    // calculate our values
    for(int neuronCounter = 0 ; neuronCounter < mNumNeurons ; neuronCounter++){
        (*mBaseline)(neuronCounter) = (*mRawSignal)(mImpulseAt-1,neuronCounter) ; 
    }

    // check our values
    cout << "baseline:  " << *mBaseline <<  endl ; 
    
    return this ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


