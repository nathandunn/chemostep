#ifndef MOVEMENTMODELTEMPLATE_HPP_
#  define MOVEMENTMODELTEMPLATE_HPP_

#include <iostream>
using std::ostream ; 

#include <XmlRenderable.hpp>


template <class T> class MovementModelTemplate : public XmlRenderable{

public:
    MovementModelTemplate(float newVelocity=0) ;
    virtual void move(T* aWorm)   ;
    virtual void setVelocity(float newVelocity) ; 
    virtual float getVelocity() ;
    virtual void toXML(ostream *s)  ; 

protected:
    float mVelocity ;
    float mDeltaX,mDeltaY,mDeltaTheta ; 
    const static float INVS_RAND_MAX ; 


} ;

#include "MovementModelTemplate.cpp"

#endif /* ifndef MOVEMENTMODELTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


