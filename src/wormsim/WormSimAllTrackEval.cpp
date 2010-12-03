
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "UniformRadWormShuffler.hpp"

#include "MapSpace.hpp"
#include "BlitzLiveNet.hpp"
#include "WormSimRadDistEval.hpp"
#include "WormSimAllTrackEval.hpp"

#ifdef DOMPI
  #include "mpi.h"
#endif

WormSimAllTrackEval::WormSimAllTrackEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity/*0.02*/,double newPiroutteVelocity/*0.02*/, double newMinDeltaT/*1.0*/,double newOutputSigmoid/*1.0*/,WormShuffler* newWormShuffler,double newTargetRad,int newLastSteps,bool newDieOnEdge)  : WormSimRadDistEval(numWorms,wormSteps,origNetwork,newMap,newForwardVelocity,newPiroutteVelocity,newMinDeltaT,newOutputSigmoid,newWormShuffler,newTargetRad,newDieOnEdge) 
,mLastSteps(newLastSteps)
{
}


void WormSimAllTrackEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimalltrackeval\">" << endl ;
  addSpacer(s) ; 
  *s << "<targetradius value=\"" << mTargetRadius << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<laststeps value=\"" << mLastSteps << "\" />" << endl ;
  baseWormXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}



double WormSimAllTrackEval::getMeanValue() 
{
    double meanValue = 0 ; 
    for(int i = 0 ; i < mMapSpace->getWormCount() ; i++){
        meanValue += getIndividualValue(i) ; 
    }

#ifdef DOMPI
    // sum all of the mean values to a single one
    MPI_Allreduce(&meanValue,&procMeanValue,1,MPI_DOUBLE,MPI_SUM,MPI_COMM_WORLD) ; 
    MPI_Comm_size(MPI_COMM_WORLD,&wormProcs) ; 
    return procMeanValue / ( wormProcs * (double) mMapSpace->getWormCount() ) ; 
#else
    return meanValue / (double) mMapSpace->getWormCount() ; 
#endif


}

void WormSimAllTrackEval::setLastSteps(int newLastSteps) 
{
    mLastSteps = newLastSteps ; 
}


double WormSimAllTrackEval::getIndividualValue(int wormNumber) 
{
    double wormAvg = 0.0 ; 
    for(int i = mLastSteps  ; i < mWormSteps ; i++){
        // get the worm's timestep, and then get its worm number
        wormAvg += mMapSpace->getDistanceFromRadius((*((*mWormPositions)[i]))[wormNumber]) ; 
    }

    // add MPI call here for summation
    return wormAvg / (double) (mWormSteps-mLastSteps) ; 

}






