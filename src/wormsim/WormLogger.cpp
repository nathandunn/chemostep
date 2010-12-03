
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::pair ; 

#include "SimpleWorm.hpp"
#include "WormLogger.hpp"
#include "WormTrack.hpp"


WormLogger::WormLogger(int numWormSteps,int defaultNumWorms) 
:mWormPositions(NULL)
,mStepCounter(0)
,mWormCounter(0)
,mNumWormSteps(numWormSteps) 
,mDefaultNumWorms(defaultNumWorms) 
{
    initLogger() ; 
}

void WormLogger::resetCounter() 
{
  mStepCounter = 0  ; 
  mWormCounter = 0  ; 
}

pair<double,double> WormLogger::getNextPoint() 
{
    if(mStepCounter>=mNumWormSteps){
        ++mWormCounter ; 
        mStepCounter = 0 ; 
    }

    // check to see if all the worms
    if(mWormCounter>= mWormPositions->size()){
        cout <<  "ran out of worms at mWormCounter[" << mWormCounter << "]" << endl ; 
        return pair<double,double>(0,0); 
    }

//    cout << "mWormCounter[" << mWormCounter << "] mStepCounter[" << mStepCounter << "]" << endl ; 

//    ++mStepCounter ;   // needs to be evaluated after the mStepCounter

    return ((*mWormPositions)[mWormCounter])->getStep(mStepCounter++) ; 
}



void WormLogger::initLogger() {
//    cout << "init logger for: " << mDefaultNumWorms << " and " << mNumWormSteps << endl ; 
    mWormPositions = new vector<WormTrack*>(mDefaultNumWorms) ; 
	
    for(int i = 0 ; i< mWormPositions->size() ; i++){
        (*mWormPositions)[i] = new WormTrack(mNumWormSteps) ; 
    }
}


/// Gets the number of recorded number of points, minus any steps that need to be ignored.
int WormLogger::getNumPoints(int ignoreSteps) 
{
    if(mWormPositions==NULL){
        return 0 ; 
    }
    else{
       return (mNumWormSteps-ignoreSteps) * mWormPositions->size() ; 
    }
}

void WormLogger::log(SimpleWorm* worm,int stepCount,int wormCount) 
{
    if(mWormPositions==NULL){
        initLogger() ; 
    }
    
    if(wormCount >= mWormPositions->size()){
        mWormPositions->push_back( new WormTrack(mNumWormSteps) ) ; 
    }

    ((*mWormPositions)[wormCount])->recordPosition( (double) worm->getX(),(double) worm->getY(), stepCount) ;     
}

vector<WormTrack*>* WormLogger::getWormTracks() 
{
    return mWormPositions ; 
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


