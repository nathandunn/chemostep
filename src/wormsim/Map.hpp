
#ifndef MAP_HPP_
#  define MAP_HPP_

#include <XmlRenderable.hpp>
#include <float.h>

class Map : public XmlRenderable {

public:
        enum{ NONE, NORTH, SOUTH, EAST, WEST } ;
	    virtual double getValue(double x,double y) const =0  ;	
	    virtual float getHeight() const =0  ;	
	    virtual float getWidth() const =0  ;	
	    virtual bool inBounds(float x,float y) const =0  ;	
        virtual float getDistanceToTarget(float x,float y) const { return DBL_MAX ; }

} ;

#endif /* ifndef MAP_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>

