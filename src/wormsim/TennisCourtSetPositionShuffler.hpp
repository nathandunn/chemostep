

#ifndef TENNISCOURTSETPOSITIONSHUFFLER_HPP_
#  define TENNISCOURTSETPOSITIONSHUFFLER_HPP_

#include "WormShuffler.hpp"

class TennisCourtMap ; 
class SimpleWorm ; 

/// This WormShuffler places worms on a rectangular map, A distance from the target, 1/2 distance of Y vertical height.  Alternates on either side, always orienting to away to the target.
class TennisCourtSetPositionShuffler : public WormShuffler {

public:
    TennisCourtSetPositionShuffler(float newWidth,float newHeight,float newTargetX, float spaceFromTarget=0.0 ) ; 
    TennisCourtSetPositionShuffler(TennisCourtMap* newMap,float spaceFromTarget ) ; 
    virtual void shuffleWorm(BaseWorm* aWorm)  ; 
    virtual void toXML(ostream *s)  ; 

protected:
    float mWidth ; 
    float mHeight ; 
    float mTargetX ; 
    float mStartX ; 

} ;

#endif /* ifndef TENNISCOURTAWAYSHUFFLER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


