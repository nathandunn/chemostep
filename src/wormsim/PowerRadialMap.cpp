#include <math.h>
#include <iostream>
using std::ostream ; 
using std::endl ; 


#include "PowerRadialMap.hpp"  


PowerRadialMap::PowerRadialMap(double newPower,double newDiameter,double newCenterConc,double newPerimeterConc): LinRadialMap(newDiameter,newCenterConc,newPerimeterConc) {
	mPower = newPower ;
}


double PowerRadialMap::getValue(double x, double y){
    double value = 0 ; 

	// absolute radial distance from the center
    double distance = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY) ,2)) ;
    double ratio =  (((0.5*mDiameter) - distance)/(0.5*mDiameter));

	// the linear ratio
    value = (mCenterConc-mPerimeterConc)*pow(ratio,mPower) + mPerimeterConc  ; 
    if(distance>(0.5*mDiameter)){
		value = MapData::WALL ; 
    }
	return value ; 	
}

void PowerRadialMap::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<mapdata type=\"power\">" << endl ; 
    addSpacer(s) ; 
    *s << "<mPower value=\"" << mPower << "\"" << endl ; 
    baseXML(s) ; 
    addSpacer(s) ; 
    *s << "</mapdata>" << endl ; 
}



