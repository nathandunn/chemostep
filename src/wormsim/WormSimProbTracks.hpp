
#ifndef WORMSIMPROBTRACKS_HPP_
#  define WORMSIMPROBTRACKS_HPP_

#include "WormSimAllTrackEval.hpp"

#include <WindowFunction.hpp>

#include <utility>
using std::pair ; 

class ProbDistribution ; 
class BlitzLiveNet ; 

/**  This class uses the ratio of probability differences between a reference worm (no gradient, no connections) and a live worm in a gradient. 
 *
 */
class WormSimProbTracks : public WormSimAllTrackEval {

public:
    WormSimProbTracks(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity=0.02,double newPiroutteVelocity=0.02, double newMinDeltaT=1.0,double newOutputSigmoid=1.0,WormShuffler* newWormShuffler=NULL,double newTargetRad=0.0,int newLastSteps=0,double newBinSize=0.1,WindowFunction* newWindowFunction= (new WindowFunction(0,1)),int newRefWorms=1000,double mSpacing=0.0,bool newDieOnEdge=false,WormSimAllTrackEval* newRefEval=NULL)  ;
    virtual double getMeanValue() ;  
    virtual pair<ProbDistribution*,ProbDistribution*> getDistributions() ; 
    virtual vector<double>* getBinsForPlotting() ; 
    virtual vector<double>* getCompareProbs() ; 
    virtual vector<double>* getWindowPlot() ; 
    virtual void toXML(ostream *s) ; 

    

protected:
    // methods
    virtual bool isReferenceSet() ; 
//    virtual WormSimAllTrackEval* createEvaluator(BlitzLiveNet* nullNet,int numWorms) ; 
    virtual Vector* calcRadii(vector<vector<pair<double,double> >*>* wormTracks) ; 
    Vector* mRadiiVector ; 
    virtual double compareProbs( ProbDistribution* currentDist,ProbDistribution* refDist,double mWindow) ;
    virtual void setReference() ; 


    // values
    double mUpperErrorBound ; 
    bool mReferenceSet ; 
    int mRefWorms ; 
    double mBinSize ; 
    vector<double>* mCompareProbs ; 
    ProbDistribution* mRefDistr; 
    ProbDistribution* mCurrentDistr ; 
    WormSimAllTrackEval* mRefEval  ; 
    BlitzLiveNet* mRefNetwork ; 
    WindowFunction* mWindowFunction ; 
    double mWindow ; 

} ; 

#endif /* ifndef WORMSIMPROBTRACKS_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

