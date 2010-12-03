
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "BlitzEulerLiveNetEvaluator.hpp"
#include "BlitzEulerNetEvaluator.hpp"
#include "NeuralNetwork.hpp"
#include "BlitzNet.hpp" 


#include "BlitzXmlNetRenderer.hpp" 
//#include "FastSigLookup.hpp" 

BlitzEulerLiveNetEvaluator::BlitzEulerLiveNetEvaluator(double newMinDeltaT,double newOutputSigmoid,NeuralNetwork* refNet)  : BlitzEulerNetEvaluator()  // , FastSigLookup(245760,10000) 
{
    mSumH = 0 ; 
    mOutputSigmoid = newOutputSigmoid ; 
    mMinDeltaT = newMinDeltaT ; 
    if(refNet!=NULL){
        setNetwork(refNet) ; 
    }

}

void BlitzEulerLiveNetEvaluator::setOutputSigmoid(double newSigmoid) 
{
    mOutputSigmoid = newSigmoid ; 
}

double BlitzEulerLiveNetEvaluator::getOutputSigmoid() 
{
    return mOutputSigmoid ; 
}



void BlitzEulerLiveNetEvaluator::setNetwork(NeuralNetwork* newNetwork) 
{
//    cout << this << "  BlitzEulerLiveNetEvaluator setting the network to: " <<  *( ((BlitzNet*) newNetwork)->getWeights()) << endl ;  // this is run a lot
    
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

    localDt = getMinDeltaT() ;   // this should be whatever the stim is set to

    checkTau() ; 

    numNeurons = evalNeurons->size() ; 

//    cout << this << "  evalWeights set: " << (*evalWeights) << endl ; 
}


double BlitzEulerLiveNetEvaluator::getMinDeltaT() 
{
    return mMinDeltaT ; 
}


double BlitzEulerLiveNetEvaluator::evalPoint(vector<double>* stimVector,bool doTrace) 
{
    int lastNeuron = numNeurons - 1 ;

    // eval for the point 
    (*input) = (*evalNeurons) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...

    // Calculate stim with gain put before outputNeuron in the off chance that the stimuulus goes to the output
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*input)(i) += (*stimVector)[i] * (*evalGain)(i)  ;
//        cout << "i["<< i << "] (*stimVector)[" << (*stimVector)[i] <<"]"  << " input[" << (*input)(i) << "]" << endl ; 
    }

    // SIG LOOKUP CODE
//    double outputNeuron  =  sigLookup(  mOutputSigmoid * (*input)(lastNeuron)  )   ; 
//    sigLookup(input) ;
//    (*evalNeurons) += ( ( (*input) - (*evalNeurons) ) / (*evalTau) ) * localDt;

    // EXP C-FUNCTION CODE
    double outputNeuron  = 1.0 / ( 1 + exp( - mOutputSigmoid * (*input)(input->size()-1) ) )   ; 
//    cout << "input value of output: " << (*input)(input->size()-1) << endl ; 
    (*sigma) = ( 1.0 / ( 1.0 + exp( - (*input) )));
    (*evalNeurons) += ( ( (*sigma) - (*evalNeurons) ) / (*evalTau) ) * localDt;
    

    // set to instantaneous value
    (*evalNeurons)(lastNeuron) = outputNeuron ; 



    // putting the trace here allows us to track the sigmoid prior to being evaluated as a binary or other fashion
    if(doTrace==true){
        for(int i = 0  ; i < numNeurons ; i++){
            (*outputVector)[i] = (*evalNeurons)(i) ; 
        }
        (*outputVector)[lastNeuron] = (*evalNeurons)(lastNeuron) ; 
        addNeuronTrace(outputVector) ;  // I think this is a vector of one, called outputVector
    }

    (*evalNeurons)(lastNeuron) = fixOutput( (*evalNeurons)(lastNeuron)  ) ; 


    // return the output of the binary neuron
    return (*evalNeurons)(lastNeuron); 
}


/// Here, we shift the output sigmoid and choose a binary output.
double BlitzEulerLiveNetEvaluator::fixOutput(double outputNeuron) 
{
    
    if( (rand()/(float) RAND_MAX) > outputNeuron ){
        return 0.0 ; 
    }
    else{
        return  1.0 ; 
    }
}


///// Relaxes based on the avg absolute changing value of all of the neurons.
//void BlitzEulerLiveNetEvaluator::relaxNet(bool doTrace) 
//{
//    cout << "BlitzEulerLiveNetEvaluator: trying to relax net: " << mRelaxTime << endl ; 
//    if(mRelaxTime==0) {
//        return ; 
//    }
//
//    // if the relax time i s greater than the eval time then:
//
//    if(mRelaxTau!=0){
//        mOriginalTau = new Vector(evalTau->size()) ; 
//        *evalTau = mRelaxTau ; 
//    }
//    
//    // copy old dt values
//    oldLocalDeltaT = localDt; 
//    localDt = mRelaxDeltaT ;
//
//    // initialize values
//    relaxPoints = (int) (mRelaxTime/mRelaxDeltaT) ; 
////    currentRelaxValue = evalPoint(mRelaxValueVector,doTrace) ; 
//    currentRelaxValue = evalPoint(mRelaxValueVector,true) ; 
//    relaxCounter = 1 ; 
//    relaxDelta = getAvgLastNeuronChange(relaxCounter) ; // start measuring change at 1, not 0
//
//    cout << "init relaxDelta: " << relaxDelta << " mRelaxLimit: " << mRelaxLimit << endl ; 
//
//    ++relaxCounter ; 
//    
//    while( relaxDelta > mRelaxLimit &&  relaxCounter < relaxPoints ){
//        currentRelaxValue = evalPoint(mRelaxValueVector,true) ; 
//        relaxDelta = getAvgLastNeuronChange(relaxCounter) ; // start measuring change at 1, not 0
//        ++relaxCounter ; 
//    }
//    *relaxedNeurons = *evalNeurons ; 
//
////    cout << "relaxed at " << relaxCounter  << " with relaxDelta: " << relaxDelta <<  endl ; 
//
//    // replace old values
//    localDt = oldLocalDeltaT ; 
//    if(mRelaxTau!=0){
//        *evalTau = *mOriginalTau ; 
//        mOriginalTau = NULL ; 
//    }
//
//    // clear array
//    currentNeuronPoint = 0 ; 
//}




void BlitzEulerLiveNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzeulerlivenetevaluator\">" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\"" << mOutputSigmoid << "\"/>" << endl ; 
  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}

double BlitzEulerLiveNetEvaluator::getSumH() 
{
    return mSumH ; 
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

