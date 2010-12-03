#ifndef SHUFFLEPRESERVEMOVEMENTMODEL_HPP_
#  define SHUFFLEPRESERVEMOVEMENTMODEL_HPP_

#include "ShuffleMovementModel.hpp" 

class WormShuffler ; 

class ShufflePreserveMovementModel: public ShuffleMovementModel{

public:
    ShufflePreserveMovementModel(WormShuffler* newWormShuffler) ; 
    virtual void move(BaseWorm* aWorm)   ;
    virtual void toXML(ostream *s)  ; 


} ;

#endif /* ifndef SHUFFLEMOVEMENTMODEL_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


