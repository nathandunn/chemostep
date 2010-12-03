/*
 * $Id$
 */
#ifndef BLITZEULERSIGLIVENETEVALUATOR_H
#  define BLITZEULERSIGLIVENETEVALUATOR_H

#include "BlitzEulerSigNetEvaluator.hpp"

/** BlitzEulerSigLiveNetEvaluator extends BlitzEulerLiveNetEvaluator but has a modifiable sigmoid.  
 *
 */
class BlitzEulerSigLiveNetEvaluator : public BlitzEulerSigNetEvaluator 
{


public:
    BlitzEulerSigLiveNetEvaluator(double newMinDeltaT=1.0,double newOutputSigmoid=1.0,NeuralNetwork* refNet=NULL,Vector* newInputSig=NULL,int newTableSize=256,double newSigmoidLimit=8.0) ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;
    virtual void setInputSig(Vector* newInputSig) ; 
    virtual Vector* getInputSig() ; 
//    virtual void sigLookupTableToXml(ostream *s) ;
    virtual void toXML(ostream *s) ;

protected:
    Vector* mInputSig ; 






} ;

#endif /* ifndef BLITZEULERLIVENETEVALUATOR_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

