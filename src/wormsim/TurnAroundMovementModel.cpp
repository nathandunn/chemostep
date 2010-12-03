
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "TurnAroundMovementModel.hpp"
#include "BaseWorm.hpp"

TurnAroundMovementModel::TurnAroundMovementModel() : SharpTurnMovementModel(0.0)
{
}


void TurnAroundMovementModel::move(BaseWorm* aWorm)   
{
    mDeltaTheta = M_PI ; 
    
    aWorm->setTheta(aWorm->getTheta()+mDeltaTheta) ; 
    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;   // 3. set dX based on velocity and theta
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   // 3. set dY based on velocity and theta
    aWorm ->setPosition((mDeltaX +aWorm->getX()), (mDeltaY+aWorm->getY())) ; // steps 4 and 6
}

void TurnAroundMovementModel::toXML(ostream *s)  
{
    *s << "<movementmodel type=\"turnaroundmovementmodel\">" << endl ; 
    *s << "<velocity value=\"" << velocity << "\">" << endl ; 
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
// $Id:$

