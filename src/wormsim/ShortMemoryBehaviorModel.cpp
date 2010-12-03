// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--dev--1.4.2--patch-1/src/wormsim/ShortMemoryBehaviorModel.cpp"
// LAST MODIFICATION: "Wed, 07 Jul 2004 16:18:25 -0700 (ndunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ShortMemoryBehaviorModel.cpp,v 1.3 2002/05/31 00:17:19 ndunn Exp $



#include <cstdlib>
#include <cmath>
#include <math.h>  // to include M_PI
#include <sys/time.h>
#include <limits.h>

#include "ShortMemoryBehaviorModel.hpp" 


ShortMemoryBehaviorModel::ShortMemoryBehaviorModel(Worm* newWorm,float newNoise){
	
   struct timeval t ; 
   gettimeofday(&t,0) ; 
	srand(t.tv_sec) ; 

    noise = newNoise  ;
    worm = newWorm ; 
    currentBehavior = FORWARD ;  
}

void ShortMemoryBehaviorModel::setNoise(float newNoise){
	noise = newNoise ; 
}

float ShortMemoryBehaviorModel::getProbability(){
	return behaviorVal ; 
}


int ShortMemoryBehaviorModel::getBehavior(){
	float randomVal =   0.5*rand()/((float) RAND_MAX) +0.25 ; 
	float newConc = worm->getValue() ; 
    behaviorVal = 0 ; 
    if(newConc>prevConc){
	    behaviorVal = FWD_VAL ; 
    }else{
	    behaviorVal = PIR_VAL ; 
    }

//    cout << "new value: " << newConc << " old value: " << prevConc << endl ; 
	prevConc = newConc ; 
  
    behaviorVal = behaviorVal*(1-noise)+randomVal*(noise) ; 
//   cout << "worm: "<< worm->getName() << " val: "  << behaviorVal  << "at: " << worm->getX() << " " << worm->getY() <<  endl ; 	

   // the pirouete value is 0.5 and the forward value is 0
    if(behaviorVal<(PIR_VAL)){
	    currentBehavior = FORWARD ; 
	}else{
//        currentBehavior = PIROUETTE; 
	    currentBehavior = SHARP_TURN_50 ; 
	}

	return currentBehavior ; 
}


char* ShortMemoryBehaviorModel::getBehaviorModel(){
    return "SHORT_MEMORY" ; 
}




