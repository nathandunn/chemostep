
// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/PETRIE_2/source/ClusterWorm.cpp"
// LAST MODIFICATION: "Mon, 18 Nov 2002 00:17:45 -0800 (ndunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ClusterWorm.cpp,v 1.7 2002/11/18 07:53:34 ndunn Exp $

#include <iostream.h>
#include "ClusterWorm.hpp"


ClusterWorm::ClusterWorm(MapSpace* newSpace, float newX, float newY,float newTheta , float velocity ,float newLeftBias,float newRightBias, float newClusterCorrelation ) : Worm(newSpace,newX,newY,newTheta,velocity,newLeftBias,newRightBias) {
		clusterCorrelation = newClusterCorrelation ; 
    }



float ClusterWorm::getValue()  {
//    cout << "get cluster" << endl ; 
   float aValue = 0.0 ; 
   aValue = aSpace->getMapValue(xPos,yPos)  ; 
//   aValue += (clusterCorrelation) / ((double) aSpace->getSumLinWormDistance(getWormNumber())) ; 
   aValue += (clusterCorrelation) / ((double) aSpace->getSumLinWormDistance(getWormNumber())) ; 
//   if(getWormNumber()==0){
//       cout << "a sample clutser value " << aValue << endl ; 
//   }
   return aValue ; 
}

//int ClusterWorm::move(){
//    if(wormSimState == WORM_RUNNING){ 
//		++stepsRun ; 
//        int behavior = behaviorModel->getBehavior();
//        if(behavior==BehaviorModel::FORWARD){
//            forwardMovementModel->move(this) ; 			
//        }else
//        if(behavior==BehaviorModel::SHARP_TURN_50){
//            turnMovementModel->move(this) ; 			
//        }else
//        if(behavior==BehaviorModel::REVERSAL){
//            cout << "doing a REVERSAL behavior" << endl ; 
//        }
//        else{
//            cout <<" another behavior" << endl ; 
//        }
//        
//        if(hitEdge()==true){
//			wormSimState = WORM_FINISHED ; 
//			died = true  ; 
//        }
//
//
//		// get worm stats
//		getWormStats() ; 
//
//    }
//    return wormSimState ; 
//    
//}

