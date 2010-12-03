
#ifndef POSITION_HPP_
#  define POSITION_HPP_

#include <iostream>
using std::ostream ; 

using std::pair ; 

class Position {

public:
    Position() ; 
    Position(Position* newPosition) ; 
    Position(float newX,float newY) ; 
    Position(float newX,float newY,float newTheta) ; 
    virtual float getX() ; 
    virtual float getY() ; 
    virtual float getDistance(float newX,float newY) ; 
    virtual void setX(float newX) ; 
    virtual void setY(float newY) ; 

    virtual float setTheta(float newTheta) ; 
    virtual float getTheta() ; 

    Position& operator=(Position &net); 
    ostream& operator<<(ostream &s) const ; 

protected:
    float mX ; 
    float mY ; 
    float mTheta ; 
    

} ;

#endif /* ifndef POSITION_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


