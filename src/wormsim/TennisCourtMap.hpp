/*
 * $Id$
 */
#ifndef TENNISCOURTMAP_HPP_
#  define TENNISCOURTMAP_HPP_

#include "RectMap.hpp"

/// This class represents a map that linearly changes over 3 different points, but with only the middle point as the target. 
class TennisCourtMap : public RectMap{

public:
    TennisCourtMap(float newWidth,float newHeight,float newTargetX,float newMinValue,float newTargetValue,float newMaxValue) ; 
    virtual float getTargetX() const  ; 
    virtual double getValue(Position* newPosition) const  ; 
    virtual double getValue(double x,double y) const  ; 
    virtual void toXML(ostream *s) ; 
    virtual float getDistanceToTarget(float x,float y) const ; 

protected:
    float mTargetX ; 
    float mMinValue,mTargetValue,mMaxValue ; 


    Position* tempPosition ; 
    
} ;

#endif /* ifndef TENNISCOURTMAP_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


