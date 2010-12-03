
#ifndef _ForwardBehaviorModel_hpp_
#define _ForwardBehaviorModel_hpp_

#include "BehaviorModel.hpp"

class ForwardBehaviorModel : public BehaviorModel {

	public:
		ForwardBehaviorModel() ; 
		virtual int getBehavior() ; 	
		virtual char* getBehaviorModel() ; 	
		virtual float getProbability() { return (float) 0.0 ; }  
		virtual void toXML(ostream *s) ; 
} ;

#endif
