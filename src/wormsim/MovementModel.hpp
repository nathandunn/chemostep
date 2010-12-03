
#ifndef MovementModel_hpp_
#define MovementModel_hpp_

#include <iostream>
using std::ostream ; 

#include <XmlRenderable.hpp>


class BaseWorm ; 
/**
*
*  Movement coincides with 6 steps.
*  1.  set Theta (possibly with dTheta) 
*  2.  set Velocity (possibly with dVelocity) 
*  3.  set dX based on Velocity and Theta
*  4.  set XPos (possibly with dXPos) 
*  5.  set dY based on Velocity and Theta
*  6.  set YPos (possibly with dYPos) 
*
*  Here, we also see that the worms have no mass.  
*/
class MovementModel : public XmlRenderable {
	
	public:
        virtual void move(BaseWorm* aWorm) = 0   ;
		virtual void setVelocity(float newVelocity) { mVelocity = newVelocity ; }  
		virtual float getVelocity() { return mVelocity  ; }

	protected:
        float mVelocity ;
        float mDeltaX,mDeltaY,mDeltaTheta ; 

};

#endif

