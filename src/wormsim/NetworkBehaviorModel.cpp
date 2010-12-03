
#include <sys/time.h>
#include <limits.h>
#include <blitzdefs.hpp>

#include "Worm.hpp"
#include "BlitzNet.hpp"
#include "NetworkBehaviorModel.hpp"

class Worm ; 


/*  ***********************************************************************************
    Constructor */
   
//! Insert description here
/*  *********************************************************************************** */
NetworkBehaviorModel::NetworkBehaviorModel(Worm* newWorm , BlitzNet*  newNet,double newNoise,double newLowThresh,double newHighThresh ,double newPirProbForwardState, double newPirProbPirouetteState ){
    struct timeval t ; 
    gettimeofday(&t,0) ; 
	srand(t.tv_sec) ; 
    currentBehavior = FORWARD ;  
	worm = newWorm ; 
	net = new BlitzNet(newNet) ; 
	lowThresh = newLowThresh ; 
	highThresh = newHighThresh ; 
    noise = newNoise ; 
    pirProbForwardState = newPirProbForwardState ; 
    pirProbPirouetteState = newPirProbPirouetteState ; 
}

/*  ***********************************************************************************
    getProbability() */
   
//! Insert description here
/*  *********************************************************************************** */
float NetworkBehaviorModel::getProbability(){
    Vector *vmem = net->getNeurons() ; 
 // return (*vmem)(net->size()-(1)) ; 
    return (*vmem)(net->getNumNeurons()-(1)) ; 
}


/*  ***********************************************************************************
    getBehavior() */
   
//! Insert description here
/*  *********************************************************************************** */
int NetworkBehaviorModel::getBehavior(){
    
    // cout << "worm value: " << worm->getValue() << endl ; 
    // double netValue = net->evalPoint(worm->getValue()) ; 
    
    double netValue = 1.0 ;  // CHANGE TO REAL VALUE!!!
    // cout << "net value: " << netValue << endl ; 

    float randomVal =   0.5*rand()/((float) RAND_MAX) +0.25 ; 
    float behaviorVal =  0 ; 

    if(netValue>highThresh){
        // cout << "low turn prob" << endl ; 
	behaviorVal = FWD_VAL ;
	
    }else 
	if(netValue< lowThresh){
         // cout << "high turn prob" << endl ; 
	    behaviorVal = PIR_VAL ;
	    
	}else{
            // cout << "resting prob" << endl ; 
	    behaviorVal =  randomVal ; 
	}
        
    behaviorVal = behaviorVal*(1-noise)+randomVal*(noise) ; 
    
    // cout << "behaviorVal: " << behaviorVal << endl ; 
    // cout << "noise: " << noise << endl ; 
    
    // the pirouete value is 0.5 and the forward value is 0
    randomVal = (rand()/((float) RAND_MAX)) ;
    
    if(behaviorVal<(PIR_VAL)){
        // cout << "fwd" << endl ; 
	currentDecision = FORWARD ;
	
        if((randomVal + pirProbForwardState )>1.0){
	    currentBehavior = SHARP_TURN_50 ;
	    
        }else{
	    currentBehavior = FORWARD ; 
        }
	
    }else{
        // cout << "turn" << endl ; 
	currentDecision = SHARP_TURN_50;
	
        if((randomVal + pirProbPirouetteState)>1.0){
	    currentBehavior = SHARP_TURN_50 ;
	    
        }else{
	    currentBehavior = FORWARD ; 
        }
    }
    
    return currentBehavior ; 
}


/*  ***********************************************************************************
    NetworkBehaviorModel() */
   
//! Insert description here
/*  *********************************************************************************** */
NetworkBehaviorModel::NetworkBehaviorModel() {
    noise = 0 ; 
    lowThresh = 0 ; 
    highThresh = 1 ; 
}


/*  ***********************************************************************************
    getBehaviorModel() */
   
//! Insert description here
/*  *********************************************************************************** */
char* NetworkBehaviorModel::getBehaviorModel(){
    return "NETWORK" ; 
}

/*  ***********************************************************************************
    resetNetwork() */
   
//! Insert description here
/*  *********************************************************************************** */
void NetworkBehaviorModel::resetNetwork(){
    net->reset() ; 
}

