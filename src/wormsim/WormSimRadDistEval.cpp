/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "MapSpace.hpp"
#include "WormMapStats.hpp"

#include "WormSimMeanDistEval.hpp"

#include "WormSimRadDistEval.hpp"

WormSimRadDistEval::WormSimRadDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity,double newPiroutteVelocity, double newMinDeltaT,double newOutputSigmoid, WormShuffler* newWormShuffler,double targetRadius,bool newDieOnEdge)  : WormSimMeanDistEval(numWorms,wormSteps,origNetwork,newMap,newForwardVelocity,newPiroutteVelocity,newMinDeltaT,newOutputSigmoid,newWormShuffler,newDieOnEdge) 
,mTargetRadius(targetRadius)
{
    mMapSpace->setCenterRadius( mTargetRadius , mMapSpace->getCenterX(), mMapSpace->getCenterY()) ; 
}

double WormSimRadDistEval::getMeanValue() 
{
    return mWormMapStats->getMeanDistanceFromRadius() ; 
}

double WormSimRadDistEval::getSdevValue() 
{
    return mWormMapStats->getSdevDistanceFromRadius() ; 
}

double WormSimRadDistEval::getIndividualValue(int wormNumber) 
{
    Worm* testWorm  = mMapSpace->getWorm(wormNumber)  ; 
    return mMapSpace->getDistanceFromRadius(testWorm->getX(),testWorm->getY()) ; 
}

double WormSimRadDistEval::getTargetRadius() 
{
    return mTargetRadius ; 
}


void WormSimRadDistEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimraddisteval\">" << endl ;
  addSpacer(s) ; 
  *s << "<targetradius value=\"" << mTargetRadius << "\" />" << endl ;
  baseWormXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}



/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/wormsim/WormSimRadDistEval.cpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 12:24:24 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

