
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "BlitzEulerSigLiveNetEvaluator.hpp"


BlitzEulerSigLiveNetEvaluator::BlitzEulerSigLiveNetEvaluator(double newMinDeltaT,double newOutputSigmoid,NeuralNetwork* refNet,Vector *newInputSig,int newTableSize,double newSigmoidLimit )  : BlitzEulerSigNetEvaluator(newMinDeltaT,newOutputSigmoid,refNet ) 
,mInputSig(newInputSig)
{
}



double BlitzEulerSigLiveNetEvaluator::evalPoint(vector<double>* stimVector,bool doTrace) 
{
    int lastNeuron = numNeurons - 1; 
    double sumH = 0 ; 
    // eval for the point 
    (*input) = (*evalNeurons) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...
	
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*input)(i) = ((*input)(i) +  (*stimVector)[i]) * (*mInputSig)(i) ;
    }



    
    // NOTE:  Problems with FastSigLookup
//    sigLookup( input ) ;  // the faster method, edits input vector in-place
//    (*evalNeurons) += ( ( (*input) - (*evalNeurons) ) / (*evalTau) ) * localDt;
    (*sigma) = ( 1.0 / ( 1.0 + exp( - (*input) )));
    (*evalNeurons) += ( ( (*sigma) - (*evalNeurons) ) / (*evalTau) ) * localDt;

    // sum all interneurons going onto the output neuron
    // or implement but last one:    
    for(int i = 0  ; i < lastNeuron ; i++){ // allow kinections from initial neuron
        sumH += (*evalNeurons)(i) * (*evalWeights)(i,lastNeuron); 
    }


    double neuronInput = sumH + (*evalWeights)(lastNeuron,lastNeuron)* (*evalNeurons)(lastNeuron)+ (*evalBias)(lastNeuron)  ;
//    (*evalNeurons)(lastNeuron) = sigLookup( (mOutputSigmoid* neuronInput) ) ; 
    (*evalNeurons)(lastNeuron) = 1/(1+exp(  -mOutputSigmoid* neuronInput ) ) ; 

    // calculate binary output, here
    if( (rand()* INVS_RAND_MAX)  > (*evalNeurons) (lastNeuron)){
        (*evalNeurons) ( lastNeuron ) =  0 ; 
    }
    else{
        (*evalNeurons) ( lastNeuron ) =  1 ; 
    }

    if(doTrace==true){
        for(int i = 0  ; i < numNeurons  ; i++){
            (*outputVector)[i] = (*evalNeurons)(i) ; 
        }
        (*outputVector)[lastNeuron] = (*evalNeurons)(lastNeuron) ; 
        addNeuronTrace(outputVector) ;  // I think this is a vector of one, called outputVector
    }

    mSumH = sumH ; 

    // return the output of the binary neuron
    return (*evalNeurons)(lastNeuron); 
}


//void BlitzEulerSigLiveNetEvaluator::sigLookupTableToXml(ostream *s) 
//{
//  addSpacer(s,1) ; 
//  *s << "<siglookuptable type=\"fastsiglookup\">" << endl ; 
//  addSpacer(s) ; 
//  *s << "<limit value=\"" << F_LIMIT << "\"/>" << endl ; 
//  addSpacer(s,-1) ; 
//  *s << "<length value=\"" << F_TABLE_LENGTH << "\"/>" << endl ; 
//  addSpacer(s) ; 
//  *s << "</siglookuptable>" << endl ; 
//}



void BlitzEulerSigLiveNetEvaluator::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"blitzeulersiglivenetevaluator\">" << endl ;
  addSpacer(s) ; 
  *s << "<outputsigmoid value=\"" << mOutputSigmoid << "\"/>" << endl ; 
  if(mInputSig==NULL){
      *s << "<inputsig value=\"NULL\"/>" << endl ; 
  }
  else{
      *s << "<inputsig value=\"" ; 
      for(int i = 0 ; i < mInputSig->size() ; i++){
          *s << (*mInputSig)(i)  ; 
          if(i< mInputSig->size()-1){
          *s << "," ; 
          }
      }
      *s << "\"/>" << endl ; 
  }

//  sigLookupTableToXml(s) ; 

  doBaseXML(s) ; 
  // close the XML
  addSpacer(s) ; 
  *s << "</evaluator>" << endl ;
}

void BlitzEulerSigLiveNetEvaluator::setInputSig(Vector* newInputSig) 
{
    if(mInputSig==NULL){
        newInputSig = new Vector( *newInputSig ) ; 
        return ; 
    }


    if(newInputSig->size()!=mInputSig->size()){
        mInputSig->resize( newInputSig->size() ) ; 
    }
    *newInputSig = *mInputSig ; 
}


Vector* BlitzEulerSigLiveNetEvaluator::getInputSig() 
{
    return mInputSig ; 
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



