

#ifndef _GaussRadialMap_hpp
#define _GaussRadialMap_hpp

#include "LinRadialMap.hpp" 

class GaussRadialMap : public LinRadialMap{

	public:
		GaussRadialMap(double newDiameter,double centerConc=1,double perimeterConc=0,double sigma=1.0) ; 
	    virtual double getValue(double x,double y)   ;	
        virtual void toXML(ostream *s) ; 

    protected:
	    virtual double getNaiveValue(double x,double y)   ;	
        double sigma ; 
        double multFudgeRatio ; 
        double oldMax, oldMin ; 
	
} ;

#endif

