/*
 * $Id$
 */
#ifndef DIEMOVEMENTTEMPLATE_HPP_
#  define DIEMOVEMENTTEMPLATE_HPP_

template <class T> 
class DieMovementTemplate : public MovementModelTemplate<T>{

public:
    DieMovementTemplate() ;
    virtual void move(T* aWorm)   ;
    virtual float getVelocity()   ;
    virtual void toXML(ostream *s)  ; 

} ;

#include "DieMovementTemplate.cpp"

#endif /* ifndef DIEMOVEMENTTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


