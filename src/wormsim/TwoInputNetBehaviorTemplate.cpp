
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BehaviorValues.hpp"
#include "RNG.hpp"

template <class WormType>
TwoInputNetBehaviorTemplate<WormType>::TwoInputNetBehaviorTemplate() : UniformNetBehaviorTemplate<WormType>(),mInputThreshold(0),mInputValueVector(NULL),mFailValue(-DBL_MAX) 
{
}


template <class WormType>
TwoInputNetBehaviorTemplate<WormType>::TwoInputNetBehaviorTemplate(BlitzLiveNet* newNet,WormType* newWorm,BlitzNetEvaluator* newEvaluator,double newThreshold,double newFailValue)  : UniformNetBehaviorTemplate<WormType>(newNet,newWorm,newEvaluator,2) , mInputThreshold(newThreshold), mFailValue(newFailValue)
{
    mInputValueVector = new vector<double>(mNumInputs) ; 
    setNetwork(newNet) ;  // sets network correctly, as well
    setWorm(newWorm) ; 
}

template <class WormType>
int TwoInputNetBehaviorTemplate<WormType>::getBehavior() 
{

    if(mWorm->getValue()> mInputThreshold){
        (*mInputValueVector)[0] = mWorm->getValue() ; 
        (*mInputValueVector)[1] = mFailValue ; 
    }
    else{
        (*mInputValueVector)[0] = mFailValue  ; 
        (*mInputValueVector)[1] = mWorm->getValue() ; 
    }
    mProbability = (mNetwork->getEvaluator())->evalPoint( mInputValueVector ,false ) ; 

    if(  mProbability  > RNG::uniform()){
	    mCurrentBehavior = BehaviorValues::FORWARD ; 
    }
    else{
        mCurrentBehavior = BehaviorValues::SHARP_TURN_50 ; 
    }
    mCurrentDecision = mCurrentBehavior ; 
    return mCurrentDecision ; 
}



template <class WormType>
void TwoInputNetBehaviorTemplate<WormType>::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<behaviormodel type=\"twoinputnetbehaviortemplate\">" << endl ;
  addSpacer(s) ; 
  *s << "<inputthreshold value=\"" << mInputThreshold << "\"/>" << endl ; 
  *s << "<failvalue value=\"" << mFailValue << "\"/>" << endl ; 
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


