#include <iostream>
using std::cout ; 
using std::endl ; 

#include "RNG.hpp" 
#include "Worm.hpp" 
#include "SetRadWormShuffler.hpp"


#include "UniformRadSpaceWormShuffler.hpp"


//#include <vector>
//using std::vector ; 
//vector<double>* radiiVector = new radiiVector() ; 

UniformRadSpaceWormShuffler::UniformRadSpaceWormShuffler(double newDiameter,double newRadius,double newSpacing ,double newEdgeBuffer): SetRadWormShuffler(newDiameter,newRadius) 
,mSpacer(newSpacing)
,mEdgeBuffer(newEdgeBuffer)
{
}

///  This method gets the implied radius range, so that it is accessible to other methods. 
double UniformRadSpaceWormShuffler::getRadiusRange()
{
    double radiusRange = 0 ;
    double radiusSpacerInwardDistFromCenter, radiusSpacerOutwardDistFromCenter ; 
    // handle the case where mSpacer will NOT occupy the center
    // distance from center to target radius minus the spacer
    mRadiusSpacerInwardDistFromCenter =   0 + mRadius - mSpacer ; 
    // distance from dish radius to target radius minus the spacer
    mRadiusSpacerOutwardDistFromCenter = ( (mDiameter/2.0) - mRadius ) - mSpacer - mEdgeBuffer ; 
    if(mRadiusSpacerInwardDistFromCenter >= 0){
        radiusRange += mRadiusSpacerInwardDistFromCenter ; 
    }
    if(mRadiusSpacerOutwardDistFromCenter >= 0  ){
        radiusRange += mRadiusSpacerOutwardDistFromCenter ; 
    }

    return radiusRange ;
    
}


/// Sets a random radius and theta outside of the spacer region. 
void UniformRadSpaceWormShuffler::shuffleWorm(Worm* aWorm) 
{
    double  placementRadius, theta , xPos,yPos  ; 

    // handle the case where mSpacer will NOT occupy the center
	mRadiusRange = getRadiusRange()  ; 

//    cout << mRadiusRange << "[" ; 
//    cout.flush() ; 

    placementRadius = RNG::uniform() * mRadiusRange ; 
    theta = RNG::uniform() * M_PI * 2.0  ;

    // mRadiusSpacerInwardDistFromCenter is calculated in getRadiusRange
    if(placementRadius > mRadiusSpacerInwardDistFromCenter ){
        placementRadius = placementRadius + ( (mDiameter/2.0) - mRadiusRange -mEdgeBuffer ) ;// current distance plus total spacer distance
    }

//    cout << placementRadius << "] " ; 
//    cout.flush() ; 

    // set it and center it
    xPos =   placementRadius * sin(theta) + (mDiameter / 2.0) ; 
    yPos =   placementRadius * cos(theta) + (mDiameter / 2.0) ; 

    aWorm->setPosition(xPos , yPos );
    aWorm->setTheta(RNG::uniform() * M_PI * 2.0 ) ;
}

void UniformRadSpaceWormShuffler::toXML(ostream *s) 
{
    *s << "\t\t<wormshuffler type=\"uniformradspacewormshuffler\">" << endl ; 
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


