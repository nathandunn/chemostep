#ifndef SIMPLE_WORM_HPP_
#  define SIMPLE_WORM_HPP_

#include <iostream>
using std::ostream ; 

#include "UniformNetBehaviorTemplate.hpp"
#include "MovementModelTemplate.hpp"
class OneWormMapSpace; 
class BehaviorModel; 
class MovementModel ; 
class Position ; 
class BlitzLiveNet ; 
class RectMap ; 

#include "BaseWorm.hpp"

/** Description:  Class Worm.
 *
 */
class SimpleWorm : public BaseWorm {


public:
    SimpleWorm(SimpleWorm* newWorm) ; 
    SimpleWorm(OneWormMapSpace* newSpace) ; 
    virtual void move() ; 
    
    // get value
    virtual float getValue() const ; 

    // get/set position 
    virtual float getX() const ; 
    virtual float getY() const ; 
    virtual Position* getPosition() const ; 
    virtual void setPosition(float xPos,float yPos) ; 
    virtual void movePosition(float xDelta,float yDelta) ; 
    virtual void  setPosition(float newX, float newY,float newTheta) ; 
    virtual void  setPosition(Position* newPosition) ; 

    // get/set velocity
    virtual void  setVelocity(float newVelocity) {
        // unused
    }; 
    virtual float getVelocity() ; 

    // get/set died
    virtual void setDied(bool newDied) { 
        // unused 
    }; 

    // get/set theta
    virtual void setTheta(float newTheta) ; 
    virtual float getTheta() const ; 

    // get/set velocities
    virtual float getForwardVelocity() ;  
    virtual float getTurnVelocity() ;
    virtual void  setForwardVelocity(float newVelocity) ;  
    virtual void  setTurnVelocity(float newVelocity) ;

    // set movement models
    virtual void  setForwardMovementModel(MovementModelTemplate<SimpleWorm> *newModel) ; 
    virtual MovementModelTemplate<SimpleWorm>* getForwardMovementModel() ; 
    virtual void  setTurningMovementModel(MovementModelTemplate<SimpleWorm> *newModel) ; 
    virtual MovementModelTemplate<SimpleWorm>* getTurningMovementModel() ; 
    virtual void  setBounceModel(MovementModelTemplate<SimpleWorm> *newModel) ; 
    virtual MovementModelTemplate<SimpleWorm>* getBounceModel() ; 

    // set behavior model
    virtual void  setBehaviorModel(UniformNetBehaviorTemplate<SimpleWorm>* behaviorModel) ; 
    virtual UniformNetBehaviorTemplate<SimpleWorm>* getBehaviorModel() ; 
//    virtual int   getBehaviorState() ; 

    virtual OneWormMapSpace* getMapSpace() ; 
    virtual int hitEdge() const ; 
    virtual bool hitEdge(int edgeType ) const ; 
    virtual void toXML(ostream *s) ; 
    SimpleWorm& operator=(SimpleWorm &rhs);

protected:
    // state variables
    float mX, mY, mTheta ; 

    // behavior model
    UniformNetBehaviorTemplate<SimpleWorm>* mBehaviorModel; 

    // movement models
    MovementModelTemplate<SimpleWorm>* mForwardMovementModel; 
    MovementModelTemplate<SimpleWorm>* mTurnMovementModel; 
    MovementModelTemplate<SimpleWorm>* mBounceMovementModel; 

    // collection reference
    OneWormMapSpace* mMapSpace ; 
    RectMap* mLocalMap ; /// Local reference of the map.

   

} ;

#endif /* ifndef WORM_H */

