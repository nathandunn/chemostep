
#ifndef RandomBehaviorModel_h
#define RandomBehaviorModel_h

#include "BehaviorModel.hpp"

class RandomBehaviorModel : public BehaviorModel {

	public:
		RandomBehaviorModel() ; 
		virtual int getBehavior() ; 	
		virtual char* getBehaviorModel() ; 	
		virtual float getProbability() ; 	
		virtual void toXML(ostream *s) ; 

    private:
        double behaviorVar ;
} ;

#endif
