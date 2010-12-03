
#ifndef PirouetteMovementModel_h
#define PirouetteMovementModel_h

#include <cmath>
#include <cstdlib>
#include <sys/time.h>

#include "MovementModel.hpp"

class BaseWorm ; 

class PirouetteMovementModel:  public MovementModel{

	public:
		PirouetteMovementModel() {}; 
		virtual void move(BaseWorm* aWorm)   ;
		virtual void setVelocity(float newVelocity) { velocity = newVelocity; }  ;
		virtual float getVelocity()  ; 

	protected:
        float velocity ;
};
#endif

