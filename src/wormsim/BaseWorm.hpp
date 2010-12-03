#ifndef BASEWORM_HPP_
#  define BASEWORM_HPP_

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <XmlRenderable.hpp>


class BaseWorm : public XmlRenderable {

public:
    virtual float getValue()const =0 ; 
    virtual float getVelocity()=0 ; 
    virtual float getX() const =0 ; 
    virtual float getY() const = 0 ; 
    virtual float getTheta() const  = 0 ; 
    virtual void setPosition(float xPos,float yPos)=0 ; 
    virtual void setPosition(float xPos,float yPos,float newTheta)=0 ; 
    virtual void setTheta(float newTheta) { cout << "setting theta at the base" << newTheta << endl  ; }  
    virtual void setVelocity(float newVelocity)=0 ; 
    virtual void setDied(bool newDied)=0 ; 

} ;

#endif /* ifndef BASEWORM_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


