

#ifndef _PowerRadialMap_hpp
#define _PowerRadialMap_hpp

#include "LinRadialMap.hpp" 

class PowerRadialMap : public LinRadialMap{

	public:
		PowerRadialMap(double newPower,double newDiameter,double centerConc=1,double perimeterConc=0) ; 
	    virtual double getValue(double x,double y)   ;	
        virtual void toXML(ostream *s) ; 
	
	private:
		double mPower ; 
} ;

#endif

