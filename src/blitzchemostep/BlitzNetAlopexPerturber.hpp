/**
* BlitzNetAlopexPerturber header file. 
* Jeremiah Sullenger, version 0.1 6/22/04
*/

#ifndef BLITZNETALOPEXPERTURBER_H
#define BLITZNETALOPEXPERTURBER_H

#include "NetPerturber.hpp" 
#include "RNG.hpp" 
#include "blitzdefs.hpp"
#include "BlitzNet.hpp"


class BlitzNetAlopexPerturber: public NetPerturber {
	
	public:
		BlitzNetAlopexPerturber(double delta=0.1, double lambda=0.55,double randomRange=0.0); // the first call, calls initSeed()
		~BlitzNetAlopexPerturber() {}
		virtual NeuralNetwork* perturb(double currentError,NeuralNetwork* newNet) ;
		virtual void initTrace ( Matrix*, Vector*, Vector*); //initializes the values needed for the perturbation.
		virtual double getDelta () {return delta;}
		double getLambda () {return lambda;}
		virtual void setDelta (double delt) {delta=delt;}
		virtual void setLambda (double lam) {lambda=lam;}
		virtual void setBeta (double bet) { beta=bet;}
		virtual void setRange (double newRange) { randomRange=newRange ;}
	
		
protected:
	
		// parameters.
		double delta; //weight change value.
		double lambda; //memory coefficient (forgetting constant) for Slambda
		double beta; //correlation gain
		double randomRange ; // delta range
		static double TAU_MIN;
	
			// instance variables.
		Matrix prev_weights_1; //network weights for iteration n-1
		Matrix prev_weights_2; //network weights for iteration n-2
		Vector prev_taus_1; //network taus for iteration n-1
		Vector prev_taus_2; //network taus for iteration n-2
		Vector prev_bias_1; //network bias for iteration n-1
		Vector prev_bias_2; //network bias for iteration n-2
			
		double error_val_1; //network fitness for iteration n-1
		double error_val_2; //net fitness n-2
		double error_val_3; //fitness n-3
		double s_lambda_1; //error gradiant memory for iteration n-1
				
		// member functions.
		
		double sgn (double num) const; //returns -1 or 1 depending on the sign of the argument.
		void shiftTrace (NeuralNetwork *net); //shifts instance variables.
	
	
};
#endif

