/**
 *  \brief  Evaluates neural networks defined by BlitzNet using the Euler's meethod.
 * 
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "BlitzEulerNetEvaluator.hpp"
#include "BlitzNetEvaluator.hpp"
#include "BlitzNet.hpp" 
#include "blitzdefs.hpp" 
#include "NeuralNetwork.hpp"  
#include "Feeder.hpp"  
#include "FeederSet.hpp"  


BlitzEulerNetEvaluator::BlitzEulerNetEvaluator()  : BlitzNetEvaluator() , 
    input(new Vector(0,MEM_POLICY)) , 
    sigma(new Vector(0,MEM_POLICY)) 

{
    network = new BlitzNet() ; 
    tempVector = NULL ; 
}

BlitzEulerNetEvaluator::~BlitzEulerNetEvaluator() {
    delete input ; 
    delete sigma ; 
}


void BlitzEulerNetEvaluator::setNetwork(NeuralNetwork* newNetwork) 
{
//    cout << "BlitzEulerNetEvaluator setting the network to: " <<  newNetwork->getNumNeurons() << endl ;  // this is run a lot
    
    if(newNetwork->getNumNeurons()!=numNeurons){
        numNeurons = newNetwork->getNumNeurons() ; 
        ((BlitzNet*)network)->setNumNeurons(numNeurons) ; 
        evalWeights->resize(numNeurons,numNeurons) ;
        evalWeightMask->resize(numNeurons,numNeurons) ;
        evalBias->resize(numNeurons) ; 
        evalBiasMask->resize(numNeurons) ; 
        evalTau->resize(numNeurons) ; 
        evalTauMask->resize(numNeurons) ; 
        evalGain->resize(numNeurons) ; 
        evalGainMask->resize(numNeurons) ; 
        evalInitNeuron->resize(numNeurons) ; 
        evalNeurons->resize(numNeurons) ; 

        input->resize(numNeurons) ; 
        sigma->resize(numNeurons) ; 
    }

    *network = *newNetwork ; 


    // now set the values
    *evalWeights =  *(((BlitzNet*) newNetwork)->getWeights())  ; 
    *evalWeightMask = *(((BlitzNet*) newNetwork)->getWeightMask()) ; 
    *evalBias = *(((BlitzNet*) newNetwork)->getBias()) ; 
    *evalBiasMask = *(((BlitzNet*) newNetwork)->getBiasMask()) ; 
    *evalTau = *(((BlitzNet*) newNetwork)->getTau()) ; 
    *evalTauMask = *(((BlitzNet*) newNetwork)->getTauMask()) ; 
    *evalGain = *(((BlitzNet*) newNetwork)->getGain()) ; 
    *evalGainMask = *(((BlitzNet*) newNetwork)->getGainMask()) ; 
    *evalInitNeuron = *(((BlitzNet*) newNetwork)->getInitNeuron()) ; 
    *evalNeurons = *(((BlitzNet*) newNetwork)->getInitNeuron()) ; 

    setStimulus(newNetwork->getEvaluator()->getStimulus()) ; 
    setTarget(newNetwork->getEvaluator()->getTarget()) ; 

//    localDt = stimulus->getDeltaT() ;   // this should be whatever the stim is set to
    localDt = getMinDeltaT() ;   

    checkTau() ; 

    numNeurons = evalNeurons->size() ; 
}

double BlitzEulerNetEvaluator::getMinDeltaT() 
{
    return stimulus->getDeltaT() ; 
}






// make sure that the smallest tau is TAU_MIN* deltaT for the stim
void BlitzEulerNetEvaluator::checkTau() 
{
    if( getMin(*evalTau) >  (EULER_MIN_TAU*localDt) ){
        return ;
    }
    for(int i = 0 ; i < evalTau->size()  ; i++){
        if( (*evalTau)(i)   < (EULER_MIN_TAU*localDt) ){
            (*evalTau)(i) = EULER_MIN_TAU * localDt  ; 
        }
    }
}



// note we may lose this later if not quick enough
double BlitzEulerNetEvaluator::evalPoint(vector<double>* stimVector,bool doTrace) 
{
    // eval for the point 
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*stimVector)[i] = (*stimVector)[i] * (*evalGain)(i) ; 
    }
    (*input) = (*evalNeurons) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...

    
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*input)(i) += (*stimVector)[i];
    }

//   sigma = sigLimitVector( input ,mGlobalSigLimit) ; 
    (*sigma) = ( 1.0 / ( 1.0 + exp( - (*input) )));
    (*evalNeurons) += ( ( (*sigma) - (*evalNeurons) ) / (*evalTau) ) * localDt;

    if(doTrace){
        for(int i = 0 ; i < evalNeurons->size() ; i++){
            (*outputVector)[i] = (*evalNeurons)(i) ; 
        }
        addNeuronTrace(outputVector) ; 
    }
    
    return (*evalNeurons)(numNeurons-1) ; 
}


void BlitzEulerNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzeulerneteval\">" << endl ;
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}




const double BlitzEulerNetEvaluator::EULER_MIN_TAU=3.0; 

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

