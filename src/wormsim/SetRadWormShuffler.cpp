
#include <RNG.hpp>
#include <Worm.hpp> 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "SetRadWormShuffler.hpp"

#include "WormShuffler.hpp"

SetRadWormShuffler::SetRadWormShuffler(double newDiameter,double newRadius,double newDistance) : WormShuffler() 
,mDiameter(newDiameter)
,mRadius(newRadius)
,mDistance(newDistance)
,mTargetOutside(true) 
{
}

double SetRadWormShuffler::calculateRadius()  
{
    double calcRadius ; 

    // if mTargetOutside is valid
	if( RNG::uniform() < 0.5){
        mTargetOutside = true ; 
    }else{
        mTargetOutside = false ; 
    }
    
    if(mTargetOutside==true){
        if( (mRadius + mDistance) > mDiameter/2.0){
            calcRadius = mRadius - mDistance ; 
        }
        else{
            calcRadius = mRadius + mDistance ; 
        }
        mTargetOutside = false ; 
    }
    else
    if(mTargetOutside==false){
        if( (mRadius - mDistance) < 0.0){
            calcRadius = mRadius + mDistance ; 
        }
        else{
            calcRadius = mRadius - mDistance ; 
        }
        mTargetOutside = true ; 
    }
    return calcRadius ; 
}


/// The worms are set plus or minus mDistance from mRadius, alternating between each so no random bias.  If (mRadius - mDistance) < 0 then only use the positive mDistance. 
void SetRadWormShuffler::shuffleWorm(BaseWorm* aWorm) 
{
        double calcRadius = calculateRadius() ; 
        double theta = RNG::uniform() * 3.1416 * 2.0  ;
        double xPos =   calcRadius * sin(theta) + (mDiameter / 2.0) ; 
        double yPos =   calcRadius * cos(theta) + (mDiameter / 2.0) ; 
        aWorm->setPosition(xPos , yPos );
        aWorm->setTheta(RNG::uniform() * 3.1416 * 2.0 ) ;
}

void SetRadWormShuffler::toXML(ostream *s) 
{
    *s << "\t\t<wormshuffler type=\"setradwormshuffler\">" << endl ; 
    *s << "\t\t\t<radius value=\"" << mRadius << "\"/>" << endl ; 
    *s << "\t\t\t<diameter value=\"" << mDiameter << "\"/>" << endl ; 
    *s << "\t\t\t<distance value=\"" << mDistance << "\"/>" << endl ; 
    *s << "\t\t</wormshuffler>"<< endl ; 
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
// FILE: "/Users/nathandunn/svn/chemostep-square/src/wormsim/SetRadWormShuffler.cpp"
// LAST MODIFICATION: "Fri, 17 Dec 2004 15:35:12 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

