
#include <cmath>
#include <sys/time.h>
#include <limits.h>
#include <iostream>
using std::cout ; 
using std::ostream ; 
using std::endl ; 

#include "SharpTurnMovementModel.hpp"
#include "UniformFwdMovement.hpp"
#include "BaseWorm.hpp"
#include "Worm.hpp"

UniformFwdMovement::UniformFwdMovement( float newLeftBias, float newRightBias ,float newVelocity){
    setLeftBias(newLeftBias) ; 
    setRightBias(newRightBias) ; 
    mVelocity = newVelocity ; 
}


void UniformFwdMovement::move(BaseWorm* aWorm ){

    // get a random angle between thresholdAngle and pi + thresholdAngle 
    // (or -thresholdAngle) 
    mDeltaTheta =   (((rand()/(float) RAND_MAX) * (rightBias+leftBias)) - leftBias) * M_PI/((float)180)   ;    
    
    // multiple times the ratio
    aWorm->setTheta(  aWorm->getTheta()+ mDeltaTheta ) ; 

    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;   // 3. set mDeltaX based on velocity and theta
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   // 3. set mDeltaY based on velocity and theta
    aWorm ->setPosition((mDeltaX+aWorm->getX()), (mDeltaY+aWorm->getY())) ; // steps 4 and 6

}

void UniformFwdMovement::toXML(ostream *s)  
{
    *s << "<movementmodel type=\"uniformfwdmovementmodel\">" << endl ; 
    *s << "\t<velocity value=\"" << velocity << "\">" << endl ; 
    *s << "\t<leftbias value=\"" << leftBias << "\">" << endl ; 
    *s << "\t<rightbias value=\"" << rightBias << "\">" << endl ; 
    *s << "</movementmodel>" << endl ; 
}



