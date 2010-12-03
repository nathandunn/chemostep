#include <math.h>
#include <iostream>
using std::ostream ; 
using std::endl ; 

#ifndef MACOSX
    #include <sys/time.h>
    #include <time.h>
    #include <stdlib.h>
#endif

#include "Dimension.hpp" 
#include "DogbowlLinRadialMap.hpp"  


DogbowlLinRadialMap::DogbowlLinRadialMap(double newDiameter,double newCenterConc,double newPerimeterConc,double newMidConc,double newMidRadius): LinRadialMap(newDiameter,newCenterConc,newPerimeterConc) {
    mMidConc = newMidConc ; 
    mMidRadius = newMidRadius ; 

//    cout << "dogbowl diam[" << mDiameter << "] centerValue[" << mCenterConc << "] perimConc[" << mPerimeterConc << "] midConc[" << mMidConc << "] mMidRadius[" << mMidRadius << "]" << endl ; 
       
}

float DogbowlLinRadialMap::getDistanceToTarget(float x,float y) const 
{
    double radius = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY) ,2)) ;
    return fabs( mMidRadius-radius) ;
}


/**  Gets the dogowl value based on the radius.  
 *
 */
double DogbowlLinRadialMap::getValue(double x, double y) const
{
	//return centerConc ; 	
    double value = 0 ; 

	// absolute radial distance from the center
    double distance = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY) ,2)) ;

	// the linear ratio
//    value = (mCenterConc-mPerimeterConc)*(((0.5*mDiameter) - distance)/(0.5*mDiameter)) + mPerimeterConc  ; 
    // the linear ratio from perimeter to mid radius
    if(distance >= mMidRadius && distance <= mDiameter/2.0){
//        value = (mMidConc-mPerimeterConc) / (mMidRadius - (mDiameter/2.0)) + mMidConc ; 
        value = (distance-mMidRadius) * (mPerimeterConc - mMidConc) / (mDiameter/2.0 - mMidRadius) + mMidConc ; 
    }
    else
    // the linear ratio from mid radius to the center 
    if(distance < mMidRadius && distance > 0 ){
//        value = (mCenterConc-mMidConc) / (0 - mMidRadius) + mCenterConc ; 
        value = distance * (mMidConc - mCenterConc) / (mMidRadius - 0 ) + mCenterConc ; 
    }
    else
    if(distance>(0.5*mDiameter)){
		value = MapData::WALL ; 
    }
	return value ; 	
}

void DogbowlLinRadialMap::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<mapdata type=\"dogbowllinear\">" << endl ; 
    baseXML(s) ; 
    addSpacer(s) ; 
    *s << "<midconc value=\"" << mMidConc << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<midradius value=\"" << mMidRadius << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "</mapdata>" << endl ; 
}




