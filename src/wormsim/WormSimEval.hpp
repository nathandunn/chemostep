#ifndef WORMSIMEVAL_HPP_
#  define WORMSIMEVAL_HPP_

#include <vector> 
using std::vector ; 
#include <utility> 
using std::pair ; 

#include <iostream>
using std::ostream ; 

#include "BlitzNetEvaluator.hpp" 

class MapSpace ; 
class NeuralNetwork ; 
class BlitzLiveNet ; 
class WormMapStats; 
class MapData; 
class WormShuffler ; 

/**  This class extends BlitzNetEvaluator to handle BlitzNet, and is a wrapper around running N worms, based on a MapSpace and a network.  Somewhere in the code we need to have a vector of networks which the worms use as a reference and is copied over after a perturbation.  All distances and speeds are in cm.
 *
 *
 *
 */
class WormSimEval : public BlitzNetEvaluator {

public:
    WormSimEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity=0.02,double newPiroutteVelocity=0.02, double newMinDeltaT=1.0,double newOutputSigmoid=1.0,WormShuffler* newWormShuffler=NULL,bool newDieOnEdge=false)  ; 
    virtual void createNetworks() ; 
    virtual void addWorms() ; 
    virtual double getTargetRadius() { return 0.0 ; }
    virtual void shuffleWorms() ; 
    virtual double eval(NeuralNetwork* newNetwork) ;  /// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.
    virtual void setNetwork(NeuralNetwork* newNetwork) ;  /// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.
    virtual double getSdev() ; 
    virtual int getCount() ; 
    virtual vector<vector<pair<double,double> >*>* getWormTracks() ; 


    // relax methods for propagation
    virtual void relaxNet(bool doTrace=false) ;  /// this method needs to run each of the assigned networks in the Cache N times
//    virtual void setRelaxLimit(double _mRelaxLimit) ; 
    virtual void setRelaxTime(double newRelaxTime) ;
    virtual void setRelaxDeltaT(double newRelaxDeltaT) ; 
    virtual void setRelaxTau(double newRelaxTau) ; 

    // custom methods
    virtual void setMapSpace(MapSpace* newMapSpace) ; 
    virtual double getMinDeltaT() ; 
    virtual void toXML(ostream *s) ; 
    virtual double getHAvg() ; 
    virtual bool evaluateWorms(NeuralNetwork* newNetwork) ;  /// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.

protected:
    virtual double getMeanValue() ;   /// Gets the mean value that we are using here.
    virtual double getSdevValue() ;   /// Gets the standard deviation of the value that we are using, here.
    virtual double getIndividualValue(int wormNumber) ;   /// This method gets an individual value of interest.
    virtual bool getIndividualValid(int wormNumber) ;  /// This method asks if a worm is valid to count in the statistics.
    virtual int getCountValue() ; /// This method returns all of the worms considered over one run on this processor.
    virtual int getCountValid() ;  /// This method only returns the number of values actually used in the mean.
    virtual void baseWormXML(ostream *s) ; /// This method handles feeders, etc.  
    MapSpace *mMapSpace ; 
    vector<BlitzLiveNet*>* mWormNets ; 
    int mNumWorms ; 
    int mWormSteps ; 
    BlitzLiveNet* mOrigNetwork; 
    BlitzLiveNet* mEvalNetwork; 
    WormMapStats* mWormMapStats; 
    WormShuffler* mWormShuffler ; 
    double mForwardVelocity, mPirouetteVelocity ; 
    double mNetOutputSigmoid ; 
    vector< vector<pair<double,double> >*>* mWormPositions ; /// This variable holds a vector of worm positions



protected:
  virtual void initTrackerVector() ; 
  double meanValue ; 
  double sdevValue ; 
  int countValue ; 
  double avgHValue  ; 
  bool mDieOnEdge ; 
  #ifdef DOMPI
  double procAvgHValue ; 
  double procMeanValue ; 
  double procSdevValue ; 
  int procCountValue ; 
  int wormRank ; 
  int wormProcs ; 
  #endif

} ;

#endif /* ifndef WORMSIMEVAL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

