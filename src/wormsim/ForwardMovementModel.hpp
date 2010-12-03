
#ifndef ForwardMovementModel_h
#define ForwardMovementModel_h


#include "MovementModel.hpp"

class BaseWorm ; 

class ForwardMovementModel:  public MovementModel{

	public:
		ForwardMovementModel() {}; 
		
		// move the worm forward
		virtual void move(BaseWorm* aWorm)   ;
        virtual void toXML(ostream *s)  ; 

};

#endif

