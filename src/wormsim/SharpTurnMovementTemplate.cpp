/*
 * $Id$
 */

#include <math.h>

#include <iostream>
using std::cout ; 
using std::endl ; 


template <class T> 
SharpTurnMovementTemplate<T>::SharpTurnMovementTemplate( float newThreshold,float newVelocity) : MovementModelTemplate<T>(newVelocity)

{
    setThresholdAngle(newThreshold) ; 
}

template <class T> 
void SharpTurnMovementTemplate<T>::move(T* aWorm)   
{
    double theta =  aWorm->getTheta() +  mThresholdAngle + (2.0* ( M_PI - mThresholdAngle )) * (rand() * INVS_RAND_MAX )  ; // 1. for now, let's get a random theta
     
//    cout << "mThresholdAngle[" << mThresholdAngle << "] deltaTheta[" << (2.0*(M_PI-mThresholdAngle))*(rand()*INVS_RAND_MAX) << "]" << endl ;   
//    cout << "theta: " << theta << endl ; 

    if(theta > 2.0 * M_PI){
        theta -= 2.0 *M_PI ;
    }
    else
    if(theta < 0.0 ){
        theta += 2.0 *M_PI ;
    }
    aWorm->setTheta(theta) ; 

    aWorm->movePosition( 
        mVelocity * cos(theta) 
        , mVelocity * sin(theta) 
        ) ; 

}

template <class T> 
void SharpTurnMovementTemplate<T>::setThresholdAngle( float newThresholdAngle ) 
{
    mThresholdAngle =  newThresholdAngle * M_PI / 180.0 ; 
}

template <class T> 
void SharpTurnMovementTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodel type=\"sharpturnmovementtemplate\">" << endl ; 
    addSpacer(s) ; 
    *s << "<velocity value=\"" << mVelocity << "\"/>" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<threshold value=\"" << mThresholdAngle << "\"/>" << endl ; 
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


