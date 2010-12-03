#include <math.h>
#include <iostream>
using std::cout ; 
using std::endl ; 


#include "QuadMap.hpp"  
#include "LinRadialMap.hpp"  


QuadMap::QuadMap(double newDiameter,double newCenterConc,double newPerimeterConc): LinRadialMap(newDiameter,newCenterConc,newPerimeterConc) {

	cout << "quadrants, ul, ur, ll, lr " << endl  ; 
    cout << getValue(newDiameter*0.25,newDiameter*0.75) << ", " ; 
    cout << getValue(newDiameter*0.75,newDiameter*0.75) << ", " ; 
    cout << getValue(newDiameter*0.25,newDiameter*0.25) << ", " ; 
    cout << getValue(newDiameter*0.75,newDiameter*0.25) << endl ; 

}


double QuadMap::getValue(double x, double y){
	//return mCenterConc ; 	
    double value = 0 ; 
    double ratio = 0 ; 

	// absolute radial distance from the center
    double distance = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY),2)) ;



    if(distance>(0.5*mDiameter)){
		value = MapData::WALL ; 
    }else{
		// define upper-left on, lower-left off
        if( (x<mCenterX) && (y>mCenterY) || (x>mCenterX) && (y<mCenterY)){
			value = mCenterConc ; 
        }else{
			value = mPerimeterConc ; 
        }

    }

    
	return value ; 	
}


// adjust the sigma so that the minimum concentration is meant 
// the minimum concentration can't be 0.
//



