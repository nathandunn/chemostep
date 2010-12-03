
#include <math.h>

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 


template <class T> 
UniformFwdMovementTemplate<T>::UniformFwdMovementTemplate( float newLeftBias, float newRightBias,float newVelocity) : MovementModelTemplate<T>(newVelocity)
,mLeftBias(newLeftBias)
,mRightBias(newRightBias)
{
}



template <class T> 
void UniformFwdMovementTemplate<T>::move(T* aWorm)   
{
    // get a random angle between thresholdAngle and pi + thresholdAngle 
    // (or -thresholdAngle) 
    mDeltaTheta =   (((rand()/(float) RAND_MAX) * (mRightBias+mLeftBias)) - mLeftBias) * M_PI/((float)180)   ;    
     
    // multiple times the ratio
    aWorm->setTheta(aWorm->getTheta()+mDeltaTheta) ; 

    mDeltaX = mVelocity * cos(aWorm->getTheta()) ;   // 3. set mDeltaX based on velocity and theta
    mDeltaY = mVelocity * sin(aWorm->getTheta()) ;   // 3. set mDeltaY based on velocity and theta
    aWorm ->setPosition((mDeltaX+aWorm->getX()), (mDeltaY+aWorm->getY())) ; // steps 4 and 6

}

template <class T> 
void UniformFwdMovementTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodel type=\"uniformfwdmovementtemplate\">" << endl ; 
    addSpacer(s) ; 
    *s << "<velocity value=\"" << mVelocity << "\"/>" << endl ; 
    addSpacer(s) ; 
    *s << "<leftbias value=\"" << mLeftBias << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<rightbias value=\"" << mRightBias << "\"/>" << endl ; 
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

// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


