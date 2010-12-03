


#include <cstdlib>
#include <cmath>
#include <math.h>  // to include M_PI
#include <sys/time.h>
#include <limits.h>



#include "RandomBehaviorModel.hpp"

float RandomBehaviorModel::getProbability(){
	return behaviorVar ; 
}

int RandomBehaviorModel::getBehavior(){
	behaviorVar =   rand()/((float) RAND_MAX) ; 
//   cout << "var1: "<< behaviorVar  << endl ; 	
	if(behaviorVar<(0.5)){
	    currentBehavior = FORWARD ; 
	}else{
	    currentBehavior = PIROUETTE; 
	}

	return currentBehavior ; 
}

RandomBehaviorModel::RandomBehaviorModel(){
   struct timeval t ; 
   gettimeofday(&t,0) ; 
	srand(t.tv_sec) ; 
   currentBehavior = FORWARD ;  
}

char* RandomBehaviorModel::getBehaviorModel(){
    return "RANDOM" ; 
}

void RandomBehaviorModel::toXML(ostream *s) 
{
  addSpacer(s) ; 
  *s << "<behaviormodel type=\"randombehaviormodel\">" << endl ;
  addSpacer(s) ; 
  *s << "</behaviormodel>" << endl ;
}


