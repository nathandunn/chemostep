#ifndef WORMSIMSQRTRADDISTEVAL_HPP_
#  define WORMSIMSQRTRADDISTEVAL_HPP_

#include "WormSimRadDistEval.hpp" 


class WormSimSqrtRadDistEval : public WormSimRadDistEval{

public:
    WormSimSqrtRadDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity=0.02,double newPiroutteVelocity=0.02, double newMinDeltaT=1.0,double newOutputSigmoid=1.0,WormShuffler* newWormShuffler=NULL,double newTargetRadius=0.0)  ; 
    virtual void toXML(ostream *s) ; 

protected:
    virtual double getMeanValue() ;  
    virtual double getSdevValue() ; 
    virtual double getIndividualValue(int wormNumber) ;   /// This method gets an individual value of interest.

} ;

#endif /* ifndef WORMSIMSQRTMEANDISTEVAL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

