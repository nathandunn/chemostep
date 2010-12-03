
#include <RNG.hpp>
#include <Worm.hpp> 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "Set2RadWormShuffler.hpp"

#include "WormShuffler.hpp"

Set2RadWormShuffler::Set2RadWormShuffler(double newDiameter,double newRadius1,double newRadius2) : WormShuffler() 
,mDiameter(newDiameter) 
,mRadius1(newRadius1)
,mRadius2(newRadius2)
,mTargetOutside(true) 
{
}



/// The worms are set plus or minus mDistance from mRadius, alternating between each so no random bias.  If (mRadius - mDistance) < 0 then only use the positive mDistance. 
void Set2RadWormShuffler::shuffleWorm(Worm* aWorm) 
{
    double calcRadius = calculateRadius() ; 
    double theta = RNG::uniform() * 3.1416 * 2.0  ;
    double xPos =   calcRadius * sin(theta) + (mDiameter / 2.0) ; 
    double yPos =   calcRadius * cos(theta) + (mDiameter / 2.0) ; 
    aWorm->setPosition(xPos , yPos );
    aWorm->setTheta(RNG::uniform() * 3.1416 * 2.0 ) ;
}

double Set2RadWormShuffler::calculateRadius()  
{
    if(mTargetOutside==true){
        mTargetOutside = false ; 
        return mRadius2 ; 
    }
    else{
        mTargetOutside = true ; 
        return mRadius1 ; 
    }
//    if( RNG::uniform() < 0.5){
//        return mRadius1 ; 
//    }else{
//        return mRadius2 ; 
//    }
}


void Set2RadWormShuffler::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<wormshuffler type=\"set2radwormshuffler\">" << endl ; 
    addSpacer(s) ; 
    *s << "<radius1 value=\"" << mRadius1 << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<radius2 value=\"" << mRadius2 << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "</wormshuffler>"<< endl ; 
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

