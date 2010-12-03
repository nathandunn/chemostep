#ifndef BLITZMIDPOINTNETEVALUATOR_HPP_
#  define BLITZMIDPOINTNETEVALUATOR_HPP_

#include "BlitzNetEvaluator.hpp" 
#include "blitzdefs.hpp"

/**  
 * Evaluates BlitzNet networks using MidPoints method.or RK2.
 *
 */
#include "BlitzNetEvaluator.hpp"

class BlitzMidPointNetEvaluator : public BlitzNetEvaluator {

public:
    BlitzMidPointNetEvaluator(double newDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL) ; 
    ~BlitzMidPointNetEvaluator() ; 
    virtual void setNetwork(NeuralNetwork* newNetwork) ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;
    virtual double fixOutput(double outputNeuron) ; /// Fixes the output neuron. 
    virtual void setOutputSigmoid(double newOutputSigmoid) ; 
    virtual double getMinDeltaT() ; 
    virtual void toXML(ostream *s) ; 

protected:
    double mOutputSigmoid ; 
//    void checkTau() ;  // defines the min tau
    Vector *sigma ; 
    Vector *input ; 
    vector<double>* tempVector ; // for evalPoint(double,bool) 
    Vector *k1 ; 
    Vector *k2 ; 
    Vector *midActivity ; 
    Vector *midInput    ; 
    int lastNeuron ; 
    double mMinDeltaT ; 

} ;

#endif /* ifndef BLITZMIDPOINTNETEVALUATOR_HPP_g*/
// -*- C++ -*-

