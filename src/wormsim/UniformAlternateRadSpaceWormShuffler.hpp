#ifndef UNIFORMALTERNATERADSPACEWORMSHUFFLER_HPP_
#  define UNIFORMALTERNATERADSPACEWORMSHUFFLER_HPP_

#include "UniformRadSpaceWormShuffler.hpp" 

/** This class extends UniformRadSpaceWormShuffler but alternates the side of the radius target that it uses.  
 *
 */
class UniformAlternateRadSpaceWormShuffler : public UniformRadSpaceWormShuffler{

public:
    UniformAlternateRadSpaceWormShuffler(double newDiameter,double newRadius=0.0,double spacing=0.0,double newEdgeBuffer=0.0) ; 
    virtual void shuffleWorm(Worm* aWorm) ; 
    virtual void toXML(ostream *s) ; 


protected:
    bool mTargetOutside ; /// whether we use the inner or outer radius

} ;

#endif /* ifndef UNIFORMRADSPACEWORMSHUFFLER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


