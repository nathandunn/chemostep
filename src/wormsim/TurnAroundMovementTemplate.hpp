  
       
   
#ifndef TURNAROUNDMOVEMENTTEMPLATE_HPP_
#  define TURNAROUNDMOVEMENTTEMPLATE_HPP_

#include "SharpTurnMovementModel.hpp"

template <class T> 
class TurnAroundMovementTemplate : public SharpTurnMovementTemplate<T>{

public:
    TurnAroundMovementTemplate(float newVelocity) ; 
    virtual void move(T* aWorm)   ;
    virtual void toXML(ostream *s)  ; 

} ;

#include "TurnAroundMovementTemplate.cpp"

#endif /* ifndef TURNAROUNDMOVEMENTTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


