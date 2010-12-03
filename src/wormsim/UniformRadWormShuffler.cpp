/*
 * $Id$
 */

#include <iostream>
using std::ostream ; 
using std::cout ; 
using std::endl ; 

#include "UniformRadWormShuffler.hpp"
#include "RNG.hpp" 
#include "Worm.hpp" 

UniformRadWormShuffler::UniformRadWormShuffler(double newDiameter ) 
{
    mDiameter = newDiameter ; 
}

/// Calculate a uniformly random radius and uniformly angle on a radial map.  Need a separate theta for position on the plate and the orientation of the worm.  
void UniformRadWormShuffler::shuffleWorm(BaseWorm* aWorm) 
{
        double radius = RNG::uniform() * (mDiameter / 2.0) ; 
        double theta = RNG::uniform() * 3.1416 * 2.0  ;
        double xPos =   radius * sin(theta) + (mDiameter / 2.0) ; 
        double yPos =   radius * cos(theta) + (mDiameter / 2.0) ; 
        aWorm->setPosition(xPos , yPos );
        aWorm->setTheta(RNG::uniform() * 3.1416 * 2.0 ) ;
}

void UniformRadWormShuffler::toXML(ostream *s) 
{
    *s << "\t\t<wormshuffler type=\"uniformradwormshuffler\">" << endl ; 
    *s << "\t\t\t<diameter value=\"" << mDiameter << "\"/>" << endl ; 
    *s << "\t\t</wormshuffler>"<< endl ; 
}


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

