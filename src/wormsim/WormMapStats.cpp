
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "WormMapStats.hpp"
#include "MapSpace.hpp" 


/*  ***********************************************************************************
    Constructor */
   
//! Takes a mapspace as an argument, from which it will calculate statistics.
/*  *********************************************************************************** */
WormMapStats::WormMapStats(MapSpace* newSpace):
	mMeanValue(0), mMeanDistanceFromCenter(0)
{
    mMapSpace = newSpace ; 
}


/*  ***********************************************************************************
    calcStats() */
   
//! From mMapSpace, calculate mMeanValue and mMeanDistanceFromCenter.
/*  *********************************************************************************** */
void WormMapStats::calcStats() 
{
    // Values exclude dead worms. Others inlcude all worms.
    mMeanValue = 0.0 ; 
    mMeanDistanceFromCenter  = 0.0 ; 
    mMeanSqrtDistanceFromCenter = 0.0 ; 
    mMeanDistanceFromRadius  = 0.0 ; 
    mMeanSqrtDistanceFromRadius  = 0.0 ; 
    mSdevValue = 0.0 ; 
    mSdevLiveValue = 0.0 ; 
    mSdevDistanceFromCenter  = 0.0 ; 
    mSdevSqrtDistanceFromCenter = 0.0 ; 
    mSdevDistanceFromRadius  = 0.0 ; 
    mSdevSqrtDistanceFromRadius= 0.0 ; 
    mCount = mMapSpace->getWormCount()  ; 

    // "Live" values
    mMeanLiveValue = 0.0 ; 
    mMeanLiveDistanceFromCenter  = 0.0 ; 
    mMeanLiveDistanceFromRadius  = 0.0 ; 

    // Set up a temporary worm to make this more readable
    Worm* testWorm ;
    
    // Set wormsMoved to false so we don't do this calculation when it's not necessary.
    mMapSpace->setWormsMoved(false) ;

    // Calculate the mean value (temperature or C) of all worms
    for(int i = 0; i < mMapSpace->getWormCount(); i++) {
        testWorm = mMapSpace->getWorm(i);

        mMeanValue += testWorm->getValue();
        mMeanDistanceFromCenter += mMapSpace->getDistanceFromCenter( testWorm->getX(),testWorm->getY() );
        mMeanSqrtDistanceFromCenter += sqrt(mMapSpace->getDistanceFromCenter( testWorm->getX(),testWorm->getY() ) );
        // an always positive version of what's above, optimize later
        mMeanDistanceFromRadius += mMapSpace->getDistanceFromRadius( testWorm->getX(),testWorm->getY() );
        mMeanSqrtDistanceFromRadius += sqrt(mMapSpace->getDistanceFromRadius( testWorm->getX(),testWorm->getY() ) )  ;

        if(!testWorm->getDied()) {
            mMeanLiveValue += testWorm->getValue();
            mMeanLiveDistanceFromCenter += mMapSpace->getDistanceFromCenter( testWorm->getX(),testWorm->getY() );
            mMeanLiveDistanceFromRadius += mMapSpace->getDistanceFromRadius( testWorm->getX(),testWorm->getY() );
        }
        
            // cout << "final xPos = " << testWorm->getX() << ", yPos = " << testWorm->getY() << endl;
    }

    // Compute the means
    mMeanValue /= mCount;
    mMeanDistanceFromCenter /= mCount;
    mMeanSqrtDistanceFromCenter /= mCount;
    mMeanDistanceFromRadius /= mCount;
    mMeanSqrtDistanceFromRadius /= mCount;
    mMeanLiveValue /= (mCount - mMapSpace->getNumDied());
    mMeanLiveDistanceFromCenter /= (mCount - mMapSpace->getNumDied());
    mMeanLiveDistanceFromRadius /= (mCount - mMapSpace->getNumDied());


    double distFromCenter = 0.0 ; 
    double sqrtDistFromCenter = 0.0 ; 
    double distFromRadius = 0.0 ; 
    double sqrtDistFromRadius = 0.0 ; 
    double sdevFromRadius = 0.0 ; 

    // Calculate sdev now that we have the mean.  
    for(int i = 0; i < mMapSpace->getWormCount(); i++) {
        testWorm = mMapSpace->getWorm(i);
        distFromCenter = mMapSpace->getDistanceFromCenter( testWorm->getX(),testWorm->getY() );
        sqrtDistFromCenter = sqrt(distFromCenter) ; 
        distFromRadius = mMapSpace->getDistanceFromRadius( testWorm->getX(),testWorm->getY() );
        sqrtDistFromRadius = sqrt(distFromRadius) ; 
        mSdevValue +=  pow( testWorm->getValue(), 2.0)  ;
        mSdevDistanceFromCenter +=  pow( distFromCenter- mMeanDistanceFromCenter , 2.0) ; 
        mSdevSqrtDistanceFromCenter +=  pow( sqrtDistFromCenter - mMeanSqrtDistanceFromCenter , 2.0) ; 
        mSdevDistanceFromRadius +=  pow( distFromRadius- mMeanDistanceFromRadius , 2.0) ; 
        mSdevSqrtDistanceFromRadius +=  pow( sqrtDistFromRadius - mMeanSqrtDistanceFromRadius , 2.0) ; 
        if(!testWorm->getDied()) {
            mSdevLiveValue += pow ( testWorm->getValue()-mMeanLiveValue, 2.0 ) ;
        }
    }




    // Compute the sdev
    mSdevValue=  sqrt( mSdevValue / mCount) ; 
    mSdevLiveValue =  sqrt( mSdevLiveValue / (mCount - mMapSpace->getNumDied()) ) ; 
    mSdevDistanceFromCenter =  sqrt ( mSdevDistanceFromCenter / mCount ) ; 
    mSdevSqrtDistanceFromCenter =  sqrt ( mSdevSqrtDistanceFromCenter / mCount ) ; 
    mSdevDistanceFromRadius =  sqrt ( mSdevDistanceFromRadius / mCount ) ; 
    mSdevDistanceFromRadius =  sqrt ( mSdevSqrtDistanceFromRadius / mCount ) ; 
}


