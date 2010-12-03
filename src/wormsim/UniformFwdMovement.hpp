
#ifndef UniformFwdMovement_h
#define UniformFwdMovement_h

#include <cmath>
#include <cstdlib>
#include <sys/time.h>


#include "PirouetteMovementModel.hpp"

class BaseWorm ; 

class UniformFwdMovement:  public PirouetteMovementModel{

	public:
		// set in degrees and converted to radians
		UniformFwdMovement( float leftBias=0, float rightBias=0,float newVelocity=0) ;
		virtual void setLeftBias(float newLeftBias) {
		 leftBias = newLeftBias ; 
		}  
		virtual void setRightBias(float newRightBias) { 
		 rightBias = newRightBias ; 
		}
		virtual float getLeftBias() { return leftBias ; }  
		virtual float getRightBias() { return rightBias ; } ; 
		virtual void move(BaseWorm* aWorm)   ;
        virtual void toXML(ostream *s)  ; 

	protected:
        float leftBias; 
        float rightBias; 
};
#endif

