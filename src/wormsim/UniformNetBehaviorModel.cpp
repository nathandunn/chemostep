/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "UniformNetBehaviorModel.hpp"

#include "BlitzLiveNet.hpp"
#include "BaseWorm.hpp"

UniformNetBehaviorModel::UniformNetBehaviorModel()  : BehaviorModel() 
{
}


UniformNetBehaviorModel::UniformNetBehaviorModel(BlitzLiveNet* newNet,BaseWorm* newWorm)  : BehaviorModel()
{
    mNetwork = newNet ; 
    mWorm = newWorm ; 
}

void UniformNetBehaviorModel::setWorm(BaseWorm* newWorm) 
{
    mWorm = newWorm ; 
}


///  Here, the current behavior becomes the current decision, since all probabilities are taken care of in the nework, assumedly.
int UniformNetBehaviorModel::getBehavior() {

    mProbability = mNetwork->evalPoint( mWorm->getValue()) ; 

    if( mProbability > RNG::uniform()){
	    currentBehavior = currentDecision = FORWARD ; 
    }
    else{
        currentBehavior = currentDecision = SHARP_TURN_50 ; 
    }


    return currentDecision ; 
}

/// Makes the assumption that the probablity has already been calculated via getBehavior
float UniformNetBehaviorModel::getProbability() {
    return mProbability ; 
}


void UniformNetBehaviorModel::setNetwork(BlitzLiveNet* newNetwork ) 
{
    mNetwork = newNetwork ; 
}




void UniformNetBehaviorModel::toXML(ostream *s) 
{
  *s << "\t<behaviormodel type=\"uniformnetbehaviormodel\">" << endl ;
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

