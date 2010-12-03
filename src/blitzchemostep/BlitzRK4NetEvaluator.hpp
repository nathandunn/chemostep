#ifndef BLITZRK4NETEVALUATOR_HPP_
#  define BLITZRK4NETEVALUATOR_HPP_

#include "BlitzNetEvaluator.hpp" 
#include "blitzdefs.hpp"

/**  
 * Evaluates BlitzNet networks using RK4s method.or RK2.
 *
 */
#include "BlitzNetEvaluator.hpp"

class BlitzRK4NetEvaluator : public BlitzNetEvaluator {

public:
    BlitzRK4NetEvaluator(double newDeltaT=1.0) ; 
    ~BlitzRK4NetEvaluator() ; 
    virtual void setNetwork(NeuralNetwork* newNetwork) ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;
    virtual double fixOutput(double outputNeuron) ; /// Fixes the output neuron. 
    virtual void setOutputSigmoid(double newOutputSigmoid) ; 
//    virtual double getMinDeltaT() ; 
    virtual void toXML(ostream *s) ; 

protected:
    double mOutputSigmoid ; 
//    void checkTau() ;  // defines the min tau
    Vector *sigma ; 
    Vector *input ; 
    vector<double>* tempVector ; // for evalPoint(double,bool) 
    Vector *k1 ; 
    Vector *k2 ; 
    Vector *k3 ; 
    Vector *k4 ; 
    Vector *midActivity ; 
    Vector *midInput    ; 
    int lastNeuron ; 

} ;

#endif /* ifndef BLITZRK4NETEVALUATOR_HPP_g*/
// -*- C++ -*-

