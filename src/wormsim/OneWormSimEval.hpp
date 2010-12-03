#ifndef ONEWORMSIMEVAL_HPP_
#  define ONEWORMSIMEVAL_HPP_





#include <iostream>
using std::ostream ; 


class OneWormMapSpace  ;
class SimpleWorm ;
class BlitzLiveNet ;
class WormShuffler ;
class WormTrack ;
class BlitzEulerLiveNetEvaluator ;
class WormLogger ;
class NeuralNetwork ;

#include "BlitzNetEvaluator.hpp"

/** Description:  Class OneWormSimEval versus WormSimEval using SimpleWorm and OneWormMapSpace.  The class encomposses a MapSpace and evaluates the WormLogger. 
 *
 */
class OneWormSimEval : public BlitzNetEvaluator {

public:
    OneWormSimEval() ; 
    virtual double eval(NeuralNetwork* newNetwork) ;  /// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.
    virtual bool evaluateWorms(NeuralNetwork* newNetwork) ;  /// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.
    virtual double evaluateMoreWorms(int moreWorms) ;  /// Evaluates more of the same worms without resetting
    virtual void setMapSpace(OneWormMapSpace* newMapSpace) ; 
    virtual OneWormMapSpace* getMapSpace() ; 
    virtual void setWorm(SimpleWorm* newWorm) ; 
    virtual BlitzNetEvaluator* getWormEval() ; 
    virtual void setNetwork(NeuralNetwork* newNetwork) ;  /// Method does not use evalPoint and evaluates over N worms.  Returns mMeanValue, here, I guess.
//    virtual void setWormNetworkEvaluator(BlitzNetEvaluator* newEvaluator) ;  /// This is the evaluator used by the worm's network.  
//    virtual BlitzLiveNet* getWormNet() ;  /// Returns the memory reference of the worm's network.
    virtual void toXML(ostream *s) ; 
    virtual vector<WormTrack*>* getWormTracks() ; 
    virtual void setTarget(double newTarget) ; 
    virtual double getMinDeltaT() ; 
    virtual void setMinDeltaT(double newDeltaT) ; 


protected:
    virtual void initDistanceVector(  int numPoints ) ; 
    virtual void calculateDistances( WormLogger* theLogger) ; 
    OneWormMapSpace* mMapSpace ; 
    int mWormSteps ; 
    int mDefaultWormNum ; 
    int mNumWorms ; 
    int mNumPoints;  /// The number of points to be considered.
    double mMeanValue ;  /// The average 'value' over N networks.
    Vector* mDistanceVector ; 
    double mTargetX; 


    // WORMSIMEVAL NETWORK VALUE
    BlitzLiveNet* mOrigNetwork ;  /// This is the OneWormSimEval network evaluator.  

    // WORM VALUES
    SimpleWorm* mWorm;  /// The worm to evaluate.

    #ifdef DOMPI
    int mWormProcs ; 
    double mProcMeanValue ; 
    #endif
} ;

#endif /* ifndef ONEWORMSIMEVAL_H */

