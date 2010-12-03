/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "UniformOneNetBehaviorModel.hpp"

#include "BlitzLiveNet.hpp"
#include "SimpleWorm.hpp"
#include "BehaviorModel.hpp"

UniformOneNetBehaviorModel::UniformOneNetBehaviorModel()  : mNetwork(NULL) , mWorm(NULL)
{ }


UniformOneNetBehaviorModel::UniformOneNetBehaviorModel(BlitzLiveNet* newNet,SimpleWorm* newWorm)  :  mNetwork(NULL) , mWorm(NULL)
{
    setNetwork(newNet) ; 
    setWorm(newWorm) ; 
}

void UniformOneNetBehaviorModel::setWorm(SimpleWorm* newWorm) 
{
    if(mWorm==NULL){
        mWorm = new SimpleWorm(newWorm) ; 
    }
    else{
        *mWorm = *newWorm ; 
    }
}


int UniformOneNetBehaviorModel::getBehavior() {

    cout << "evaluating point: "<< mWorm->getValue() << " at : " << (mWorm->getX()) << " " << mWorm->getY()  << endl ;
    mProbability = ((BlitzLiveNet*) mNetwork)->evalPoint( mWorm->getValue()) ; 

     if(  mProbability  > RNG::uniform()){
	 mCurrentBehavior = mCurrentDecision = BehaviorModel::FORWARD ; 
    }
    else{
        mCurrentBehavior = mCurrentDecision = BehaviorModel::SHARP_TURN_50 ; 
    }
    cout << "UniformOneNetBehaviorModel mCurrentDecision: " << mCurrentDecision << " mProbability: " <<  mProbability << endl ; 
    return mCurrentDecision ; 
}

/// Makes the assumption that the probablity has already been calculated via getBehavior
float UniformOneNetBehaviorModel::getProbability() {
    return mProbability ; 
}


void UniformOneNetBehaviorModel::setNetwork(BlitzLiveNet* newNetwork ) 
{
    if (mNetwork==NULL){
        mNetwork = new BlitzLiveNet(newNetwork) ; 
    }
    else{
        *mNetwork = *newNetwork ; 
    }
}




void UniformOneNetBehaviorModel::toXML(ostream *s) 
{
  *s << "\t<behaviormodel type=\"uniformonenetbehaviormodel\">" << endl ;
  *s << "\t</behaviormodel>" << endl ;
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
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

