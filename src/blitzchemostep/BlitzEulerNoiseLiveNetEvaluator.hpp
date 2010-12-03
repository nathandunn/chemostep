/*
 * $Id$
 */
#ifndef BLITZEULERNOISELIVENETEVALUATOR_H
#  define BLITZEULERNOISELIVENETEVALUATOR_H

#include "BlitzEulerNetEvaluator.hpp"
class NeuralNetwork ; 

/** Extends BlitzEulerNoiseLiveNetEvaluator providing methods which don't have feeders.  Easier than making BlitzEulerNoiseLiveNetEvaluator conform to BlitzLiveNet specs.    This class was developed to be used with WormSimEval, though it provides more generality. 
 *
 */
class BlitzEulerNoiseLiveNetEvaluator : public BlitzEulerNetEvaluator 
{


public:
    BlitzEulerNoiseLiveNetEvaluator(double newMinDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL,double mInputNoise=0.0,double mOutputNoise=0.0) ; 
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
    double mInputNoise,mOutputNoise ; 




} ;

#endif /* ifndef BLITZEULERLIVENETEVALUATOR_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

