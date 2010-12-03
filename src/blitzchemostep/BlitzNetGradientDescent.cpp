/*
 * $Id: BlitzNetGradientDescent.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzNet.hpp"
#include "blitzdefs.hpp"
#include "BlitzNetGradientDescent.hpp"

BlitzNetGradientDescent::BlitzNetGradientDescent() : GradDescent()
    ,maxIters(10)
    ,fudgeValue(0.05)
    ,network(NULL)
    ,minImprovmement(0.0)
{
}


/** 
 * This trains the weights, biases, and taus of the network.
 *
 * Because we are assuming local search, we optimize each variable, in turn.
 * So, first each weight is adjusted, then each bias, then each tau, this is 
 * then repeated for N times or until there are no further improvements.
 *
 * We still use the mask in order to 
 *
 */
TrainingTarget* BlitzNetGradientDescent::train() 
{
    if(network == NULL){
        return NULL; 
    }

    BlitzNet* trainNet = new BlitzNet() ; 
    *trainNet = *network ; 

    Matrix* weights = trainNet->getWeights() ; 
    Vector* bias = trainNet->getBias() ; 
    Vector* tau = trainNet->getTau() ; 
    Matrix* weightMask = trainNet->getWeightMask() ; 
    Vector* biasMask = trainNet->getBiasMask() ; 
    Vector* tauMask = trainNet->getTauMask() ; 

    int size = trainNet->getNumNeurons() ; 
    int iters = 0 ; 
    int subIters = 0 ; 
    double initError = trainNet->eval() ; 
    double finalError = trainNet->eval()  ; 


    cout << "initError: " <<  initError << endl ; 
    double deltaError = initError / 10.0 ;  // start with a small value

    double nextError = initError ; 
    double prevError = initError ; 

    while( -deltaError > minImprovmement || iters > maxIters){

        // do the weights first, skipping those with a mask of 0
		for(int i = 0 ; i < size ; i++){
            for(int j = 0 ; j < size ; j++){
                //  try and correct the weight at i,j
                while( -deltaError > minImprovmement || subIters > maxIters){
                    (*weights)(i,j) = (*weights)(i,j) + deltaError * fudgeValue ; 
                    prevError = nextError ; 
                    nextError = trainNet->eval() ; 
                    deltaError = nextError - prevError ; 

                    // count strikes here, two to be out
                    ++subIters ; 
                }
            }
        }

        

        // do the bias next, skipping those with a mask of 0
		for(int i = 0 ; i < size ; i++){

        }
       

        // do the tau next, skipping those with a mask of 0
		for(int i = 0 ; i < size ; i++){

        }

        finalError = trainNet->eval() ; 
        deltaError = finalError - initError ; 
        iters++ ; 
    }

    return trainNet ; 
}

void BlitzNetGradientDescent::setNetwork(BlitzNet* newNet) 
{
    network = newNet ; 
}

void BlitzNetGradientDescent::setMaxIters(int newMaxIters) 
{
    maxIters = newMaxIters ; 
}

void BlitzNetGradientDescent::setFudgeValue(double newFudgeValue) 
{
    fudgeValue = newFudgeValue ; 
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
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/blitzchemostep/BlitzNetGradientDescent.cpp"
// LAST MODIFICATION: "Mon, 29 Dec 2003 20:17:12 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzNetGradientDescent.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

