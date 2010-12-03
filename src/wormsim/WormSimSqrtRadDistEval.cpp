
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "Worm.hpp"
#include "WormMapStats.hpp"
#include "BlitzLiveNet.hpp" 
#include "MapData.hpp" 

#include "WormSimSqrtRadDistEval.hpp"


WormSimSqrtRadDistEval::WormSimSqrtRadDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity,double newPiroutteVelocity, double newMinDeltaT,double newOutputSigmoid,WormShuffler* newWormShuffler,double newTargetRadius) : WormSimRadDistEval(numWorms,wormSteps,origNetwork,newMap,newForwardVelocity,newPiroutteVelocity,newMinDeltaT,newOutputSigmoid,newWormShuffler,newTargetRadius)  
{ 
}



double WormSimSqrtRadDistEval::getMeanValue() 
{
     return (mWormMapStats->getMeanSqrtDistanceFromRadius()) ; 
}

double WormSimSqrtRadDistEval::getSdevValue() 
{
    return  (mWormMapStats->getSdevSqrtDistanceFromRadius() ); 
}

double WormSimSqrtRadDistEval::getIndividualValue(int wormNumber) 
{
    Worm* testWorm  = mMapSpace->getWorm(wormNumber)  ; 
    return sqrt(mMapSpace->getDistanceFromRadius(testWorm->getX(),testWorm->getY())  ) ; 
}


void WormSimSqrtRadDistEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimsqrtraddisteval\">" << endl ;
  addSpacer(s) ; 
  *s << "<targetradius value=\"" << mTargetRadius << "\" />" << endl ;
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

