
#include <math.h>

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 


template <class T> 
StraightFwdMovementTemplate<T>::StraightFwdMovementTemplate( float newVelocity) : MovementModelTemplate<T>(newVelocity)
{
}



template <class T> 
void StraightFwdMovementTemplate<T>::move(T* aWorm)   
{
    float theta = aWorm->getTheta() ; 
    aWorm ->movePosition( mVelocity * cos(theta)
        , mVelocity * sin(theta)
        ) ; // steps 4 and 6

}

template <class T> 
void StraightFwdMovementTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodel type=\"straightfwdmovementtemplate\">" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<velocity value=\"" << mVelocity << "\"/>" << endl ; 
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


