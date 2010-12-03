#include <iostream>
using std::cout ; 
using std::endl ; 

#include "RNG.hpp" 
#include "Worm.hpp" 
#include "SetRadWormShuffler.hpp"


#include "UniformAlternateRadSpaceWormShuffler.hpp"


//#include <vector>
//using std::vector ; 
//vector<double>* radiiVector = new radiiVector() ; 

UniformAlternateRadSpaceWormShuffler::UniformAlternateRadSpaceWormShuffler(double newDiameter,double newRadius,double newSpacing ,double newEdgeBuffer): UniformRadSpaceWormShuffler (newDiameter,newRadius,newSpacing,newEdgeBuffer) 
,mTargetOutside(RNG::coinToss())
{
}



/// Sets a random radius and theta outside of the spacer region. 
void UniformAlternateRadSpaceWormShuffler::shuffleWorm(Worm* aWorm) 
{
    double  placementRadius, theta , xPos,yPos  ; 

    // handle the case where mSpacer will NOT occupy the center
    // divide by 2.0, since we are only considering one side or the other
	mRadiusRange = getRadiusRange() / 2.0   ; 

//    cout << mRadiusRange << "[" ; 
//    cout.flush() ; 

    placementRadius = RNG::uniform() * mRadiusRange ; 
    theta = RNG::uniform() * M_PI * 2.0  ;

    // mRadiusSpacerInwardDistFromCenter is calculated in getRadiusRange
//    if(placementRadius > mRadiusSpacerInwardDistFromCenter ){
    if( mTargetOutside == true){
        // if on the outside, then add the target radius
        placementRadius = placementRadius + mRadius  ;// current distance plus total spacer distance
        mTargetOutside = false ; 
    }
    else{ // if placing on the inside, instead
        mTargetOutside = true ; 
    }

//    cout << placementRadius << "] " ; 
//    cout.flush() ; 

    // set it and center it
    xPos =   placementRadius * sin(theta) + (mDiameter / 2.0) ; 
    yPos =   placementRadius * cos(theta) + (mDiameter / 2.0) ; 

    aWorm->setPosition(xPos , yPos );
    aWorm->setTheta(RNG::uniform() * M_PI * 2.0 ) ;
}

void UniformAlternateRadSpaceWormShuffler::toXML(ostream *s) 
{
    *s << "\t\t<wormshuffler type=\"uniformalternateradspacewormshuffler\">" << endl ; 
    *s << "\t\t\t<radius value=\"" << mRadius << "\"/>" << endl ; 
    *s << "\t\t\t<diameter value=\"" << mDiameter << "\"/>" << endl ; 
    *s << "\t\t\t<spacer value=\"" << mSpacer << "\"/>" << endl ; 
    *s << "\t\t\t<edgebuffer value=\"" << mEdgeBuffer << "\"/>" << endl ; 
    *s << "\t\t</wormshuffler>"<< endl ; 
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


