/*
 * $Id$
 */
#ifndef TWOINPUTNETBEHAVIORTEMPLATE_HPP_
#  define TWOINPUTNETBEHAVIORTEMPLATE_HPP_

#include "UniformNetBehaviorTemplate.hpp"

template <class WormType>
class TwoInputNetBehaviorTemplate : public UniformNetBehaviorTemplate<WormType>{

public:
    TwoInputNetBehaviorTemplate()  ; 
    TwoInputNetBehaviorTemplate(BlitzLiveNet* newNet,WormType* newWorm,BlitzNetEvaluator* newEvaluator=NULL,double newThresholdValue=0.5,double newFailValue=-DBL_MAX)  ; 
    virtual int getBehavior() ; 
    virtual void toXML(ostream *s) ; 
   
protected:
    double mInputThreshold,mFailValue  ; 
    vector<double>* mInputValueVector  ; 

} ;

#include "TwoInputNetBehaviorTemplate.cpp"

#endif /* ifndef TWOINPUTNETBEHAVIORTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


