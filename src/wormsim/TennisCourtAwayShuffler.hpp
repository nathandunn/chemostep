

#ifndef TENNISCOURTAWAYSHUFFLER_HPP_
#  define TENNISCOURTAWAYSHUFFLER_HPP_

#include "WormShuffler.hpp"

class TennisCourtMap ; 
class SimpleWorm ; 

/// This WormShuffler places worms on a rectangular map, A distance from the target, 1/2 distance of Y vertical height.  Alternates on either side, always orienting to away to the target.
class TennisCourtAwayShuffler : public WormShuffler {

public:
    TennisCourtAwayShuffler(float newWidth,float newHeight,float newTargetX, float spaceFromTarget=0.0 ) ; 
    TennisCourtAwayShuffler(TennisCourtMap* newMap,float spaceFromTarget ) ; 
    virtual void shuffleWorm(BaseWorm* aWorm)  ; 
    virtual void reset()  ;  
    virtual void toXML(ostream *s)  ; 

protected:
    bool mLeftSide ; /// Defined as less that the targetX
    float mWidth ; 
    float mHeight ; 
    float mTargetX ; 
    float mSpaceFromTarget ; 

} ;

#endif /* ifndef TENNISCOURTAWAYSHUFFLER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


