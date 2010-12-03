
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BehaviorValues.hpp"
//#include "RNG.hpp"

template <class WormType>
UniformNetBehaviorTemplate<WormType>::UniformNetBehaviorTemplate() : BehaviorTemplate<WormType>(), mWorm(NULL),mNetwork(NULL), mProbability(0.0), mNumInputs(0) 
{
}


template <class WormType>
UniformNetBehaviorTemplate<WormType>::UniformNetBehaviorTemplate(BlitzLiveNet* newNet,WormType* newWorm,BlitzNetEvaluator* newEvaluator,int newInputs)  : BehaviorTemplate<WormType>() , mNetwork(NULL) , mWorm(NULL), mProbability(0.0),mEvaluator(newEvaluator) ,mNumInputs(newInputs)
{
    setNetwork(newNet) ;  // sets network correctly, as well
    setWorm(newWorm) ; 
}

template <class WormType>
int UniformNetBehaviorTemplate<WormType>::getBehavior() 
{
    mProbability = mNetwork->evalPoint( mWorm->getValue(), mNumInputs ) ; 

	if(mWorm->hitEdge()){
	    mCurrentBehavior = BehaviorValues::BOUNCE; 
	}
	else
	if(  mProbability  > RNG::uniform()){
//    if(  mProbability  > ( rand() / (float) RAND_MAX ) ){
	    mCurrentBehavior = BehaviorValues::FORWARD ; 
    }
    else{
        mCurrentBehavior = BehaviorValues::SHARP_TURN_50 ; 
    }
    mCurrentDecision = mCurrentBehavior ; 
    return mCurrentDecision ; 
}

template <class WormType>
float UniformNetBehaviorTemplate<WormType>::getProbability() 
{
    return mProbability  ; 
}

/// A reference setter, not a copy constructor.  
template <class WormType>
void UniformNetBehaviorTemplate<WormType>::setWorm(WormType* newWorm) 
{
    mWorm = newWorm ; 
}

template <class WormType>
void UniformNetBehaviorTemplate<WormType>::setNetwork(BlitzLiveNet* newNet) 
{
    if(mNetwork==NULL){
        mNetwork = new BlitzLiveNet(newNet) ; 
    }
    else{
        *mNetwork = *newNet ; 
    }
    mNetwork->setEvaluator( mEvaluator ) ;   // use connect here
    mEvaluator->setNetwork( mNetwork ) ; 

}


template <class WormType>
void UniformNetBehaviorTemplate<WormType>::decrementTabCount() 
{
  decrementTabCount() ; 
}


template <class WormType>
void UniformNetBehaviorTemplate<WormType>::addSpacer(ostream *s,int postCounterAdjust/*0*/) 
{
  addSpacer(s,postCounterAdjust) ; 
}


template <class WormType>
void UniformNetBehaviorTemplate<WormType>::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<behaviormodel type=\"uniformnetbehaviortemplate\">" << endl ;
  mEvaluator->toXML(s) ; 
  decrementTabCount() ; 
  addSpacer(s) ; 
  *s << "</behaviormodel>" << endl ;
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


