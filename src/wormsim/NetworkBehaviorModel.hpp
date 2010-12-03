
#ifndef NetworkBehaviorModel_h
#define NetworkBehaviorModel_h

#include "BlitzNet.hpp"
#include "BehaviorModel.hpp"
#include "Worm.hpp"

class Worm ; 

class NetworkBehaviorModel : public BehaviorModel {

	public:
		NetworkBehaviorModel()  ; 	
		NetworkBehaviorModel(Worm* newWorm, BlitzNet* newNet,double newNoise,double lowThresh,double highThresh,double newPirProbForwardState, double newPirProbPirouetteState) ; 
		virtual int getBehavior() ; 	
        virtual int getCurrentBehavior(){  return currentBehavior ; } ; 
		virtual char* getBehaviorModel() ; 	
		virtual void resetNetwork() ; 
		virtual float getProbability() ; 	

	protected:
		BlitzNet* net ; 
		Worm* worm; 
		float lowThresh ; 
		float highThresh ; 
        // noise goes from 0 to 1, whith 0 indicating no noise
        // and 1 being totally random
        float noise ; 


} ;

#endif
