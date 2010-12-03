
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "UniformNetBehaviorTemplate.hpp"
#include "MovementModelTemplate.hpp"
#include "BehaviorValues.hpp"
#include "OneWormMapSpace.hpp"
#include "Position.hpp"
#include "BaseWorm.hpp"
#include "RectMap.hpp"


#include "SimpleWorm.hpp"

SimpleWorm::SimpleWorm(OneWormMapSpace* newSpace) : BaseWorm()
,mMapSpace(newSpace)
,mForwardMovementModel(NULL)
,mTurnMovementModel(NULL)
,mBounceMovementModel(NULL)
{
    mLocalMap = (RectMap*) (newSpace->getMap()) ; 
}

SimpleWorm::SimpleWorm(SimpleWorm* newWorm) : BaseWorm()
,mMapSpace(newWorm->getMapSpace())
{
    mX = newWorm->getX() ; 
    mY = newWorm->getY() ; 
    mTheta = newWorm->getTheta() ; 

    setBehaviorModel( newWorm->getBehaviorModel()  ) ; 
    setForwardMovementModel (  (newWorm->getForwardMovementModel()) ) ; 
    setTurningMovementModel(newWorm->getTurningMovementModel()) ;
    setBounceModel( newWorm->getBounceModel() ) ; 
}

MovementModelTemplate<SimpleWorm>* SimpleWorm::getForwardMovementModel() 
{
    return mForwardMovementModel ; 
}

MovementModelTemplate<SimpleWorm>* SimpleWorm::getTurningMovementModel() 
{
    return mTurnMovementModel ; 
}

MovementModelTemplate<SimpleWorm>* SimpleWorm::getBounceModel() 
{
    return mBounceMovementModel ; 
}

/// Moves a worm, ignoring if the worm is dead or not.  
void SimpleWorm::move() 
{
//        mBehaviorState = mBehaviorModel->getBehavior( );

//                if(hitEdge()){
//                    cout << "hitEdge" << endl; 
//                    mBounceMovementModel->move(this) ; 
//                }
        switch(mBehaviorModel->getBehavior()){
           case BehaviorValues::FORWARD:
               mForwardMovementModel->move(this) ; 
               break ; 
           case BehaviorValues::SHARP_TURN_50:
               mTurnMovementModel->move(this) ; 
               break ; 
           case BehaviorValues::BOUNCE:
               mBounceMovementModel->move(this) ; 
               break ; 
           default:
               cout << "behavior not defined" << endl ; 
               throw "behavior not defined" ; 
               break ; 
        }


}

bool SimpleWorm::hitEdge(int edgeType ) const
{
	return ( hitEdge()==edgeType) ; 
    
}



UniformNetBehaviorTemplate<SimpleWorm>* SimpleWorm::getBehaviorModel() 
{
    return mBehaviorModel ; 
}



SimpleWorm& SimpleWorm::operator=(SimpleWorm &rhs){
  setBehaviorModel(rhs.getBehaviorModel()) ; 
  setForwardMovementModel( rhs.getForwardMovementModel() ) ; 
  setTurningMovementModel(rhs.getTurningMovementModel() ) ; 
  setBounceModel(rhs.getBounceModel() ) ; 

}



/// Returns the edge that was hit.
int SimpleWorm::hitEdge() const
{
    // in bounds, so not hit edge
	return mLocalMap->hitEdge( getX(),getY() ) ; 
}


float SimpleWorm::getValue() const 
{
    return mLocalMap->getValue( mX,mY) ;
}

float SimpleWorm::getX() const
{
    return mX ; 
}

float SimpleWorm::getY() const
{
    return mY ; 
}

Position* SimpleWorm::getPosition() const
{
    return new Position(mX,mY,mTheta) ; 
}

void  SimpleWorm::setPosition(Position* newPosition) 
{
	mX = newPosition->getX() ; 
	mY = newPosition->getY() ; 
	mTheta = newPosition->getTheta() ; 
}

void SimpleWorm::movePosition(float xDelta,float yDelta) 
{
	mX += xDelta ; 
	mY += yDelta ; 
}


void  SimpleWorm::setPosition(float newX, float newY,float newTheta) 
{
	mX = newX ; 
	mY = newY ; 
	mTheta = newTheta ; 

}

void SimpleWorm::setPosition(float xPos,float yPos) 
{
	mX = xPos ; 
	mY = yPos ; 
}


float SimpleWorm::getTheta() const
{
    return mTheta ; 
}


void SimpleWorm::setTheta(float newTheta) 
{
    mTheta = newTheta ; 
}

float SimpleWorm::getForwardVelocity() 
{
    return mForwardMovementModel->getVelocity() ; 
}

float SimpleWorm::getTurnVelocity() 
{
    return mTurnMovementModel->getVelocity() ; 
}

void  SimpleWorm::setForwardVelocity(float newVelocity) 
{
    mForwardMovementModel->setVelocity(newVelocity) ; 
}

void  SimpleWorm::setTurnVelocity(float newVelocity) 
{
    mTurnMovementModel->setVelocity(newVelocity) ; 
}

void  SimpleWorm::setForwardMovementModel(MovementModelTemplate<SimpleWorm> *newModel) 
{
    mForwardMovementModel = newModel ; 
}

void  SimpleWorm::setTurningMovementModel(MovementModelTemplate<SimpleWorm> *newModel) 
{
    mTurnMovementModel = newModel ; 
}

void  SimpleWorm::setBounceModel(MovementModelTemplate<SimpleWorm> *newModel) 
{
    mBounceMovementModel = newModel ; 
}

void  SimpleWorm::setBehaviorModel(UniformNetBehaviorTemplate<SimpleWorm>* behaviorModel) 
{
    mBehaviorModel = behaviorModel  ;
}

//void  SimpleWorm::setVelocity(float newVelocity) 
//{
//    mVelocity = newVelocity ; 
//}
//

float SimpleWorm::getVelocity() {
    cout << "not implemented" << endl ;
    throw "not implemented" ; 
}

//bool SimpleWorm::getDied() 
//{
//    return mDied ; 
//}


OneWormMapSpace* SimpleWorm::getMapSpace() 
{
    return mMapSpace ; 
}


void SimpleWorm::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<simpleworm>" << endl ;
  mBehaviorModel->toXML(s) ; 
  mForwardMovementModel->toXML(s) ; 
  mTurnMovementModel->toXML(s) ; 
  mBounceMovementModel->toXML(s) ; 
  decrementTabCount() ; 
  addSpacer(s) ; 
  // close the XML
  *s << "</simpleworm>" << endl ;

}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */



