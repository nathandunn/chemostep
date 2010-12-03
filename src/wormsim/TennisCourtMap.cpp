#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "Position.hpp"
#include "TennisCourtMap.hpp"

TennisCourtMap::TennisCourtMap(float newWidth,float newHeight,float newTargetX,float newMinValue,float newTargetValue,float newMaxValue) : RectMap(newWidth,newHeight)
,mTargetX(newTargetX)  
,mMinValue(newMinValue) 
,mTargetValue(newTargetValue) 
,mMaxValue(newMaxValue) 
,tempPosition(new Position(newTargetX,newHeight/2.0,0)) 
{
}

float TennisCourtMap::getDistanceToTarget(float x,float y) const 
{
    return fabs( x -  mTargetX) ; 
}



float TennisCourtMap::getTargetX() const 
{
    return mTargetX ; 
}




double TennisCourtMap::getValue(double xPos,double yPos) const  
{
    if( xPos < mTargetX){
        return  (    (mTargetValue - mMinValue)/ (mTargetX - 0 ) * xPos + mMinValue   ) ; 
    }
    else{
        return  (    (mMaxValue - mTargetValue )/ (mWidth - mTargetX ) * (xPos-mTargetX) + mTargetValue ) ; 
    }
}


/// Value only changes in the X direction.
double TennisCourtMap::getValue(Position* newPosition) const
{
    return getValue(newPosition->getX(),newPosition->getY()) ; 
}

void TennisCourtMap::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<map type=\"tenniscourtmap\">" << endl ;
  addSpacer(s) ; 
  *s << "<width value=\"" << mWidth << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<height value=\"" << mHeight << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<targetwidth value=\"" << mTargetX << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<min  value=\"" << mMinValue << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "<target value=\"" << mTargetValue << "\"/>" << endl ;
  addSpacer(s,-1) ; 
  *s << "<max value=\"" << mMaxValue << "\"/>" << endl ;
  addSpacer(s) ; 
  *s << "</map>" << endl ;

}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


