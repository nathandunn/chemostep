

#ifndef BehaviorModel_hpp_
#define BehaviorModel_hpp_

#include <iostream>
using std::ostream ; 
using std::endl ; 

#include "XmlRenderable.hpp" 


/*
*
*  This is the abstract class that gives the rest of the behaviors.
* 
*  The behavior model is set up in order to render a turning decision.   
*  Based on that decision it will turn based on the turning probability for that
*  decision.
*
*
*/
class BehaviorModel : public XmlRenderable {
	public:
		virtual int getBehavior() = 0  ; 	
		virtual int getCurrentBehavior() { return currentBehavior ; }   ; 	
		virtual int getCurrentDecision() { return currentDecision ; }   ; 	
		virtual float getProbability() = 0; 	
        virtual void setPirouetteProbabilityForwardState(double newProbState){
			pirProbForwardState = newProbState ; 
        }
        virtual void setPirouetteProbabilityPirouetteState(double newProbState){
			pirProbPirouetteState = newProbState ; 
        }

        
		static const float FWD_VAL = 0 ; 
		static const float PIR_VAL = 0.5 ; 
		static const float MID_VAL = 0.25 ; 
		static const char* DEC_FWD  ; 
		static const char* DEC_PIR  ; 
        static const int FORWARD = 0 ; 
        static const int PIROUETTE = 1 ; 
        static const int REVERSAL = 2 ; 
        static const int SHARP_TURN_50 = 3 ; 
        static const int MIDDLE = 4 ; 

	protected:
		int currentBehavior ; 
		int currentDecision ; 
		double pirProbForwardState; 
		double pirProbPirouetteState; 

} ;

#endif
