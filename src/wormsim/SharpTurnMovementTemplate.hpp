

#ifndef SHARPTURNMOVEMENTTEMPLATE_HPP_
#  define SHARPTURNMOVEMENTTEMPLATE_HPP_


#include "MovementModelTemplate.hpp"


template <class T> 
class SharpTurnMovementTemplate : public MovementModelTemplate<T>{

public:
    SharpTurnMovementTemplate( float newThreshold,float newVelocity) ; 
    virtual void move(T* aWorm)   ;
    virtual void setThresholdAngle( float mThresholdAngle ) ;  
    virtual float getThresholdAngle() { return mThresholdAngle*180.0 / M_PI ; }
    virtual void toXML(ostream *s)  ; 
protected:
    float mThresholdAngle ; 

} ;

#include "SharpTurnMovementTemplate.cpp"

#endif /* ifndef SHARPTURNMOVEMENTTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


