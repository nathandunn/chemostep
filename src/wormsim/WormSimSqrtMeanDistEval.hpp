#ifndef WORMSIMSQRTMEANDISTEVAL_HPP_
#  define WORMSIMSQRTMEANDISTEVAL_HPP_

#include "WormSimMeanDistEval.hpp" 


class WormSimSqrtMeanDistEval : public WormSimMeanDistEval{

public:
    WormSimSqrtMeanDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity=0.02,double newPiroutteVelocity=0.02, double newMinDeltaT=1.0,double newOutputSigmoid=1.0,WormShuffler* newWormShuffler=NULL)  ; 
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

