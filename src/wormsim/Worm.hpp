
#ifndef Worm_hpp
#define Worm_hpp

#include <string>
using std::string ; 

#include <iostream>
using std::ostream ; 

#include <utility>
using std::pair; 

#include "MapSpace.hpp"
#include "BehaviorModel.hpp"
#include "MovementModel.hpp"
#include "BaseWorm.hpp"

class MovementModel ; 
class MapSpace ; 

class Worm : public BaseWorm {

public:	
    Worm(MapSpace* newSpace) ; 
    Worm(MapSpace* newSpace, float newX, float newY,float newTheta , float velocity ,float newLeftBias=0,float newRightBias=0) ; 
    virtual void  clearStats() ; 
    virtual bool  inCenter() ; 
    virtual float getX() const {  return xPos ; } ; 
    virtual float getY() const {  return yPos ; } ;
    virtual MapSpace* getMapSpace() { return aSpace ; }  
    virtual float getTheta() const {  return theta; } ; 
    virtual float getValue()  const ; 
    virtual float getVelocity() {  return velocity ; } ; 
    virtual void  setVelocity(float newVelocity){ velocity = newVelocity ; } ; 
    virtual void  setForwardMovementModel(MovementModel *newModel){ forwardMovementModel = newModel ;  } ; 
    virtual void  setTurningMovementModel(MovementModel *newModel){ turnMovementModel = newModel ;  } ; 
    virtual void  setBounceModel(MovementModel *newModel){ bounceMovementModel = newModel ;  } ; 
    virtual void  setForwardVelocity(float newVelocity) ;  
    virtual void  setPirouetteVelocity(float newVelocity) ;
    virtual float getForwardVelocity() ;  
    virtual float getPirouetteVelocity() ;
    virtual void  setTheta(float newTheta) {  theta = newTheta ; } ; 
    virtual int   move() ;
    virtual double getDistanceFromCenter() ;
    virtual void  setPosition(float newX, float newY) ; 
    virtual void  setPosition(float newX, float newY,float newTheta) ; 
    virtual void  setBehaviorModel(BehaviorModel* behaviorModel) ; 
    virtual BehaviorModel* getBehaviorModel() ; 
    virtual string getName(){ return name ; }  
    virtual void  setName(string newName){ name = newName ; }  
    virtual int   getWormNumber(){ return wormNumber ; }  
    virtual void  setWormNumber(int newWormNumber){ wormNumber = newWormNumber ; }  
    virtual float getTurningThreshold() ; 
    virtual void  setTurningThreshold(float degrees ) ;
    const static int WORM_FINISHED ; 
    const static int WORM_RUNNING ; 
    virtual int   getTimeAtCenter(){ return atCenter ; }  
    virtual int   getTimeToCenter(){ return timeToCenter; }  
    virtual bool  getReachedCenter(){ return reachedCenter ; }  
    virtual bool  getDied(){ return died ; }  
    virtual void  setDied(bool isDead){ died = isDead ; } 
    virtual bool  hitEdge() ;   
    virtual double getRunDecisionAverage() { return (double)runDecisionCount/ (double) stepsRun ; }  
    virtual double getMiddleDecisionAverage() { return (double)middleDecisionCount/ (double) stepsRun ; }  
    virtual double getPirouetteDecisionAverage() { return (double)pirouetteDecisionCount/ (double) stepsRun ; }  
    virtual double getRunBehaviorAverage() { return (double)runBehaviorCount/ (double) stepsRun ; }  
    virtual double getSharpTurnBehaviorAverage() { return (double)sharpTurnBehaviorCount/ (double) stepsRun ; }  
    virtual double getProbabilityAverage() ;
    virtual double getAverageConcentrationDiff() ;
    virtual pair<double,double> getPosition() ; 
    virtual void toXML(ostream *s) ; 

protected:
    virtual int getWormStats() ; 
    double prevConc ; 
    double currentConc ; 
    double diffConcTotal ; 
    int stepsRun ; 
    int runDecisionCount  ; 
    int middleDecisionCount ; 
    int pirouetteDecisionCount  ; 
    int runBehaviorCount  ; 
    int sharpTurnBehaviorCount  ; 
    double probabilityCount ; 
    int atCenter  ; 
    int timeToCenter  ; 
    bool reachedCenter ; 
    bool died ; 
    float leftBias ; 
    float rightBias; 
    float xPos ; 
    float yPos ; 
    float theta ; 
    float velocity ; 
    BehaviorModel* behaviorModel ; 
    string name ; 
    MapSpace* aSpace ; 
    MovementModel* forwardMovementModel; 
    MovementModel* turnMovementModel; 
    MovementModel* bounceMovementModel; 
    int wormSimState ; 
    int wormNumber ; 
} ;

#endif

