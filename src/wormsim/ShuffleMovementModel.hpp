#ifndef SHUFFLEMOVEMENTMODEL_HPP_
#  define SHUFFLEMOVEMENTMODEL_HPP_

#include "MovementModel.hpp" 

class WormShuffler ; 

class ShuffleMovementModel : public MovementModel {

public:
    ShuffleMovementModel(WormShuffler* newWormShuffler) ; 
    virtual void move(BaseWorm* aWorm)   ;
    virtual void setVelocity(float newVelocity) { }  ;
    virtual float getVelocity() { return 0.0 ; }

protected:
    WormShuffler* mWormShuffler ; 

} ;

#endif /* ifndef SHUFFLEMOVEMENTMODEL_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


