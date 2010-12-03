/**
 *  \brief  Evaluates neural networks defined by BlitzNet using the RK4 or Huen's method.
 * 
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "BlitzRK4NetEvaluator.hpp"
#include "BlitzNetEvaluator.hpp"
#include "BlitzNet.hpp" 
#include "blitzdefs.hpp" 
#include "NeuralNetwork.hpp"  
#include "Feeder.hpp"  
#include "FeederSet.hpp"  


BlitzRK4NetEvaluator::BlitzRK4NetEvaluator(double newDeltaT)  : BlitzNetEvaluator() , 
    input(new Vector(0,MEM_POLICY)) , 
    sigma(new Vector(0,MEM_POLICY)) ,
    k1(new Vector(0,MEM_POLICY)), 
    k2(new Vector(0,MEM_POLICY)) ,
    k3(new Vector(0,MEM_POLICY)) ,
    k4(new Vector(0,MEM_POLICY)) ,
    midActivity(new Vector(0,MEM_POLICY)) ,
    midInput(new Vector(0,MEM_POLICY)) 
{
    localDt = newDeltaT;
    network = new BlitzNet() ; 
    tempVector = NULL ; 
}

BlitzRK4NetEvaluator::~BlitzRK4NetEvaluator() {
    delete input ; 
    delete sigma ; 
}

void BlitzRK4NetEvaluator::setOutputSigmoid(double newOutputSigmoid) 
{
    mOutputSigmoid = newOutputSigmoid ; 
}



void BlitzRK4NetEvaluator::setNetwork(NeuralNetwork* newNetwork) 
{
//    cout << "BlitzRK4NetEvaluator setting the network to: " <<  newNetwork->getNumNeurons() << endl ;  // this is run a lot
    
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
        k3->resize(numNeurons) ; 
        k4->resize(numNeurons) ; 
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

    setStimulus(newNetwork->getEvaluator()->getStimulus()) ; 
    setTarget(newNetwork->getEvaluator()->getTarget()) ; 

//    localDt = stimulus->getDeltaT() ;   // this should be whatever the stim is set to
    localDt = getMinDeltaT() ;   

//    checkTau() ; 

    numNeurons = evalNeurons->size() ; 
    lastNeuron = numNeurons - 1 ; 
}

//double BlitzRK4NetEvaluator::getMinDeltaT() 
//{
//    return stimulus->getDeltaT() ; 
//}






// make sure that the smallest tau is TAU_MIN* deltaT for the stim
//void BlitzRK4NetEvaluator::checkTau() 
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
double BlitzRK4NetEvaluator::evalPoint(vector<double>* stimVector,bool doTrace) 
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

    // This is where deltaT is evaluated by the RK4 method, such that:
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
    if(doTrace){
        for(int i = 0 ; i < evalNeurons->size() ; i++){
            (*outputVector)[i] = (*evalNeurons)(i) ; 
        }
        addNeuronTrace(outputVector) ; 
    }
    (*evalNeurons)(lastNeuron) = fixOutput( (*evalNeurons)(lastNeuron)  ) ; 
    
    return (*evalNeurons)(lastNeuron) ; 
}

double BlitzRK4NetEvaluator::fixOutput(double outputNeuron) 
{
    return outputNeuron ; 
}



void BlitzRK4NetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzmidpointneteval\">" << endl ;
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

