/*
 * $Id$
 */
#ifndef UNIFORMNETBEHAVIORMODEL_HPP_
#  define UNIFORMNETBEHAVIORMODEL_HPP_

#include "BehaviorModel.hpp"

class BlitzLiveNet ; 
class BaseWorm; 

/**  This class does sharp-turns or runs based on the uniform probability of the output network it is evaluating.  
 *
 *
 */
class UniformNetBehaviorModel : public BehaviorModel{

public:
    UniformNetBehaviorModel()  ; 
    UniformNetBehaviorModel(BlitzLiveNet* newNet,BaseWorm* newWorm)  ; 
    virtual int getBehavior() ; 
    virtual float getProbability() ;
    virtual void setWorm(BaseWorm* newWorm) ; 
    virtual void setNetwork(BlitzLiveNet* newNet) ; 

    virtual BlitzLiveNet* getNetwork() { return mNetwork; } ;
    virtual void toXML(ostream *s) ; 

protected:
    BlitzLiveNet* mNetwork ; 
    BaseWorm* mWorm ; 
    float mProbability ; 

    



} ;

#endif /* ifndef UNIFORMNETBEHAVIORMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

