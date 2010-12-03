#ifndef UNIFORMFWDMOVEMENTTEMPLATE_HPP_
#  define UNIFORMFWDMOVEMENTTEMPLATE_HPP_

#include <iostream>
using std::ostream ; 

#include "MovementModelTemplate.hpp"

template <class T> 
class UniformFwdMovementTemplate : public MovementModelTemplate<T> {

    public:
		// set in degrees and converted to radians
		UniformFwdMovementTemplate( float leftBias, float rightBias,float newVelocity) ;
		virtual void move(T* aWorm)   ;
		virtual float getLeftBias() { return mLeftBias ; }  
		virtual float getRightBias() { return mRightBias ; }  
		virtual void setLeftBias(float newLeftBias) {
		  mLeftBias = newLeftBias ; 
		}  
		virtual void setRightBias(float newRightBias) { 
		  mRightBias = newRightBias ; 
		}
        virtual void toXML(ostream *s)  ; 

	protected:
        float mLeftBias ; 
        float mRightBias ; 

} ;

#include "UniformFwdMovementTemplate.cpp" 

#endif /* ifndef UNIFORMFWDMOVEMENTTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


