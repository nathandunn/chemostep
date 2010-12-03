#ifndef UNIFORMRADSPACEWORMSHUFFLER_HPP_
#  define UNIFORMRADSPACEWORMSHUFFLER_HPP_

#include "SetRadWormShuffler.hpp" 


class UniformRadSpaceWormShuffler : public SetRadWormShuffler{

public:
    UniformRadSpaceWormShuffler(double newDiameter,double newRadius=0.0,double spacing=0.0,double newEdgeBuffer=0.0) ; 
    virtual void shuffleWorm(Worm* aWorm) ; 
    virtual void toXML(ostream *s) ; 

    virtual double getRadiusRange(); 

protected:
    double mSpacer ; 
    double mEdgeBuffer; 

    //used internally
    double mRadiusRange, mRadiusSpacerInwardDistFromCenter, mRadiusSpacerOutwardDistFromCenter ; 

} ;

#endif /* ifndef UNIFORMRADSPACEWORMSHUFFLER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


