// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.4--patch-1/src/petriapp/ShortMemoryBehaviorModel.hpp"
// LAST MODIFICATION: "Wed, 19 May 2004 12:22:03 -0700 (nathandunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: ShortMemoryBehaviorModel.h,v 1.3 2002/05/31 00:17:19 ndunn Exp $

#ifndef ShortMemoryBehaviorModel_hpp_
#define ShortMemoryBehaviorModel_hpp_

#include "BehaviorModel.hpp"
#include "Worm.hpp"

class ShortMemoryBehaviorModel : public BehaviorModel {

	public:
		ShortMemoryBehaviorModel(Worm* newWorm,float newNoise = 0 ) ; 
		ShortMemoryBehaviorModel() ; 
		virtual int getBehavior() ; 	
        virtual void setNoise(float newNoise) ; 
		virtual char* getBehaviorModel() ; 	
		virtual float getProbability() ; 	

	protected:
        // noise goes from 0 to 1, whith 0 indicating no noise
        // and 1 being totally random
        float noise ; 
        float prevConc ; 
        Worm* worm ; 

    private:
	     float behaviorVal  ; 
} ;

#endif


