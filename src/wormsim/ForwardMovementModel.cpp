
#include <math.h>
#include <iostream>
using std::ostream ; 
using std::endl ; 

#include "ForwardMovementModel.hpp"
#include "BaseWorm.hpp"

void ForwardMovementModel::move(BaseWorm* aWorm ){

	// 1. theta doesn't change, no turn

	// 2. set to a constant velocity from this velocity

	// 3. set dX and dY based on velocity and theta
	mDeltaX = mVelocity * cos(aWorm->getTheta()) ;
	mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   

	// steps 4 and 6
   	aWorm ->setPosition((mDeltaX+aWorm->getX()), (mDeltaY+aWorm->getY())) ; 
}


void ForwardMovementModel::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodel type=\"forwardmovementmodel\">" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<velocity value=\"" << mVelocity << "\">" << endl ; 
    addSpacer(s) ; 
    *s << "</movementmodel>" << endl ; 
}


