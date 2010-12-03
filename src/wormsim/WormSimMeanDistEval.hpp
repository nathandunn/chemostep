#ifndef WORMSIMMEANDISTEVAL_HPP_
#  define WORMSIMMEANDISTEVAL_HPP_

#include <iostream>
using std::ostream ; 

#include "WormSimEval.hpp"

class NeuralNetwork ; 

/**  This class extends WormSimEval, calculating the mean distance from the center of the map.
 *
 */
class WormSimMeanDistEval : public WormSimEval{

public:
    WormSimMeanDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity=0.02,double newPiroutteVelocity=0.02, double newMinDeltaT=1.0,double newOutputSigmoid=1.0,WormShuffler* newWormShuffler=NULL,bool newDieOnEdge=false)  ; 
//    virtual double eval(NeuralNetwork* newNetwork) ;  /// This method explicitly calculates the distance from the center of the map.
    virtual void toXML(ostream *s) ; 

protected:
    virtual double getMeanValue() ;  
    virtual double getSdevValue() ; 
    virtual double getIndividualValue(int wormNumber) ;   /// This method gets an individual value of interest.
    virtual bool getIndividualValid(int wormNumber) ;  /// This method asks if a worm is valid to count in the statistics.
    virtual int getCountValid() ;  /// This method only returns the number of values actually used in the mean.

} ;

#endif /* ifndef WORMSIMMEANDISTEVAL_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/wormsim/WormSimMeanDistEval.hpp"
// LAST MODIFICATION: "Thu, 28 Oct 2004 12:26:34 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

