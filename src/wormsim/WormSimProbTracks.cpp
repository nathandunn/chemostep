
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <utility>
using std::pair ; 

using std::max ; 

#ifdef DOMPI
  #include "mpi.h"
#endif


#include <BlitzLiveNet.hpp>
#include <blitzdefs.hpp>


//#include "UniformRadSpaceWormShuffler.hpp"
//#include "EvenRadWormShuffler.hpp"
#include "EvenRadWormShuffler.hpp"
#include "WormSimAllTrackEval.hpp"
#include "ProbDistribution.hpp"
#include "LinRadialMap.hpp"
#include "MapSpace.hpp"


#include "WormSimProbTracks.hpp"

WormSimProbTracks::WormSimProbTracks(int numWorms,int newWormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity,double newPiroutteVelocity, double newMinDeltaT,double newOutputSigmoid,WormShuffler* newWormShuffler,double newTargetRad,int newLastSteps,double newBinSize,WindowFunction* newWindowFunction,int newRefWorms,double newSpacing,bool newDieOnEdge,WormSimAllTrackEval* newRefEval)  : WormSimAllTrackEval(numWorms,newWormSteps,origNetwork,newMap,newForwardVelocity,newPiroutteVelocity,newMinDeltaT,newOutputSigmoid,newWormShuffler,newTargetRad,newLastSteps,newDieOnEdge)
,mBinSize(newBinSize)
,mRefWorms(newRefWorms)  
,mWindowFunction(newWindowFunction)  
,mReferenceSet(false)  
,mRefDistr(NULL)  
,mCurrentDistr(NULL)  
,mRefNetwork(NULL)  
,mCompareProbs(NULL)  
,mRadiiVector(NULL)  
,mUpperErrorBound(10.0)  
,mRefEval(newRefEval)  
{
}




/// Returns a meanValue as the inverse of the average of the ratios.  If the average of the ratios is 0 or infinite, than it returns the # of bins, which is a VERY high error value.  
double WormSimProbTracks::getMeanValue() 
{
    if( isReferenceSet()==false){
        setReference() ; 
    }


    // set values 
    // the first step is to create bins from our tracks
	if(mCurrentDistr==NULL){
        // use the maximum possible radius
        mCurrentDistr = new ProbDistribution(mBinSize,  max( (((LinRadialMap*) mMapSpace->getMap())->getDiameter()/ 2.0)- mTargetRadius , mTargetRadius ) , 0.0) ; 
    }

    // use this evaluator to calculate tracks
    mCurrentDistr->setDistribution( calcRadii(getWormTracks()) ) ;
    double returnCompareProbs  =   compareProbs( mCurrentDistr, mRefDistr ,mWindow) ; 
    if( returnCompareProbs == 0.0){
        return mCurrentDistr->getNumBins() * 1.0 ; 
    }
    else{
        return 1.0 / returnCompareProbs ; 
    }
}


vector<double>* WormSimProbTracks::getCompareProbs() 
{
    return new vector<double>(*mCompareProbs) ; 
}

vector<double>* WormSimProbTracks::getWindowPlot() 
{
    vector<double>* returnVector = new vector<double>() ; 
    int maxRadiusBin = mRefDistr->getNumBins() ; 
    int maxWindowBin = mRefDistr->getBinForValue(mWindow) ; 
    double maxRadius = (((LinRadialMap*) mMapSpace->getMap())->getDiameter() / 2.0)- mTargetRadius ;
    for(double radius = 0 ; radius < maxRadius ; radius+=mBinSize ){
        returnVector->push_back( mWindowFunction->getValue(radius) ) ; 
    }
    return returnVector ; 
}



/**  This returns the integral of the ratio from 0 to mWindow.  If the result is 0 (poor result), it returns a very small number).  
 *
 */
double WormSimProbTracks::compareProbs( ProbDistribution* currentDist,ProbDistribution* refDist,double thisWindow) 
{
    double returnValue = 0.0 ; 
    double radius = 0.0 ; 
    int maxWindowBin = currentDist->getBinForValue(thisWindow) ; 
    int maxRadiusBin= currentDist->getNumBins() ; 

    double refValue, currentValue, ratioValue  ; 
    if(mCompareProbs==NULL  || mCompareProbs->size() != maxRadiusBin ){
        mCompareProbs = new vector<double>(maxRadiusBin) ; 
    }

    for(int binNumber = 0 ; binNumber < maxRadiusBin ; binNumber++){
        refValue = refDist->getValueForBin(binNumber) ; 
        currentValue = currentDist->getValueForBin(binNumber) ; 
        if(refValue==0 && currentValue==0.0){
            // returns 0?
            ratioValue = 0 ; 
        }
        else
        if(refValue==0){
            // need an upper bound
            ratioValue = mUpperErrorBound  ; 
        }
        // if currentValue =0, will be 0
        else{
            ratioValue = currentValue / refValue ; 
        }
//        (*mCompareProbs)[binNumber] =   ratioValue ; 
        (*mCompareProbs)[binNumber] =   ratioValue * mWindowFunction->getValue( (mRefDistr->getBinMax(binNumber)) ) ; 
        returnValue +=  (*mCompareProbs)[binNumber] ;
    }

    double highValue = 10.0 ; 
    if( returnValue ==0.0){
        return (1.0/highValue) ; 
    }
    if(returnValue < 0){
        return (1/ ( highValue - returnValue) ) ;  // 10+negative value, gives more range
    }

    return returnValue ; 
}





