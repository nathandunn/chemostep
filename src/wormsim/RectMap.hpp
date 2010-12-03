#ifndef RECTMAP_HPP_
#  define RECTMAP_HPP_

#include <iostream>
using std::ostream ; 

#include "Map.hpp" 

class Position ; 

class RectMap : public Map {

public:
    RectMap() ; 
    RectMap(float xWidth,float yHeight) ; 
	virtual double getValue(Position* newPosition) const =0 ; 
	virtual double getValue(double xPos,double yPos) const =0 ; 
//    virtual void toXML(ostream *s) const =0 ; 
    virtual float getHeight() const  ;  /// Return Y
    virtual float getWidth() const  ;  /// Return X
    virtual bool inBounds(float x, float y) const  ;  /// Returns true if within 0 and width and/or height.
    virtual int hitEdge(float x,float y) const    ;	
     

protected:
    float mWidth, mHeight ; 
    

} ;

#endif /* ifndef RECTMAP_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


