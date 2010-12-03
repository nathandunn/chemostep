#include <iostream>
using std::cout ; 
using std::endl ; 

#ifdef DOMPI
  #include "mpi.h"
#endif


#include "WormLogger.hpp"
#include "OneWormMapSpace.hpp"
#include "WorstPairOneWormSimEval.hpp"

WorstPairOneWormSimEval::WorstPairOneWormSimEval() : OneWormSimEval()
,mDistVector1(NULL)
,mDistVector2(NULL)
{
}

void WorstPairOneWormSimEval::calculateDistances( WormLogger* theLogger) 
{
    mNumPoints = mMapSpace->getNumPoints() ; // retrieve the # of points actually run and cast to local variable 
    int localStepCount = mMapSpace->getWormStepCount() ;
    int worm1StepCount  = 0 ; 
    int worm2StepCount = 0 ; 
    int worm1TotalCount ,worm2TotalCount;
    double meanDist1 , meanDist2  ; 
    int startCount, stopCount ; 
    int trackCount  = 0 ; 

    worm1TotalCount = mNumPoints / localStepCount / 2 ; 
    worm2TotalCount= mNumPoints / localStepCount / 2 ; 
    if( (worm1TotalCount + worm2TotalCount) < mNumPoints/localStepCount ){
        ++worm1TotalCount; 
    }

    if(mDistVector1==NULL){
        mDistVector1 = new Vector(localStepCount*worm1TotalCount) ; 
        mDistVector2 = new Vector(localStepCount*worm2TotalCount) ; 
    }

    if(mDistVector1->size()!=(localStepCount*worm1TotalCount)){
        mDistVector1->resize(localStepCount*worm1TotalCount) ; 
    }

    if(mDistVector2->size()!=(localStepCount*worm2TotalCount)){
        mDistVector2->resize(localStepCount*worm2TotalCount) ; 
    }

    initDistanceVector(mNumPoints) ; 
    theLogger->resetCounter() ;  // reset counter as we enumerate over points

    *mDistVector1 = DBL_MAX ; 
    *mDistVector2 = DBL_MAX ; 
    mMeanValue = 0 ; 
   
    for(int i = 0 ; i < mNumPoints ; i++){
        (*mDistanceVector)(i) =  fabs( (theLogger->getNextPoint()).first - mTargetX)  ; 
    }


    // Sum over everything, in basic, unoptimized form, which seems to be pretty quick.
    while( trackCount < mNumPoints ){

        // If these counters are the same, then increment the first 1.
        if(worm1StepCount==worm2StepCount){
            // Set up a generic counter
            startCount = worm1StepCount*localStepCount ; 
            stopCount = startCount + localStepCount ; 

            for( ; startCount < stopCount ; startCount++,trackCount++){
                (*mDistVector1)(startCount) = (*mDistanceVector)(trackCount) ;
            }
            ++worm1StepCount ; 
        }
        // worm1StepCount > worm2StepCount
        else{
            startCount = worm2StepCount*localStepCount ; 
            stopCount = startCount + localStepCount ; 
            for( ; startCount < stopCount ; startCount++,trackCount++){
                (*mDistVector2)(startCount) = (*mDistanceVector)(trackCount) ;
            }
            ++worm2StepCount ; 
        }
    }
    

    // sum all of the mMeanValue stuff, here
    #ifdef DOMPI
    fromValues.count1 = worm1StepCount ; 
    fromValues.count2 = worm2StepCount ; 
    fromValues.sum1 = sum(*mDistVector1) ; 
    fromValues.sum2 = sum(*mDistVector2) ; 
    MPI_Allreduce(&fromValues,&toValues,4,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD) ; 
    meanDist1 = toValues.sum1 / (toValues.count1*localStepCount) ; 
    meanDist2 = toValues.sum2 / (toValues.count2*localStepCount) ; 
    #else
    meanDist1 = sum(*mDistVector1) / ((float) worm1StepCount*localStepCount) ; 
    meanDist2 = sum(*mDistVector2) / ((float) worm2StepCount * localStepCount) ; 
//    cout << "worm1StepCount[" << worm1StepCount << "] worm2StepCount[" << worm2StepCount << "]" << endl ; 
    #endif
    if(meanDist1 > meanDist2 || worm2StepCount==0){
        mMeanValue = meanDist1 ; 
    }
    else{
        mMeanValue = meanDist2 ; 
    }


}



void WorstPairOneWormSimEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"worstpaironewormsimeval\">" << endl ;
  mMapSpace->toXML(s) ; 
  // add a blurb about a worm shuffler
  doBaseXML(s) ; 
  addSpacer(s) ; 
  // close the XML
  *s << "</evaluator>" << endl ;
}



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


