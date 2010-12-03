/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "DieMovementModel.hpp"
#include "BaseWorm.hpp" 

void DieMovementModel::move(BaseWorm* aWorm)   
{
    aWorm->setDied(true) ; 
}

void DieMovementModel::setVelocity(float newVelocity) {
//    cout << "why are you setting DieMovementModel velocity? to: " << newVelocity << endl ; 
   // do nothing 
};

float DieMovementModel::getVelocity() {
  return 0.0 ; 
}

void DieMovementModel::toXML(ostream *s)  
{
    addSpacer(s) ; 
    *s << "<movementmodel type=\"diemovementmodel\">" << endl ; 
    addSpacer(s) ; 
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

