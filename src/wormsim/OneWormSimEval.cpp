
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 
using std::pair ; 

#ifdef DOMPI
  #include "mpi.h"
#endif


#include "BlitzNetEvaluator.hpp" 
#include "WormLogger.hpp"
#include "Map.hpp"
#include "BlitzLiveNet.hpp"
#include "SimpleWorm.hpp"
#include "OneWormMapSpace.hpp"
#include "BlitzNetEvaluator.hpp" 
#include "WormShuffler.hpp" 
#include "WormLogger.hpp" 



#include "OneWormSimEval.hpp"

OneWormSimEval::OneWormSimEval() : BlitzNetEvaluator() 
,mOrigNetwork(NULL)
,mMapSpace(NULL)
,mDistanceVector(NULL)
{
#ifdef DOMPI
    MPI_Comm_size(MPI_COMM_WORLD,&mWormProcs) ; 
#endif
}


double OneWormSimEval::eval(NeuralNetwork* newNetwork) 
{
    if(newNetwork->getValid() == true){
        return mMeanValue ; 
    }
    mNumPoints = mMapSpace->getWormStepCount() ; 
    resetTrace( mNumPoints , mNumPoints ) ; 

    evaluateWorms(newNetwork) ; 
    return mMeanValue ; 

}/// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.

double OneWormSimEval::evaluateMoreWorms(int moreWorms) 
{
    mMapSpace->moveWorms( moreWorms) ; 
    calculateDistances( mMapSpace->getLogger() ) ;  // sets mMeanValue and anything else
    mOrigNetwork->setValue(mMeanValue) ; 
    mOrigNetwork->setValid(true) ; 

    return mMeanValue ; 
}


BlitzNetEvaluator* OneWormSimEval::getWormEval() 
{
    if(mMapSpace==NULL){
        cout << "mapspace not yet definted" << endl ; 
        return NULL ; 
    }
//    return (BlitzNetEvaluator*) ((mWorm->getBehaviorModel())->getNetwork())->getEvaluator() ; 
    return (BlitzNetEvaluator*) (((mMapSpace->getWorm())->getBehaviorModel())->getNetwork())->getEvaluator() ; 
}




bool OneWormSimEval::evaluateWorms(NeuralNetwork* newNetwork) 
{
    setNetwork(newNetwork) ; 
    mMapSpace->clearStats() ; 
    mMapSpace->moveWorms() ; 
	
    // CALCULATE DISTANCES and SUM, COUNTER AT THE SAME TIME

    calculateDistances( mMapSpace->getLogger() ) ;  // sets mMeanValue and anything else
    mOrigNetwork->setValue(mMeanValue) ; 
    mOrigNetwork->setValid(true) ; 

    return true ; 
}

///  Inits a distance vector.
void OneWormSimEval::initDistanceVector( int numPoints) 
{
    if(mDistanceVector==NULL){
        mDistanceVector = new Vector( numPoints )  ; 
    }
    else
//    if(mDistanceVector->size() != numPoints  ){
    if(mDistanceVector->size() < numPoints  ){
        mDistanceVector->resize( numPoints ) ;
    }
    else{
        // do nothing, since its okay if its too large
    }

    // we assume that this just resizes, and doesn't need to be reset
}


///  Calculates distances from the targets.  Initially, we will ignore no points.  We realize that the # of points of interest is the # of points evaluated, not necessarily all of hte points int the logger.
void OneWormSimEval::calculateDistances( WormLogger* theLogger) 
{
    int localNumPoints = mMapSpace->getNumPoints() ; // retrieve the # of points actually run and cast to local variable 
    mNumPoints = localNumPoints ; 

    initDistanceVector(mNumPoints) ; 
    theLogger->resetCounter() ;  // reset counter as we enumerate over points
  
    Map* theMap = mMapSpace->getMap() ; 
    pair<double,double> point ; 
    for(int i = 0 ; i < mNumPoints ; i++){
         
//        (*mDistanceVector)(i) =  fabs( (theLogger->getNextPoint()).first - mTargetX)  ; 
        point = theLogger->getNextPoint() ; 
        (*mDistanceVector)(i) =  theMap->getDistanceToTarget( point.first,point.second)  ; 
//        cout << i << ": distance[" << (*mDistanceVector)(i)  << "] point[" << point.first << "," << point.second << "]" << endl ;  
    }

    // Sum over everything, in basic, unoptimized form, which seems to be pretty quick.
    mMeanValue = 0 ; 
    for(int i = 0 ; i < localNumPoints ; i++){
        mMeanValue += (*mDistanceVector)(i) ; 
    }

    // sum all of the mMeanValue stuff, here
    #ifdef DOMPI
    MPI_Allreduce(&mMeanValue,&mProcMeanValue,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD) ; 
    mMeanValue = mProcMeanValue / ( (double) mNumPoints * mWormProcs) ; 
    #else
    mMeanValue = mMeanValue / (double) mNumPoints ; 
    #endif



}

void OneWormSimEval::setTarget(double newTarget) 
{
    mTargetX = newTarget ; 
}



vector<WormTrack*>* OneWormSimEval::getWormTracks() 
{
    return  (mMapSpace->getLogger())->getWormTracks() ; 
}



void OneWormSimEval::setMapSpace(OneWormMapSpace* newMapSpace) 
{
    mMapSpace = newMapSpace ; 
}


void OneWormSimEval::setWorm(SimpleWorm* newWorm) 
{
    mWorm = newWorm ; 
    mMapSpace->setWorm(newWorm) ; 
}

/// This setNetwork method sets a memory reference for mOrigNetwork, setting itself as the evaluator (which makes sense, anyway).  
void OneWormSimEval::setNetwork(NeuralNetwork* newNetwork) 
{
    mOrigNetwork = (BlitzLiveNet*) newNetwork ; 
    mOrigNetwork->setEvaluator(this) ;
    
    if(  mMapSpace!=NULL && mMapSpace->getWorm()!= NULL && ((mMapSpace->getWorm())->getBehaviorModel())!=NULL){
        ((mMapSpace->getWorm())->getBehaviorModel())->setNetwork( mOrigNetwork ) ; // this sets a copy in the behavior model
    }

}




void OneWormSimEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"onewormsimeval\">" << endl ;
  mMapSpace->toXML(s) ; 
  // add a blurb about a worm shuffler
  doBaseXML(s) ; 
  addSpacer(s) ; 
  // close the XML
  *s << "</evaluator>" << endl ;
}

OneWormMapSpace* OneWormSimEval::getMapSpace() 
{
    return mMapSpace ; 
}





void OneWormSimEval::setMinDeltaT(double newDeltaT) 
{
    mMinDeltaT = newDeltaT ; 
}


double OneWormSimEval::getMinDeltaT() 
{
    return mMinDeltaT  ; 
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



