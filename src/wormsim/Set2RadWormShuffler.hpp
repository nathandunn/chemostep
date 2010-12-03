#ifndef SET2RADWORMSHUFFLER_HPP_
#  define SET2RADWORMSHUFFLER_HPP_

#include "WormShuffler.hpp"

class Set2RadWormShuffler : public WormShuffler {

public:
    Set2RadWormShuffler(double newDiameter, double newRadius1,double newRadius2) ; 
    virtual void shuffleWorm(Worm* aWorm) ; 
    virtual void toXML(ostream *s) ; 

protected:
    virtual double calculateRadius()  ; 
    double mDiameter ; 
    double mRadius1 ; 
    double mRadius2 ; 
    bool mTargetOutside ; 
} ;

#endif /* ifndef SETRADWORMSHUFFLER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>

