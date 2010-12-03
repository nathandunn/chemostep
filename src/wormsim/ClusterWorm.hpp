
#ifndef _ClusterWorm_hpp
#define _ClusterWorm_hpp

#include <string>
using std::string ; 

#include "Worm.hpp"

class MovementModel ; 
class MapSpace ; 

class ClusterWorm : public Worm {

public:	
	ClusterWorm(MapSpace* newSpace, float newX, float newY,float newTheta , float velocity ,float newLeftBias=0,float newRightBias=0, float newClusterCorrelation = 0  ) ; 
//    virtual	int move() ;
    virtual	float getValue()  ; 

private:
    float clusterCorrelation ; 
    
} ;

#endif

