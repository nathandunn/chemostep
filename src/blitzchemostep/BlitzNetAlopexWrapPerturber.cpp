/**
* BlitzNetAlopexWrapPerturber implementation.
* Jeremiah Sullenger, v 0.1, 6/22/04
*/

#include <math.h>
#include "BlitzNetAlopexWrapPerturber.hpp"
#include "RNG.hpp"
#include <iostream>
using std::cout;
using std::endl;
#include <fstream>
using std::ofstream;
using std::ios;


BlitzNetAlopexWrapPerturber::BlitzNetAlopexWrapPerturber(double newWrapValue,double delta, double lambda,double randRange):BlitzNetAlopexPerturber(delta,lambda,randRange) 
{
    mWrapValue = newWrapValue ; 
}

void BlitzNetAlopexWrapPerturber::setWrapValue(double newWrapValue) 
{
    mWrapValue = newWrapValue ; 
}

double BlitzNetAlopexWrapPerturber::checkValue(double checkValue) 
{
    if( checkValue > mWrapValue){
        checkValue =  checkValue - 2.0 *mWrapValue ;   // wrap to the negative side
    }
    else 
    if( checkValue < -mWrapValue){
        checkValue =  checkValue + 2.0 *mWrapValue ;   // wrap to the negative side
    }
    return checkValue ; 
}

/*
 * Perturbs the network
 */
NeuralNetwork* BlitzNetAlopexWrapPerturber::perturb(double currentError, NeuralNetwork* newNet) 
{
	
	// if this is the first time the perturb function is called for the network then delta-E should be 0.
	// delta-E is determined by subtracting the previous two error values.
	if (error_val_1==0 && error_val_2==0 && error_val_3==0)
		error_val_1= error_val_2= error_val_3= currentError;
	
	BlitzNet* blitzNet = (BlitzNet*) newNet ; 
	Matrix* weights = blitzNet->getWeights()  ; 
	Matrix* weightMask = blitzNet->getWeightMask()  ; 
	Vector* bias = blitzNet->getBias()  ; 
	Vector* biasMask = blitzNet->getBiasMask()  ; 
	Vector* taus = blitzNet->getTau()  ; 
	Vector* tauMask = blitzNet->getTauMask()  ; 
	Vector* initNeurons = blitzNet->getInitNeuron()  ; 
	Vector* initNeuronMask = blitzNet->getInitNeuronMask()  ; 

	double dt = blitzNet->getMinDeltaT() ; 
	TAU_MIN = dt*3.0 ; 
		
	double cor_i_j; //correlation value
	double p_i_j; //sigmoid of correlation
	double deltE= error_val_1 - error_val_2; //change in error from n-1 and n-2
	double deltE_1 = fabs(error_val_2 - error_val_3); //absolute value of change in error from n-2 and n-3
	double slamd= deltE_1*lambda + (1.0 - lambda)*s_lambda_1; // memory function.
		
	//adjust the weights according to the alopex function.
	for (int j=0; j< weights->columns(); j++) {
		for (int i=0; i< weights->rows(); i++) {
			cor_i_j= (sgn(prev_weights_1(i,j) - prev_weights_2(i,j))*deltE)/slamd;
			p_i_j= (1.0 / (1.0 + exp(beta*-1*cor_i_j)));
			(*weights)(i,j) = checkValue( (*weights)(i,j) + ((RNG::uniform()*randomRange)+delta)*sgn(RNG::uniform()- p_i_j)*(*weightMask)(i,j)  ) ;
		}
		
		// Perturb the Tau and Bias according to the TauMask and BiasMask and the alopex function.
		cor_i_j= (sgn(prev_taus_1(j) - prev_taus_2(j))*deltE)/slamd;
		p_i_j= (1.0 / (1.0 + exp(beta*-1*cor_i_j)));
		(*taus)(j) = checkValue( (*taus)(j) + ((RNG::uniform()*randomRange)+delta)*sgn(RNG::uniform()- p_i_j)* (*tauMask)(j) );

		cor_i_j= (sgn(prev_bias_1(j) - prev_bias_2(j))*deltE)/slamd;
		p_i_j= (1.0 / (1.0 + exp(beta*-1*cor_i_j)));
		(*bias)(j) = checkValue( (*bias)(j) + ((RNG::uniform()*randomRange)+delta)*sgn(RNG::uniform()- p_i_j) * (*biasMask)(j) ) ;
	
		// handle here, not in evaluator
		if((*taus)(j) < dt*TAU_MIN) {
			(*taus)(j) = dt*TAU_MIN ;  
		}

	}
	blitzNet->setValid (false);
	s_lambda_1 = slamd; 
	shiftTrace(blitzNet);

	//for testing
	//cout << error_val_2;
	//cout << error_val_1;
  return blitzNet ; 
}




