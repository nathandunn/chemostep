
#include <math.h>
#include <sys/time.h>
#include <limits.h>
#include <iostream>
using std::cout ; 
using std::ostream ; 
using std::endl ; 


#include "SharpTurnMovementModel.hpp"
#include "BaseWorm.hpp"

SharpTurnMovementModel::SharpTurnMovementModel( float threshold,float newVelocity): PirouetteMovementModel(){
    setThresholdAngle(threshold) ; 
    mVelocity = newVelocity ;
}

void SharpTurnMovementModel::setThresholdAngle( float threshold ) {
    mThresholdAngle = threshold * M_PI / 180.0 ; 
}

void SharpTurnMovementModel::move(BaseWorm* aWorm ){

    mDeltaTheta =  mThresholdAngle + (2* ( M_PI - mThresholdAngle )) * (rand() / ((float) RAND_MAX))  ; 
    aWorm->setTheta(aWorm->getTheta()+mDeltaTheta) ; 
    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;  
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   
    aWorm ->setPosition((mDeltaX+aWorm->getX()), (mDeltaY+aWorm->getY())) ; 
    
}

void SharpTurnMovementModel::toXML(ostream *s)  
{
    *s << "<movementmodel type=\"sharpturnmovementmodel\">" << endl ; 
    *s << "<velocity value=\"" << mVelocity << "\">" << endl ; 
    *s << "<threshold value=\"" << mThresholdAngle << "\">" << endl ; 
    *s << "</movementmodel>" << endl ; 
}


