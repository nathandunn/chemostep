
#include <iostream>
using std::ostream ; 
using std::cout ; 
using std::endl ; 

#ifdef DOMPI
  #include "mpi.h"
#endif


#include "MapSpace.hpp"
#include "WormMapStats.hpp"
#include "NeuralNetwork.hpp"

#include "WormSimMeanDistEval.hpp"


WormSimMeanDistEval::WormSimMeanDistEval(int numWorms,int wormSteps,BlitzLiveNet* origNetwork,MapData* newMap,double newForwardVelocity,double newPiroutteVelocity, double newMinDeltaT,double newOutputSigmoid,WormShuffler* newWormShuffler,bool newDieOnEdge)  : WormSimEval(numWorms,wormSteps,origNetwork,newMap,newForwardVelocity,newPiroutteVelocity,newMinDeltaT,newOutputSigmoid,newWormShuffler,newDieOnEdge) 
{
}

double WormSimMeanDistEval::getMeanValue() 
{
    return mWormMapStats->getMeanDistanceFromCenter() ; 
}

double WormSimMeanDistEval::getIndividualValue(int wormNumber) 
{
    Worm* testWorm  = mMapSpace->getWorm(wormNumber)  ; 
    return mMapSpace->getDistanceFromCenter(testWorm->getX(),testWorm->getY()) ; 
}

bool WormSimMeanDistEval::getIndividualValid(int wormNumber) 
{
    return true ; 
}

int WormSimMeanDistEval::getCountValid() 
{
    return mMapSpace->getWormCount() ; 
}




double WormSimMeanDistEval::getSdevValue() 
{
    return mWormMapStats->getSdevDistanceFromCenter() ; 
}


void WormSimMeanDistEval::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"wormsimmeandisteval\">" << endl ;
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

