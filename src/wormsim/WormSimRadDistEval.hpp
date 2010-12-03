#ifndef WORMSIMRADDISTEVAL_HPP_
#  define WORMSIMRADDISTEVAL_HPP_

#include "WormSimMeanDistEval.hpp"

class NeuralNetwork ; 

///  This class calculates the distance from a set radius where the distance is always positive.
class WormSimRadDistEval : public WormSimMeanDistEval {

public:
    WormSimRadDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity,double newPiroutteVelocity,double newMinDeltaT,double newOutputSigmoid, WormShuffler* newWormShuffler=NULL,double targetRadius=0.0,bool newDieOnEdge=false)  ; 
    virtual double getTargetRadius() ;  
    virtual void toXML(ostream *s) ; 

protected:
    virtual double getMeanValue() ;  
    virtual double getSdevValue() ; 
    virtual double getIndividualValue(int wormNumber) ;   /// This method gets an individual value of interest.
    double mTargetRadius ; 

} ;

#endif /* ifndef WORMSIMRADDISTEVAL_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/wormsim/WormSimRadDistEval.hpp"
// LAST MODIFICATION: "Thu, 28 Oct 2004 12:26:14 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

