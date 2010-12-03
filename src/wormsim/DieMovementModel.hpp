#ifndef DIEMOVEMENTMODEL_HPP_
#  define DIEMOVEMENTMODEL_HPP_

#include "MovementModel.hpp" 


class DieMovementModel : public MovementModel {

public:
    DieMovementModel(){} ;
    virtual void move(BaseWorm* aWorm)   ;
    virtual void setVelocity(float newVelocity)   ;
    virtual float getVelocity()   ;
    virtual void toXML(ostream *s)  ; 

} ;

#endif /* ifndef DIEMOVEMENTMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

