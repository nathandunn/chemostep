
#include "BaseWorm.hpp" 
#include "SimpleWorm.hpp" 
#include "Map.hpp"
#include "WormShuffler.hpp"
#include "WormLogger.hpp"

#ifdef DOMPI
  #include "mpi.h"
#endif

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "OneWormMapSpace.hpp"

OneWormMapSpace::OneWormMapSpace() : mWorm(NULL) 
,mMap(NULL)
,mLogger(NULL)
,mWormStepCount(0)
,mWormRunCount(0)
{
    #ifdef DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&mNumProcs) ; 
    MPI_Comm_rank(MPI_COMM_WORLD,&mProcNum) ; 
    #endif
}

SimpleWorm* OneWormMapSpace::getWorm() 
{
    return mWorm ; 
}

void OneWormMapSpace::setWorm(SimpleWorm* newWorm) 
{
    mWorm = newWorm ; 
}

Map* OneWormMapSpace::getMap() 
{
   return mMap ; 
}

void OneWormMapSpace::setMap(Map* newMap) 
{
    mMap = newMap ; 
}

WormShuffler* OneWormMapSpace::getWormShuffler() 
{
    return mWormShuffler ; 
}

void OneWormMapSpace::setWormShuffler(WormShuffler* newWormShuffler) 
{
    mWormShuffler = newWormShuffler ; 
}

WormLogger* OneWormMapSpace::getLogger() 
{
    return mLogger ; 
}


bool OneWormMapSpace::moveWorms(int additionalWorms) 
{
    #ifdef DOMPI
    additionalWorms = additionalWorms / mNumProcs ; 
    #endif 
    mTempMaxWormCount += additionalWorms ; 
    if(mLogger==NULL){
        mLogger = new WormLogger( mWormStepCount,mTempMaxWormCount) ; // implicitly resets the counter
    }

	
    for(  ; mWormRunCount < mTempMaxWormCount ;  mWormRunCount++){

		mWormShuffler->shuffleWorm(  mWorm) ; 
        // RELAX WORM
        
        for(int stepCount = 0 ; stepCount < mWormStepCount ;  stepCount++){
            mLogger->log(mWorm,stepCount,mWormRunCount) ; 
            mWorm->move()  ; 
        }
    }
    
    return true ; 
}

/// Resets logger and worm count.
void OneWormMapSpace::clearStats() 
{
    mWormRunCount = 0 ; 
    #ifdef DOMPI
    mTempMaxWormCount = mMaxWormCount / mNumProcs ; 
    #else
    mTempMaxWormCount = mMaxWormCount ; 
    #endif
    if(mLogger!=NULL){
        mLogger->resetCounter() ; 
    }
}

void OneWormMapSpace::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<onewormmapspace type=\"onewormmapspace\">" << endl ;
  addSpacer(s) ; 
  *s << "<wormruncount value=\"" << mWormRunCount << "\"/>" << endl ; 
  addSpacer(s) ; 
  *s << "<wormstepcount value=\"" << mWormStepCount<< "\"/>" << endl ; 
  addSpacer(s) ; 
  *s << "<maxwormcount value=\"" << mMaxWormCount << "\"/>" << endl ; 
  mMap->toXML(s) ; 
  mWormShuffler->toXML(s) ; 
  mWorm->toXML(s) ; 
  decrementTabCount() ; 
  addSpacer(s) ; 
  *s << "</onewormmapspace>" << endl ;
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


