
#ifndef SharpTurnMovementModel_h
#define SharpTurnMovementModel_h

#include <cmath>
#include <cstdlib>
#include <sys/time.h>

#include "PirouetteMovementModel.hpp"

class BaseWorm ; 

class SharpTurnMovementModel:  public PirouetteMovementModel{

	public:
		SharpTurnMovementModel( float newThreshold=0,float newVelocity=0) ;
		virtual void move(BaseWorm* aWorm)   ;
        virtual void setThresholdAngle( float newThreshold ) ;  
        virtual float getThresholdAngle() { return mThresholdAngle*180.0 / M_PI ; }
        virtual void toXML(ostream *s)  ; 
	private:
        float mThresholdAngle ; 
};
#endif

