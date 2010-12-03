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
#include "LinRadialMap.hpp"  


LinRadialMap::LinRadialMap(double newDiameter,double newCenterConc,double newPerimeterConc){
      struct timeval t;
      gettimeofday(&t,0);
	  srand48(t.tv_sec);

	mDiameter = newDiameter ;
	mCenterConc = newCenterConc ; 
	mPerimeterConc = newPerimeterConc ; 

	mCenterX = (0.5)*mDiameter ; 
	mCenterY = (0.5)*mDiameter ; 
}


// return a set of X/Y 
Dimension LinRadialMap::getRandom(double scale,double startX,double startY){

    double xValue, yValue , minDistance, maxDistance, rDistance , rTheta ,startRadius ; 

    startRadius = sqrt((pow(startX-(mDiameter/2.0),2.0))+(pow(startY-(mDiameter/2.0),2.0)))  ;

    
    minDistance = startRadius - 0.5*scale ; 
    maxDistance = startRadius + 0.5*scale ; 

//    cout << "minDistance: "  << minDistance << endl ; 
//    cout << "maxDistance: "  << maxDistance << endl ; 
    
    // get a random theta  ; 
    rTheta = ((double) drand48()) * M_PI * 2.0 ; 
    
    // get a random diameter ; 
    rDistance = ((double) drand48())*(maxDistance-minDistance) + minDistance ; 

//    cout << "rTheta: " << rTheta << endl ; 
//    cout << "rDistance: " << rDistance << endl ; 
  
    xValue = cos(rTheta)*rDistance + (mDiameter /2.0 ) ; 
    yValue = sin(rTheta)*rDistance + (mDiameter / 2.0 ) ; 

//    cout << "xValue: " << xValue << endl ; 
//    cout << "yValue: " << yValue << endl ; 
    Dimension d(xValue,yValue) ; 

    return d ; 
}



double LinRadialMap::getValue(double x, double y) const {
	//return centerConc ; 	
    double value = 0 ; 

	// absolute radial distance from the center
    double distance = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY) ,2)) ;

	// the linear ratio
    value = (mCenterConc-mPerimeterConc)*(((0.5*mDiameter) - distance)/(0.5*mDiameter)) + mPerimeterConc  ; 
    if(distance>(0.5*mDiameter)){
		value = MapData::WALL ; 
    }
	return value ; 	
}



void LinRadialMap::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<mapdata type=\"linear\">" << endl ; 
    baseXML(s) ; 
    *s << "</mapdata>" << endl ; 

}

void LinRadialMap::baseXML(ostream *s) 
{
    addSpacer(s) ;
    *s << "<mDiameter value=\"" << mDiameter << "\"/>" << endl ; 
    addSpacer(s) ;
    *s << "<mCentervalue value=\"" << mCenterConc << "\"/>" << endl ; 
    addSpacer(s) ;
    *s << "<perimvalue value=\"" << mPerimeterConc << "\"/>" << endl ; 
}



