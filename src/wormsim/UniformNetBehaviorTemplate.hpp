/*
 * $Id$
 */
#ifndef UNIFORMNETBEHAVIORTEMPLATE_HPP_
#  define UNIFORMNETBEHAVIORTEMPLATE_HPP_

#include "BlitzLiveNet.hpp"
#include "BehaviorTemplate.hpp"

template <class WormType>
class UniformNetBehaviorTemplate : public BehaviorTemplate<WormType>{

public:
    UniformNetBehaviorTemplate()  ; 
    UniformNetBehaviorTemplate(BlitzLiveNet* newNet,WormType* newWorm,BlitzNetEvaluator* newEvaluator=NULL,int newInputs=1)  ; 
    virtual int getBehavior() ; 
    virtual float getProbability() ;
    virtual void setWorm(WormType* newWorm) ; 
    virtual void setNetwork(BlitzLiveNet* newNet) ; 

    virtual BlitzLiveNet* getNetwork() { return mNetwork; } ;
    virtual void toXML(ostream *s) ; 

		// wrappers to XmlRenderable methods . . . messy
    virtual void addSpacer(ostream *s,int postCounterAdjust=0) ; 
    static void decrementTabCount() ; 
   
protected:
    BlitzLiveNet* mNetwork ; 
    WormType* mWorm ; 
    int mCurrentDecision, mCurrentBehavior; 
    double mProbability ; 
    BlitzNetEvaluator* mEvaluator ; 
    int mNumInputs ; 

} ;

#include "UniformNetBehaviorTemplate.cpp"

#endif /* ifndef UNIFORMNETBEHAVIORTEMPLATE_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


