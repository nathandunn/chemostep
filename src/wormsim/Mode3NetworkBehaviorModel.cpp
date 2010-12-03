
 
#include <sys/time.h>
#include <limits.h>
#include <blitzdefs.hpp>


#include "Worm.hpp"
#include "BlitzNet.hpp"
#include "Mode3NetworkBehaviorModel.hpp"

class Worm ; 

Mode3NetworkBehaviorModel::Mode3NetworkBehaviorModel(Worm* newWorm , BlitzNet*  newNet,double newNoise,double newLowThresh,double newHighThresh ,double newPirProbForwardState, double newPirProbPirouetteState ,double newPirProbMiddleState) : NetworkBehaviorModel(newWorm, newNet,newNoise, newLowThresh, newHighThresh, newPirProbForwardState,newPirProbPirouetteState){
    struct timeval t ; 
    gettimeofday(&t,0) ; 
	srand(t.tv_sec) ; 
    pirProbMiddleState = newPirProbMiddleState ; 
}


int Mode3NetworkBehaviorModel::getBehavior(){

//	cout << "worm value: " << worm->getValue() << endl ; 
//    double netValue = net->evalPoint(worm->getValue()) ; 

    double netValue = 1.0 ; 
//	cout << "net value: " << netValue << endl ; 
	float randomVal =   0.5*rand()/((float) RAND_MAX) +0.25 ; 
	float behaviorVal =  0 ; 
    if(netValue>highThresh){
//cout << "low turn prob" << endl ; 
	    behaviorVal = FWD_VAL ; 
    }else 
	if(netValue< lowThresh){
//cout << "high turn prob" << endl ; 
	    behaviorVal = PIR_VAL ; 
    }else{
//cout << "resting prob" << endl ; 
		behaviorVal =  MID_VAL ; 
	}
  

    behaviorVal = behaviorVal*(1-noise)+randomVal*(noise) ; 

//    cout << "behaviorVal: " << behaviorVal << endl ; 
//    cout << "noise: " << noise << endl ; 
//
//
 
    // the pirouete value is 0.5 and the forward value is 0
    // the mid value is 0.25.  This is a silly way to do this.
    randomVal = (rand()/((float) RAND_MAX)) ; 

    if(behaviorVal==MID_VAL){
	    currentDecision = MIDDLE ; 
        if((randomVal + pirProbMiddleState)>1.0){
//cout << "mid to turn" << endl ; 
			currentBehavior = SHARP_TURN_50 ; 
        }else{
        	currentBehavior = FORWARD ; 
//cout << "mid to fwd" << endl ; 
        }
    }
    else
    if(behaviorVal<(PIR_VAL)){
	    currentDecision = FORWARD ; 
        if((randomVal + pirProbForwardState )>1.0){
//cout << "fwd to turn" << endl ; 
			currentBehavior = SHARP_TURN_50 ; 
        }else{
        	currentBehavior = FORWARD ; 
//cout << "fwd to fwd" << endl ; 
        }
	}else{
	    currentDecision = SHARP_TURN_50; 
        if((randomVal + pirProbPirouetteState)>1.0){
			currentBehavior = SHARP_TURN_50 ; 
//cout << "turn to turn " << endl ; 
        }else{
        	currentBehavior = FORWARD ; 
//cout << "turn to fwd" << endl ; 
        }
	}

	return currentBehavior ; 
}


Mode3NetworkBehaviorModel::Mode3NetworkBehaviorModel() {
    noise = 0 ; 
    lowThresh = 0 ; 
    highThresh = 1 ; 
}


char* Mode3NetworkBehaviorModel::getBehaviorModel(){
    return "MODE3NETWORK" ; 
}

void Mode3NetworkBehaviorModel::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<behaviormodel type=\"mode3networkbehaviormodel\">" << endl ;
  addSpacer(s) ; 
  *s << "<pirprobmiddlestate value=\"" << pirProbMiddleState << "\"" << endl ;
  addSpacer(s) ; 
  *s << "<lowthresh value=\"" << lowThresh << "\"" << endl ;
  addSpacer(s) ; 
  *s << "<highthresh value=\"" << highThresh << "\"" << endl ;
  addSpacer(s,-1) ; 
  *s << "<noise value=\"" << noise << "\"" << endl ;
  addSpacer(s) ; 
  *s << "</behaviormodel>" << endl ;
}



