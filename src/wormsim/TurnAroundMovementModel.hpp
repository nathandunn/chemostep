#ifndef TURNAROUNDMOVEMENTMODEL_HPP_
#  define TURNAROUNDMOVEMENTMODEL_HPP_

#include "SharpTurnMovementModel.hpp"

class BaseWorm ; 

/// This SharpTurnMovementModel simply bounces the worm directly back at whatever its initial velocity was (turning or running).
class TurnAroundMovementModel : public SharpTurnMovementModel{

public:
    TurnAroundMovementModel()   ; 
    virtual void move(BaseWorm* aWorm)   ;
    virtual void toXML(ostream *s)  ; 

} ;

#endif /* ifndef TURNAROUNDMOVEMENTMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