bool WormSimProbTracks::isReferenceSet() 
{
    return mReferenceSet ; 
}



// This method sets a reference probability distribution by running a horde of worms, as usual, and storing the distribution.
void WormSimProbTracks::setReference() 
{
    // store old settings
    mRefNetwork = new BlitzLiveNet(mOrigNetwork) ; 
//    *mRefNetwork = *(mOrigNetwork) ; 
    int numWorms ; 

    (*(mRefNetwork->getBias())) = 0 ; 
//    (*(mRefNetwork->getBias()))(mRefNetwork->getNumNeurons()-1) = 10000.0  ;  // we want only running
    (*(mRefNetwork->getWeights())) = 0 ; 

    #ifdef DOMPI
        MPI_Comm_size(MPI_COMM_WORLD, &wormProcs) ;
        MPI_Comm_rank(MPI_COMM_WORLD, &wormRank) ;
        numWorms = mRefWorms / wormProcs ; 
    #else
        numWorms = mRefWorms ; 
    #endif
    mRefNetwork->setEvaluator( mRefEval ) ; 

    #ifdef DOMPI
    if(wormRank==0)
    #endif
    cout << "START ref eval" << endl ; 
    mRefEval->evaluateWorms(mRefNetwork) ; 
    mRefNetwork->eval() ; 
    #ifdef DOMPI
    if(wormRank==0)
    #endif
    cout << "END ref eval" << endl ; 
    
    
    // set values 
    // the first step is to create bins from our tracks
	if(mRefDistr==NULL){
        // use the maximum possible radius
        mRefDistr = new ProbDistribution(mBinSize, max( ((LinRadialMap*) mMapSpace->getMap())->getDiameter() / 2.0 - mTargetRadius , mTargetRadius ), 0.0) ; 
    }
    Vector* radiiVector =  calcRadii(   mRefEval->getWormTracks())  ;
    mRefDistr->setDistribution( radiiVector) ; 

    // set reference set to true
    mReferenceSet = true ; 
}


/// Returns a reference in a pair (*mRefDistr,*mCurrentDistr).
pair<ProbDistribution*,ProbDistribution*> WormSimProbTracks::getDistributions() 
{
//    return new pair<ProbDistribution*,ProbDistribution*>(mRefDistr,mCurrentDistr) ; 
    return pair<ProbDistribution*,ProbDistribution*>(mRefDistr,mCurrentDistr) ; 
}

///  Returns the center of each bin, making sure to encompass the maximum of each.
vector<double>* WormSimProbTracks::getBinsForPlotting() 
{
   vector<double>* returnVector  = new vector<double>(mRefDistr->getNumBins()) ; 
   Bin theBin(0,0) ; 
   for(int i = 0 ; i < returnVector->size() ; i++){
       theBin = mRefDistr->getBin(i) ; 
       (*returnVector)[i] =  (theBin.first + theBin.second) / 2.0 ; 
   }
   
   return returnVector ; 
}



/// Here we take every worm and position and turn it into a radius.
Vector* WormSimProbTracks::calcRadii(vector<vector<pair<double,double> >*>* wormTracks) 
{
    int numPositions  ; 
    int numWorms = ((*wormTracks)[0])->size(); 

    // calculate numPositions as the number of worms * the number of steps we wish to consider
    // maybe we can use for_each() here?
    numPositions = (mWormSteps - mLastSteps)* numWorms ;  // calculate for only # of worms on processor

//    returnVector = new Vector(numPositions) ; 
    if ( mRadiiVector ==NULL || mRadiiVector->size() != numPositions ){
        mRadiiVector = new Vector(numPositions) ; 
    }

    int counter = 0 ; 
    for(int wormStep = mLastSteps ; wormStep < mWormSteps ; wormStep++){
        for(int wormNumber = 0 ; wormNumber < numWorms ; wormNumber++,counter++){
            (*mRadiiVector)(counter) = mMapSpace->getDistanceFromRadius((*((*wormTracks)[wormStep]))[wormNumber]) ; 
        }
    }
    return mRadiiVector ; 
}

void WormSimProbTracks::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimprobtracks\">" << endl ;
  addSpacer(s) ; 
  *s << "<targetradius value=\"" << mTargetRadius << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<laststeps value=\"" << mLastSteps << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<binsize value=\"" << mBinSize << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<refwormcount value=\"" << mRefWorms << "\" />" << endl ;
  mWindowFunction->toXML(s) ; 
  baseWormXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
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
// $Id:$