/*  ***********************************************************************************
    getMeanValue() */
   
//! Call calcStats if mean value has not already been determined.
/*  *********************************************************************************** */
double WormMapStats::getMeanValue() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mMeanValue ; 
}


/*  ***********************************************************************************
    getMeanDistanceFromCenter() */
   
//! Call calcStats if the mean distance from center has not already been determined.
/*  *********************************************************************************** */
double WormMapStats::getMeanDistanceFromCenter() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mMeanDistanceFromCenter ; 
}

double WormMapStats::getMeanSqrtDistanceFromCenter() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mMeanSqrtDistanceFromCenter ; 
}

double WormMapStats::getSdevSqrtDistanceFromCenter() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mSdevSqrtDistanceFromCenter ; 
}


double WormMapStats::getSdevLiveValue() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mSdevLiveValue ; 
    
}




/*  ***********************************************************************************
    getMeanDistanceFromRadius() */
   
//! Call calcStats if the mean distance from the set radius has not already been determined.
/*  *********************************************************************************** */
double WormMapStats::getMeanDistanceFromRadius() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mMeanDistanceFromRadius ; 
}

double WormMapStats::getSdevSqrtDistanceFromRadius() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mSdevSqrtDistanceFromRadius ; 
}


double WormMapStats::getMeanSqrtDistanceFromRadius() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mMeanSqrtDistanceFromRadius ; 
}



/*  ***********************************************************************************
    getMeanLiveValue() */
   
//! Call calcStats if the mean distance from center of all living worms has not already been determined.
/*  *********************************************************************************** */
double WormMapStats::getMeanLiveValue() 
{
    cout << "A in getMeanLiveValue" << endl ; 
    if(mMapSpace->getWormsMoved() == true){
    cout << "B in getMeanLiveValue" << endl ; 
        calcStats() ; 
    }
    cout << "C in getMeanLiveValue" << endl ; 

    return mMeanLiveValue ; 
}


/*  ***********************************************************************************
    getMeanLiveDistanceFromCenter() */
   
//! Call calcStats if the mean distance from center of all living worms has not already been determined.
/*  *********************************************************************************** */
double WormMapStats::getMeanLiveDistanceFromCenter() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }

    return mMeanLiveDistanceFromCenter ; 
}


/*  ***********************************************************************************
    getMeanLiveDistanceFromCenter() */
   
//! Call calcStats if the mean distance from center of all living worms has not already been determined.
/*  *********************************************************************************** */
double WormMapStats::getMeanLiveDistanceFromRadius() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mMeanLiveDistanceFromRadius ; 
}

double WormMapStats::getSdevValue() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mSdevValue ; 
}


double WormMapStats::getSdevDistanceFromCenter() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mSdevDistanceFromCenter ; 
}

double WormMapStats::getSdevDistanceFromRadius() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mSdevDistanceFromRadius; 
}

int WormMapStats::getCount() 
{
    if(mMapSpace->getWormsMoved() == true){
        calcStats() ; 
    }
    return mCount ; 
}



/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

