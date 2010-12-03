
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include <math.h>

#include "Position.hpp"

Position::Position()  :
mX(0.0)    
,mY(0.0)    
,mTheta(0.0)    
{
}

Position::Position(float newX,float newY) :
mX(newX)    
,mY(newY)    
,mTheta(0.0)    
{
}

Position::Position(Position* newPosition) 
{
    mX = newPosition->getX() ; 
    mY = newPosition->getY() ; 
	setTheta(newPosition->getTheta()) ; 
}


Position::Position(float newX,float newY,float newTheta) :
mX(newX)    
,mY(newY)    
//,mTheta(newTheta)    
{
    setTheta(newTheta) ; 
}

float Position::getTheta() 
{
    return mTheta ; 
}

float Position::setTheta(float newTheta) 
{
    if(newTheta>= 2.0 * M_PI){
        newTheta = newTheta - 2.0 * M_PI ; 
    }
    else
    if(newTheta< 0.0 ){
        newTheta = newTheta + 2.0 * M_PI ; 
    }
    mTheta = newTheta ; 
	return mTheta ; 
}



float Position::getX() 
{
  return mX ; 
}

float Position::getY() 
{
  return mY ; 
}

float Position::getDistance(float newX,float newY) 
{
    return sqrt(  pow ( newX - mX , 2.0) + pow ( newY - mY, 2.0) ) ;  
}

ostream& Position::operator<<(ostream &s) const {
    s << "x,y,theta[" << mX << "," << mY << "," << mTheta ; 
}

Position& Position::operator=(Position &rhs){

    mX = rhs.getX() ; 
    mY = rhs.getY() ; 
    setTheta(rhs.getTheta()) ; 
}


void Position::setX(float newX) 
{
    mX = newX ; 
}


void Position::setY(float newY) 
{
    mY = newY ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


