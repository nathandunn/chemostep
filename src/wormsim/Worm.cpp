#include <iostream>
using std::cout ; 
using std::endl ; 

#include <utility>
using std::pair ; 

#include <utility>
using std::pair ; 

#include <math.h>
#include <stdlib.h>

#include "MovementModel.hpp"
#include "Worm.hpp"
#include "Dimension.hpp"
#include "BehaviorModel.hpp"
#include "RandomBehaviorModel.hpp"
#include "UniformFwdMovement.hpp"
#include "ForwardMovementModel.hpp"
#include "SharpTurnMovementModel.hpp"
//#include "TurnAroundMovementModel.hpp"
#include "DieMovementModel.hpp"


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
Worm::Worm(MapSpace* newSpace)  {
    aSpace = newSpace ; 
    clearStats() ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
Worm::Worm(MapSpace* newSpace,float newX, float newY, float newTheta  , float newVelocity, float newLeftBias, float newRightBias )  {
    aSpace = newSpace ; 
    xPos = newX ; 
    yPos = newY ; 
    theta = newTheta ; 
    velocity = newVelocity ; 
    leftBias = newLeftBias ; 
    rightBias = newRightBias ; 
    behaviorModel = new RandomBehaviorModel() ; 
    forwardMovementModel = new UniformFwdMovement(leftBias,rightBias,newVelocity) ; 
    turnMovementModel = new SharpTurnMovementModel(0,newVelocity) ; 
    bounceMovementModel = new DieMovementModel() ; 
    
    clearStats() ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
void Worm::clearStats(){
    
//    prevConc = 0.0 ; 
//    currentConc = 0.0 ; 
//    diffConcTotal = 0.0 ; 
//    stepsRun = 0 ; 
//    runDecisionCount  = 0; 
//    middleDecisionCount = 0 ; 
//    pirouetteDecisionCount  = 0 ; 
//    runBehaviorCount  = 0 ; 
//    sharpTurnBehaviorCount = 0 ; 
//    double probabilityCount ; 
//    int atCenter  ; 
//    int timeToCenter  ; 
//    bool reachedCenter ; 
//    bool died ; 
//    float leftBias ; 
//    float rightBias; 
//    float xPos ; 
//    float yPos ; 
//    float theta ; 
//    float velocity ; 
//    BehaviorModel* behaviorModel ; 
//    string name ; 
//    MapSpace* aSpace ; 
//    MovementModel* forwardMovementModel; 
//    MovementModel* turnMovementModel; 
//    int wormSimState ; 
//    int wormNumber ; 


    wormSimState = Worm::WORM_RUNNING ; 
    name = "bob" ; 
    atCenter = 0 ; 
    timeToCenter = 0 ; 
    reachedCenter = false ; 
    died = false ; 
    runDecisionCount  = 0 ;  
    middleDecisionCount = 0 ;  
    pirouetteDecisionCount  = 0 ;  
    runBehaviorCount  = 0 ;  
    sharpTurnBehaviorCount  = 0 ;  
    stepsRun = 0 ;  
    probabilityCount = 0 ; 
    diffConcTotal = 0 ; 
}


// if the current position is within the center of the mapSpace
// so ask the mapSpace based on the point

/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
bool Worm::inCenter(){
    return aSpace->inCenter(xPos,yPos) ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
void Worm::setTurningThreshold(float degrees){
    (dynamic_cast<SharpTurnMovementModel *> (turnMovementModel)   )-> setThresholdAngle(degrees) ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
float Worm::getTurningThreshold(){
    return (dynamic_cast<SharpTurnMovementModel *> (turnMovementModel))-> getThresholdAngle() ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
void Worm::setBehaviorModel(BehaviorModel* newBehaviorModel){
    behaviorModel = newBehaviorModel ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
BehaviorModel* Worm::getBehaviorModel(){
    return behaviorModel ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
bool Worm::hitEdge(){
    return aSpace->hitEdge(xPos,yPos)  ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
float Worm::getValue() const {
    // cout << "NOT getting cluster" << endl ; 
    return aSpace->getMapValue(xPos,yPos)  ; 
}




/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
void Worm::setPirouetteVelocity(float newVelocity){
    turnMovementModel->setVelocity( newVelocity); 
    bounceMovementModel->setVelocity( newVelocity); 
}


float Worm::getForwardVelocity() 
{
    return forwardMovementModel->getVelocity(); 
}

float Worm::getPirouetteVelocity() 
{
    return turnMovementModel->getVelocity(); 
}



/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
void Worm::setForwardVelocity(float newVelocity){
    forwardMovementModel->setVelocity( newVelocity); 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
double Worm::getAverageConcentrationDiff(){
    return (double) double (diffConcTotal / ((double) stepsRun-1.0)) ;
}

double Worm::getDistanceFromCenter() 
{
    return aSpace->getDistanceFromCenter(xPos,yPos)  ; 
}


/// returns the state of each worm
int Worm::move(){
    
    if(wormSimState == WORM_RUNNING){ 
        ++stepsRun ; 
        int behavior = behaviorModel->getBehavior();
	
        if(behavior == BehaviorModel::FORWARD){
            forwardMovementModel->move(this) ;
        }else
	    if(behavior == BehaviorModel::SHARP_TURN_50){
            turnMovementModel->move(this) ;
	    }else
		if(behavior == BehaviorModel::REVERSAL){
		    cout << "doing a REVERSAL behavior" << endl ;
		} else{
		    cout <<" another behavior" << endl ; 
		}
        
        if(hitEdge() == true){
//             cout << "worm hit edge bouncing" << endl ; 

            // bounce
            bounceMovementModel->move(this) ; 
            if(died==true){
                wormSimState = WORM_FINISHED ; 
            }
        }
		
	// get worm stats
    	getWormStats() ; 
    }

//    cout << "x,y: " << xPos << "," << yPos << " rad: " << aSpace->getDistanceFromCenter(xPos,yPos)  << " val: " << aSpace->getMapValue(xPos,yPos) << endl ;
    
    return wormSimState ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
int Worm::getWormStats(){
    
    if(inCenter()==true){
	++atCenter ; 
	reachedCenter = true ;
	
    }else{
	if(reachedCenter==false){
	    ++timeToCenter ;  
	}
    }
    
    if(stepsRun>0){
        prevConc = currentConc ; 
        currentConc = getValue() ; 
        diffConcTotal += fabs(currentConc - prevConc) ; 
    } 
    
    // get more stats
    int theCurrentDecision = behaviorModel->getCurrentDecision() ; 
    int theCurrentBehavior = behaviorModel->getCurrentBehavior() ;
    
    if(theCurrentBehavior==BehaviorModel::SHARP_TURN_50){
        ++sharpTurnBehaviorCount ;
    } else
	if(theCurrentBehavior==BehaviorModel::FORWARD){
	    ++runBehaviorCount ; 		
	}
    
    
    if(theCurrentDecision==BehaviorModel::FORWARD){
        ++runDecisionCount;
    } else
	if(theCurrentDecision==BehaviorModel::MIDDLE){
	    ++middleDecisionCount ;
	} else
	    if(theCurrentDecision==BehaviorModel::SHARP_TURN_50){
		++pirouetteDecisionCount ; 		
    }
    
    probabilityCount += behaviorModel->getProbability()  ; 
    return 1 ; 
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
double Worm::getProbabilityAverage(){
    return  probabilityCount/(double) stepsRun;
}


/*  ***********************************************************************************
    () */
   
//! Description here.
/*  *********************************************************************************** */
void Worm::setPosition(float x, float y){
    xPos = x ; 
    yPos = y ; 
}

void  Worm::setPosition(float newX, float newY,float newTheta) 
{
    xPos = newX  ; 
    yPos = newY  ; 
    theta = newTheta ; 
}


pair<double,double> Worm::getPosition() 
{
    return pair<double,double>(xPos,yPos) ; 
}


void Worm::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<worm>" << endl ;
  behaviorModel->toXML(s) ; 
  forwardMovementModel->toXML(s) ; 
  turnMovementModel->toXML(s) ; 
  bounceMovementModel->toXML(s) ; 
  addSpacer(s) ; 
  // close the XML
  *s << "</worm>" << endl ;
}



const int Worm::WORM_FINISHED = 1; 
const int Worm::WORM_RUNNING = 2; 





