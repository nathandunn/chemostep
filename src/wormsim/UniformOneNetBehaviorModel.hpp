/*
 * $Id$
 */
#ifndef UNIFORMONENETBEHAVIORMODEL_HPP_
#  define UNIFORMONENETBEHAVIORMODEL_HPP_

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

class BlitzLiveNet ; 
class SimpleWorm; 

/**  This class does sharp-turns or runs based on the uniform probability of the output network it is evaluating.  
 *
 *
 */
class UniformOneNetBehaviorModel {

public:
    UniformOneNetBehaviorModel()  ; 
    UniformOneNetBehaviorModel(BlitzLiveNet* newNet,SimpleWorm* newWorm)  ; 
    virtual int getBehavior() ; 
    virtual float getProbability() ;
    virtual void setWorm(SimpleWorm* newWorm) ; 
    virtual void setNetwork(BlitzLiveNet* newNet) ; 

    virtual BlitzLiveNet* getNetwork() { return mNetwork; } ;
    virtual void toXML(ostream *s) ; 

protected:
    BlitzLiveNet* mNetwork ; 
    SimpleWorm* mWorm ; 
    float mProbability ; 
    int mCurrentBehavior, mCurrentDecision ;

    



} ;

#endif /* ifndef UNIFORMONENETBEHAVIORMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

