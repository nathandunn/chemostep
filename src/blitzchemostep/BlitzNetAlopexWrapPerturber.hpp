/**
* BlitzNetAlopexWrapPerturber header file. 
* Jeremiah Sullenger, version 0.1 6/22/04
*/

#ifndef BLITZNETALOPEXWRAPPERTURBER_H
#define BLITZNETALOPEXWRAPPERTURBER_H

#include "BlitzNetAlopexPerturber.hpp" 
#include "RNG.hpp" 
#include "blitzdefs.hpp"
#include "BlitzNet.hpp"


class BlitzNetAlopexWrapPerturber: public BlitzNetAlopexPerturber {
	
	public:
		BlitzNetAlopexWrapPerturber(double newWrapValue=DBL_MAX,double delta=0.1, double lambda=0.55,double randRange=0.0); // the first call, calls initSeed()
//        ~BlitzNetAlopexWrapPerturber() {}
		virtual NeuralNetwork* perturb(double currentError,NeuralNetwork* newNet) ;
        virtual void setWrapValue(double newWrapValue) ; 
	
		
protected:
        virtual double checkValue(double checkValue) ; 
        double mWrapValue ; 
	
	
};
#endif

