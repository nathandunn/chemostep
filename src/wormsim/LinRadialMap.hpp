
#ifndef _LinRadialMap_hpp
#define _LinRadialMap_hpp

#include <iostream>
using std::ostream ; 


#include "Dimension.hpp" 
#include "MapData.hpp" 

class Dimension ; 

class LinRadialMap : public MapData {

	public:
		LinRadialMap(double diameter,double centerConc=1,double perimeterConc=0) ; 
	    virtual double getValue(double x,double y) const    ;	
	    virtual double getDiameter() const {return mDiameter ; }   	
//	    virtual Dimension getRandom(double scale =0 )   ;	
	    virtual Dimension getRandom(double scale =0 ,double startingX =0  , double startingY =0 )   ;	
        virtual void toXML(ostream *s) ; 
        virtual double getmCenterConc(){ return mCenterConc ; }
        virtual double getPerimiterConc() { return mPerimeterConc ; }
 
	protected:
        virtual void baseXML(ostream *s) ; 
		double mCenterConc ; 
		double mPerimeterConc ; 
		double mDiameter ; 
		double mCenterX ; 
		double mCenterY ; 

} ;

#endif
