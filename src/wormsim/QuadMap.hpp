

#ifndef _QuadMap_hpp
#define _QuadMap_hpp

#include "LinRadialMap.hpp" 

class QuadMap : public LinRadialMap{

	public:
		QuadMap(double newDiameter,double centerConc=1,double perimeterConc=0) ; 
	    virtual double getValue(double x,double y)   ;	

	
} ;

#endif

