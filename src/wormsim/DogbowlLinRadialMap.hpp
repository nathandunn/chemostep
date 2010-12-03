
#ifndef _DogbowlDogbowlLinRadialMap_hpp
#define _DogbowlDogbowlLinRadialMap_hpp

#include <iostream>
using std::ostream ; 


#include "Dimension.hpp" 
#include "LinRadialMap.hpp" 

class Dimension ; 

/** This class is a LinRadialMap, but it has 3 points, inner, middle and outter concentrations.  If the middle is the same as the outter, you get the Dogbowl design.    
 */
class DogbowlLinRadialMap : public LinRadialMap {

	public:
		DogbowlLinRadialMap(double newDiameter,double centerConc=1,double perimeterConc=0,double midConcentration=0.5,double midRadius=0.0) ; 
	    virtual double getValue(double x,double y) const ;	
        virtual void toXML(ostream *s) ; 
        virtual double getMiddleConc() { return mMidConc ; }
        virtual double getMiddleRadius() { return mMidRadius ; }
        virtual float getDistanceToTarget(float x,float y) const ; 
 
	protected:
		double mMidConc ; 
		double mMidRadius ; 

} ;

#endif
