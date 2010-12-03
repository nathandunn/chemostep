
#include <cmath>
#include <sys/time.h>
#include <limits.h>

#include "PirouetteMovementModel.hpp"
#include "BaseWorm.hpp"

void PirouetteMovementModel::move(BaseWorm* aWorm ){
	//cout <<" moving in a pirouette!!" << endl ; 
	float dX = 0 ; 
	float dY = 0 ; 
	float dTheta = 0 ; 

    // get a random angle between 0 and 2PI
	dTheta = 2.0 * M_PI * (rand() / ((float) RAND_MAX))  ; // 1. for now, let's get a random theta
//	cout << dTheta  << endl ; 
	aWorm->setTheta(aWorm->getTheta()+dTheta) ; 

	aWorm->setVelocity(velocity) ;  // 2. set to a constant velocity
	dX = aWorm->getVelocity() * cos(aWorm->getTheta()) ;   // 3. set dX based on velocity and theta
	dY = aWorm->getVelocity() * sin(aWorm->getTheta()) ;   // 3. set dY based on velocity and theta
   	aWorm ->setPosition((dX+aWorm->getX()), (dY+aWorm->getY())) ; // steps 4 and 6
	
	//cout << "dX: " << dX << endl ; 
	//cout << "dY: " << dY << endl ; 
}

float PirouetteMovementModel::getVelocity()  
{
    return velocity ; 
}




