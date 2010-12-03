/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "SharpTurnMovementTemplate.hpp"

template <class T> 
TurnAroundMovementTemplate<T>::TurnAroundMovementTemplate(float newVelocity) : SharpTurnMovementTemplate<T>(0.0,newVelocity)
{
}


template <class T> 
void TurnAroundMovementTemplate<T>::move(T* aWorm)   
{
    mDeltaTheta = M_PI ; 
    
    aWorm->setTheta(aWorm->getTheta()+mDeltaTheta) ; 
    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;   // 3. set dX based on velocity and theta
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   // 3. set dY based on velocity and theta
    aWorm ->setPosition((mDeltaX +aWorm->getX()), (mDeltaY+aWorm->getY())) ; // steps 4 and 6
}


template <class T> 
void TurnAroundMovementTemplate<T>::toXML(ostream *s)  
{
    *s << "<movementmodel type=\"turnaroundmovementtemplate\">" << endl ; 
    *s << "<velocity value=\"" << mVelocity << "\">" << endl ; 
    *s << "</movementmodel>" << endl ; 
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


