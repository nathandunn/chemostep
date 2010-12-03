#ifndef SETRADWORMSHUFFLER_HPP_
#  define SETRADWORMSHUFFLER_HPP_

#include "WormShuffler.hpp"

class SetRadWormShuffler : public WormShuffler {

public:
    SetRadWormShuffler(double newDiameter,double newRadius,double newDistance=0) ; 
    virtual void shuffleWorm(BaseWorm* aWorm) ; 
    virtual void toXML(ostream *s) ; 

protected:
    virtual double calculateRadius()  ; 
    double mDiameter ; 
    double mRadius ; 
    double mDistance; 

    bool mTargetOutside  ;  /// If mTargetOutside is true then mDiameter is added to mRadius, if false, then it is subtracted.
} ;

#endif /* ifndef SETRADWORMSHUFFLER_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>

