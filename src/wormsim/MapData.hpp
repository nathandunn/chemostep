


#ifndef MapData_hpp
#define MapData_hpp

#include <iostream>
using std::ostream ; 
using std::cout ; 
using std::endl ; 

#include "Map.hpp" 
class Dimension ; 

class MapData: public Map {

	public:
	    virtual double getValue(double x,double y) const  =0  ;	
	    virtual double getDiameter() const =0  ;	
	    virtual Dimension getRandom(double scale = 0,double startX = 0 , double startY = 0  ) =0  ;	
//        virtual void toXML(ostream *s) = 0 ; 

        // fields
        const static double WALL = -1 ; 
	    virtual bool inBounds(float x,float y) const  {
            cout << "not implemented" << endl ; 
           return false ;    
        };	


	    virtual float getHeight() const  { return  getDiameter() ; }   	
	    virtual float getWidth() const  { return  getDiameter()   ;	}
} ;

#endif

