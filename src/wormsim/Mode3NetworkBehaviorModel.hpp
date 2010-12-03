
#ifndef Mode3NetworkBehaviorModel_h
#define Mode3NetworkBehaviorModel_h

#include "BlitzNet.hpp"
#include "NetworkBehaviorModel.hpp"
#include "Worm.hpp"

class Worm ; 

class Mode3NetworkBehaviorModel : public NetworkBehaviorModel {

	public:
		Mode3NetworkBehaviorModel()  ; 	
		Mode3NetworkBehaviorModel(Worm* newWorm, BlitzNet* newNet,double newNoise,double lowThresh,double highThresh,double newPirProbForwardState, double newPirProbPirouetteState, double newPirProbMiddleState) ; 
		virtual int getBehavior() ; 	
		virtual char* getBehaviorModel() ; 	
		virtual void toXML(ostream *s) ; 

    protected:
        double pirProbMiddleState ; 

} ;

#endif
