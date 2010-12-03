/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 


template <class T>
MovementModelTemplate<T>::MovementModelTemplate(float newVelocity) : 
mVelocity(newVelocity)
{
}


template <class T> 
void MovementModelTemplate<T>::setVelocity(float newVelocity) {
    mVelocity = newVelocity ; 
}

template <class T> 
float MovementModelTemplate<T>::getVelocity() 
{
    return mVelocity ; 
}

template <class T> 
void MovementModelTemplate<T>::move(T* aWorm)   
{
    cout << "trying to move something" << endl ; 
}

template <class T> 
void MovementModelTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s,1) ; 
    *s << "<movementmodeltemplate type=\"movementtemplate\">" << endl ; 
    addSpacer(s,-1) ; 
    *s << "<velocity value=\""<< mVelocity<< "\">" << endl  ; 
    addSpacer(s) ; 
    *s << "</movementmodeltemplate>" << endl ; 
}

const float INVS_RAND_MAX = 1.0 / (float) RAND_MAX ;  


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


