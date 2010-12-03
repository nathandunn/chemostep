
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "ShufflePreserveMovementModel.hpp"
#include "ShuffleMovementModel.hpp"
#include "WormShuffler.hpp"
#include "BaseWorm.hpp"
#include "Worm.hpp"


ShufflePreserveMovementModel::ShufflePreserveMovementModel(WormShuffler* newWormShuffler) : ShuffleMovementModel(newWormShuffler)
{
}

///  This method preserves the orientation and position of the worm.  I.e., if it keeps hitting the edge, it will continue to do so. 
void ShufflePreserveMovementModel::move(BaseWorm* aWorm)   
{
    float theta = aWorm->getTheta() ; 
    mWormShuffler->shuffleWorm(aWorm) ; 
    float distance = ((Worm*) aWorm)->getDistanceFromCenter() ; 
    aWorm->setTheta(theta) ; 
    double xPos =   distance * sin(theta) + ( ((Worm*) aWorm)->getMapSpace())->getCenterX()     ; 
    double yPos =   distance * cos(theta) + (((Worm*) aWorm)->getMapSpace())->getCenterY()  ; 
    aWorm->setPosition(xPos,yPos) ; 
}

void ShufflePreserveMovementModel::toXML(ostream *s)  
{
    *s << "<movementmodel type=\"shufflepreservemovementmodel\">" << endl ; 
    mWormShuffler->toXML(s) ; 
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


