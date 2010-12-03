/**
 *  \brief  Evaluates neural networks defined by BlitzNet using the MidPoint or Huen's method.
 * 
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "BlitzMidPointNetEvaluator.hpp"
#include "BlitzNetEvaluator.hpp"
#include "BlitzNet.hpp" 
#include "blitzdefs.hpp" 
#include "NeuralNetwork.hpp"  
#include "Feeder.hpp"  
#include "FeederSet.hpp"  


BlitzMidPointNetEvaluator::BlitzMidPointNetEvaluator(double newDeltaT,double newOutputSigmoid,NeuralNetwork* refNet)  : BlitzNetEvaluator() , 
    input(new Vector(0,MEM_POLICY)) , 
    sigma(new Vector(0,MEM_POLICY)) ,
    k1(new Vector(0,MEM_POLICY)), 
    k2(new Vector(0,MEM_POLICY)) ,
    midActivity(new Vector(0,MEM_POLICY)) ,
    midInput(new Vector(0,MEM_POLICY)) ,
    mOutputSigmoid(newOutputSigmoid )
    
{
    network = new BlitzNet() ; 
    tempVector = NULL ; 

//    mSumH = 0 ; 
    mOutputSigmoid = newOutputSigmoid ; 
    mMinDeltaT = newDeltaT ; 
    if(refNet!=NULL){
        setNetwork(refNet) ; 
    }
}

BlitzMidPointNetEvaluator::~BlitzMidPointNetEvaluator() {
    delete input ; 
    delete sigma ; 
}

void BlitzMidPointNetEvaluator::setOutputSigmoid(double newOutputSigmoid) 
{
    mOutputSigmoid = newOutputSigmoid ; 
}



void BlitzMidPointNetEvaluator::setNetwork(NeuralNetwork* newNetwork) 
{
//    cout << "BlitzMidPointNetEvaluator setting the network to: " <<  newNetwork->getNumNeurons() << endl ;  // this is run a lot
    
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

        k1->resize(numNeurons) ; 
        k2->resize(numNeurons) ; 
        midActivity->resize(numNeurons) ; 
        midInput->resize(numNeurons) ; 
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

    /// These are unnecessary since most of the networks will simply use an "evalPoint" method anyway, I hope.  It also conforms to the way that BlitzEulerLiveNetEvaluator functions, as well.
//    setStimulus(newNetwork->getEvaluator()->getStimulus()) ; 
//    setTarget(newNetwork->getEvaluator()->getTarget()) ; 

    localDt = getMinDeltaT() ;   

//    checkTau() ; 

    numNeurons = evalNeurons->size() ; 
    lastNeuron = numNeurons - 1 ; 
}

double BlitzMidPointNetEvaluator::getMinDeltaT() 
{
    return mMinDeltaT ; 
}






// make sure that the smallest tau is TAU_MIN* deltaT for the stim
//void BlitzMidPointNetEvaluator::checkTau() 
//{
//    if( getMin(*evalTau) >  (EULER_MIN_TAU*localDt) ){
//        return ;
//    }
//    for(int i = 0 ; i < evalTau->size()  ; i++){
//        if( (*evalTau)(i)   < (EULER_MIN_TAU*localDt) ){
//            (*evalTau)(i) = EULER_MIN_TAU * localDt  ; 
//        }
//    }
//}



// note we may lose this later if not quick enough
double BlitzMidPointNetEvaluator::evalPoint(vector<double>* stimVector,bool doTrace) 
{
    // eval for the point 
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*stimVector)[i] = (*stimVector)[i] * (*evalGain)(i) ; 
    }
    (*input) = (*evalNeurons) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...
    
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*input)(i) += (*stimVector)[i];
    }
    // EXP C-FUNCTION CODE
    double outputNeuron  = 1.0 / ( 1 + exp( - mOutputSigmoid * (*input)(lastNeuron) ) )   ; 

//   sigma = sigLimitVector( input ,mGlobalSigLimit) ; 
    (*sigma) = ( 1.0 / ( 1.0 + exp( - (*input) )));

    // This is where deltaT is evaluated by the MidPoint method, such that:
    // y(t+deltat) = y(t) + deltat * dy/dt( t + deltat/2,y(t)+deltat/2+dy/dt(t,y(t))) 
//    // k1 = deltat * dy/dt
    (*k1) = localDt * ( ( (*sigma) - (*evalNeurons) ) / (*evalTau) ) ; 
//    // k2 = deltat * dy/dt (y=y(t)+1/2 k1)
//    (*midActivity) = ( (*evalNeurons)+ (0.5 * (*k1) ) ) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...
    (*midActivity) =   (*evalNeurons) + (0.5*(*k1)) ;  // Had to split this up onto two lines in order to get it to compile
    (*midInput) =  (*midActivity) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*midInput)(i) += (*stimVector)[i];
    }
    (*sigma) = ( 1.0 / ( 1.0 + exp( - (*midInput) )));
    (*k2) = localDt * ( ( (*sigma) - (*midActivity) ) / (*evalTau) ) ; 
    (*evalNeurons) = (*evalNeurons) + (*k2) ; 
//    // y(t+deltat) = y(t) + k2 ; 
//    (*evalNeurons) = (*evalNeurons) + (*k2) ; 

//    FIX OUTPUT NEURON for use in the sigmoid
    (*evalNeurons)(lastNeuron) = outputNeuron ; 

    if(doTrace){
        for(int i = 0 ; i < evalNeurons->size() ; i++){
            (*outputVector)[i] = (*evalNeurons)(i) ; 
        }
        addNeuronTrace(outputVector) ; 
    }

    (*evalNeurons)(lastNeuron) = fixOutput( (*evalNeurons)(lastNeuron)  ) ; 
    
    return (*evalNeurons)(lastNeuron) ; 
}

double BlitzMidPointNetEvaluator::fixOutput(double outputNeuron) 
{
    return outputNeuron ; 
}



void BlitzMidPointNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzmidpointneteval\">" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\"" << mOutputSigmoid << "\"/>" << endl ; 
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
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

