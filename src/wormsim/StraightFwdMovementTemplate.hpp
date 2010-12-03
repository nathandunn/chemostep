#ifndef UNIFORMFWDMOVEMENTTEMPLATE_HPP_
#  define UNIFORMFWDMOVEMENTTEMPLATE_HPP_

#include <iostream>
using std::ostream ; 

#include "MovementModelTemplate.hpp"

template <class T> 
class StraightFwdMovementTemplate : public MovementModelTemplate<T> {

    public:
		// set in degrees and converted to radians
		StraightFwdMovementTemplate( float newVelocity) ;
		virtual void move(T* aWorm)   ;
        virtual void toXML(ostream *s)  ; 


} ;

#include "StraightFwdMovementTemplate.cpp" 

#endif /* ifndef UNIFORMFWDMOVEMENTTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


