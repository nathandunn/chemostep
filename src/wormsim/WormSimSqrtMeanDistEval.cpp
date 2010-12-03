
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "Worm.hpp"
#include "WormMapStats.hpp"
#include "BlitzLiveNet.hpp" 
#include "MapData.hpp" 

#include "WormSimMeanDistEval.hpp"
#include "WormSimSqrtMeanDistEval.hpp"


WormSimSqrtMeanDistEval::WormSimSqrtMeanDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity,double newPiroutteVelocity, double newMinDeltaT,double newOutputSigmoid,WormShuffler* newWormShuffler) : WormSimMeanDistEval(numWorms,wormSteps,origNetwork,newMap,newForwardVelocity,newPiroutteVelocity,newMinDeltaT,newOutputSigmoid,newWormShuffler)  
{ }


double WormSimSqrtMeanDistEval::getIndividualValue(int wormNumber) 
{
    Worm* testWorm  = mMapSpace->getWorm(wormNumber)  ; 
    return sqrt(mMapSpace->getDistanceFromCenter(testWorm->getX(),testWorm->getY())  ) ; 
}

double WormSimSqrtMeanDistEval::getMeanValue() 
{
     return (mWormMapStats->getMeanSqrtDistanceFromCenter() ) ;
}

double WormSimSqrtMeanDistEval::getSdevValue() 
{
    return  (mWormMapStats->getSdevSqrtDistanceFromCenter() ); 
}

void WormSimSqrtMeanDistEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimsqrtmeandisteval\">" << endl ;
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
// FILE: "/Users/nathandunn/svn/chemotrunk/src/wormsim/WormSimSqrtMeanDistEval.cpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 12:24:47 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

