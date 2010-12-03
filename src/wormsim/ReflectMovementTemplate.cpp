
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 


#include "MovementModelTemplate.hpp"

template <class T>
ReflectMovementTemplate<T>::ReflectMovementTemplate( float newVelocity) : MovementModelTemplate<T>(newVelocity){ }


template <class T>
void ReflectMovementTemplate<T>::move(T* aWorm)   
{
    // get a random angle between thresholdAngle and pi + thresholdAngle 
    // (or -thresholdAngle) 
//    mDeltaTheta = aWorm->getTheta() - (2.0 * M_PI)   ;    
   
//     cout << "ReflectMovementTemplate--PRE-move theta: " << aWorm->getTheta() << endl ;
  
     // if we were going to to this more advanced
	 // 1. get the wall it bounced off against
	 // 2. calculate based on that
	 if(aWorm->getTheta()> M_PI){
	  aWorm->setTheta(aWorm->getTheta() - M_PI) ; 
	 }
	 else{
	  aWorm->setTheta(aWorm->getTheta() + M_PI) ; 
	 }
    

    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;   // 3. set mDeltaX based on velocity and theta
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   // 3. set mDeltaY based on velocity and theta
    aWorm ->setPosition((mDeltaX+aWorm->getX()), (mDeltaY+aWorm->getY())) ; // steps 4 and 6

//     cout << "POST-move X: " << aWorm->getX()  << " Y: " << aWorm->getY() << " theta: " << aWorm->getTheta() << endl ;

}

template <class T>
void ReflectMovementTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodel type=\"reflectmovementtemplate\">" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<velocity value=\""<< mVelocity<< "\"/>" << endl  ; 
    addSpacer(s) ; 
    *s << "</movementmodel>" << endl ; 
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



