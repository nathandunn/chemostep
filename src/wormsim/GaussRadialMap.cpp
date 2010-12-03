#include <math.h>
#include <iostream>
using std::cout ; 
using std::endl ; 


#include "GaussRadialMap.hpp"  
#include "LinRadialMap.hpp"  


GaussRadialMap::GaussRadialMap(double newDiameter,double newCenterConc,double newPerimeterConc, double newSigma): LinRadialMap(newDiameter,newCenterConc,newPerimeterConc) {

    sigma = newSigma ; 
	multFudgeRatio= 1.0 ; 

	// adjust the fudge-factor and sigma until we get the perimiter and center concentrations
  	oldMax =  getNaiveValue(newDiameter/2,newDiameter/2) ;
  	oldMin =  getNaiveValue(newDiameter,newDiameter/2) ;
    double oldRatio = fabs((oldMax - oldMin)) ; 
    double newRatio =  fabs((newCenterConc- newPerimeterConc)) ;
   
    multFudgeRatio = newRatio / oldRatio ; 
	cout << "oldMax: " << oldMax << endl ; 
	cout << "oldMin: " << oldMin << endl ; 
	cout << "newPerimeterConc: " << newPerimeterConc << endl ; 

    
    
	cout << "new guass map from: "  ; 
	cout << getValue(newDiameter/2,newDiameter/2) ; 
	cout << " to "  ; 
	cout << getValue(newDiameter,newDiameter/2) ; 
	cout << endl ; 
}


double GaussRadialMap::getValue(double x, double y){
	//return centerConc ; 	
    double value = 0 ; 
    double ratio = 0 ; 

	// absolute radial distance from the center
    double distance = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY),2)) ;


    ratio =  -1.0/2.0*pow(((distance)/(0.5*mDiameter)),2)/pow(sigma,2);
    value = exp(ratio)/ (sigma * pow(2*M_PI,0.5)) ;  

    value -= oldMin ; 
    value *= multFudgeRatio ; 
    value += mPerimeterConc ; 

//    value = (centerConc-mPerimeterConc)*value + mPerimeterConc  ; 
    if(distance>(0.5*mDiameter)){
		value = MapData::WALL ; 
    }
    
	return value ; 	
}


// adjust the sigma so that the minimum concentration is meant 
// the minimum concentration can't be 0.
//

double GaussRadialMap::getNaiveValue(double x, double y){
	//return centerConc ; 	
    double value = 0 ; 
    double ratio = 0 ; 

	// absolute radial distance from the center
    double distance = sqrt(pow((x-mCenterX),2 )+pow((y-mCenterY),2)) ;


    ratio =  -1.0/2.0*pow(((distance)/(0.5*mDiameter)),2)/pow(sigma,2);
     value = exp(ratio)/ (sigma * pow(2*M_PI,0.5)) ;  
//     value = (centerConc-mPerimeterConc)*value + mPerimeterConc  ; 
   
    if(distance>(0.5*mDiameter)){
		value = MapData::WALL ; 
    }
    
	return value ; 	
}

void GaussRadialMap::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<mapdata type=\"linear\">" << endl ; 
    addSpacer(s) ; 
    *s << "<sigma value=\"" << sigma << "\"" << endl ; 
    baseXML(s) ; 
    addSpacer(s,-1) ; 
    *s << "</mapdata>" << endl ; 
}



