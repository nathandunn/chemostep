/*
 * $Id$
 */
#ifndef BLITZEULERLIVENETEVALUATOR_H
#  define BLITZEULERLIVENETEVALUATOR_H

#include "BlitzEulerNetEvaluator.hpp"
class NeuralNetwork ; 

/** Extends BlitzEulerLiveNetEvaluator providing methods which don't have feeders.  Easier than making BlitzEulerLiveNetEvaluator conform to BlitzLiveNet specs.    This class was developed to be used with WormSimEval, though it provides more generality. 
 *
 */
class BlitzEulerLiveNetEvaluator : public BlitzEulerNetEvaluator 
{


public:
    BlitzEulerLiveNetEvaluator(double newMinDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL) ; 
    virtual void setNetwork(NeuralNetwork* newNetwork) ; 
    virtual void setOutputSigmoid(double newSigmoid) ; 
    virtual double getOutputSigmoid() ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;
    virtual void toXML(ostream *s) ;
    virtual double getMinDeltaT() ; 
    virtual double getSumH() ; 
//    virtual void relaxNet(bool doTrace=false) ; 
    virtual double fixOutput(double outputNeuron) ; /// Fixes the output neuron. 
    

protected:
    double mSumH ; 
    double mOutputSigmoid ; 




} ;

#endif /* ifndef BLITZEULERLIVENETEVALUATOR_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

