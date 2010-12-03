/*
 * $Id$
 */

#include <iostream>
using std::ostream ; 
using std::endl ; 



template <class T> 
DieMovementTemplate<T>::DieMovementTemplate() : MovementModelTemplate<T>()
{
}

template <class T> 
void DieMovementTemplate<T>::move(T* aWorm)   
{
    aWorm->setDied(true) ; 
}


template <class T> 
float DieMovementTemplate<T>::getVelocity()   
{
  return 0.0 ; 
}

template <class T> 
void DieMovementTemplate<T>::toXML(ostream *s)  
{
    addSpacer(s) ; 
    *s << "<movementmodel type=\"diemovementtemplate\">" << endl ; 
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


