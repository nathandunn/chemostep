

#ifndef WORMSIMALLTRACKEVAL_HPP_
#  define WORMSIMALLTRACKEVAL_HPP_

#include "WormSimRadDistEval.hpp"

class WormSimAllTrackEval : public WormSimRadDistEval{

public:
    WormSimAllTrackEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity=0.02,double newPiroutteVelocity=0.02, double newMinDeltaT=1.0,double newOutputSigmoid=1.0,WormShuffler* newWormShuffler=NULL,double newTargetRad=0.0,int newLastSteps=0,bool newDieOnEdge=false)  ; 
    virtual double getMeanValue() ;  
    virtual double getIndividualValue(int wormNumber) ;  
    virtual void setLastSteps(int newLastSteps) ;  
    virtual void toXML(ostream *s) ; 

protected:
    int mLastSteps ;

} ;

#endif /* ifndef WORMSIMALLTRACKEVAL_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/wormsim/WormSimAllTrackEval.hpp"
// LAST MODIFICATION: "Thu, 28 Oct 2004 12:25:15 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

