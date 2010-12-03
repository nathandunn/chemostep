#ifndef EVENRADWORMSHUFFLER_HPP_
#  define EVENRADWORMSHUFFLER_HPP_

#include <iostream>
using std::ostream ; 

#include "WormShuffler.hpp"


/// This class extends WormShuffler and evnly distribution of worms on a radial plate with random initial orientations.  It supports MPI by staggering the distribution, and incrementing by a value propotional to the number of processors. 
class EvenRadWormShuffler : public WormShuffler {

public:
    EvenRadWormShuffler(double newDiameter,double newNumWorms,double newEdgeBuffer=0) ; 
    virtual void shuffleWorm(BaseWorm* aWorm) ; 
    virtual void reset()  ; /// Resets counter. 
    virtual void toXML(ostream *s) ; 
    virtual double getCurrentRadius() ; 

protected:
    double mDiameter ; 
    double mNumWorms ; 
    double mRadSpace ; 
    double mCurrentRadius ; 
    double mEdgeBuffer ; 
    double mActiveRadius  ; 

    #ifdef DOMPI
    int mSetNum ; 
    int mNumSets ;
    #endif 

} ;

#endif 
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

