
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzNetPerturber.hpp"
#include "BlitzNet.hpp"
#include "RNG.hpp"

NeuralNetwork* BlitzNetPerturber::perturb(double temp,NeuralNetwork* newNet) 
{

//    cout << "perturbin net at: " << temp << endl ; 

    BlitzNet* blitzNet = (BlitzNet*) newNet ; 
    Matrix* weights = blitzNet->getWeights()  ; 
    Matrix* weightMask = blitzNet->getWeightMask()  ; 
    Vector* bias = blitzNet->getBias()  ; 
    Vector* biasMask = blitzNet->getBiasMask()  ; 
    Vector* taus = blitzNet->getTau()  ; 
    Vector* tauMask = blitzNet->getTauMask()  ; 
    Vector* initNeurons = blitzNet->getInitNeuron()  ; 
    Vector* initNeuronMask = blitzNet->getInitNeuronMask()  ; 
//    cout << "*initNeurons: " << (*initNeurons) << endl ; 
//    cout << "*blitzNet->getInitNeuron(): " << (*(blitzNet->getInitNeuron())) << endl ; 

    int columnCount , rowCount ; 
  int matrixLength = (int) sqrt((double) weights->size()) ; 
  for(columnCount = 0 ; columnCount < matrixLength; ++columnCount  ) {
      for( rowCount = 0  ;  rowCount < matrixLength ; ++rowCount ) {
        (*weights)(rowCount,columnCount) +=   RNG::normal() * temp * (*weightMask)(rowCount,columnCount) ; 
      }

      // Perturb the Tau and Bias according to the TauMask and BiasMask
      (*taus)(columnCount) += RNG::normal() * temp * (*tauMask)(columnCount); 
      (*bias)(columnCount) += RNG::normal() * temp * (*biasMask)(columnCount); 
//      (*initNeurons)(columnCount) += RNG::uniform() * temp * (*initNeuronMask)(columnCount);  // don't want to deal with these, as the range is limited to between 0 and 1
  
  }
  return blitzNet ; 
}

void BlitzNetPerturber::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s) ; 
  *s << "<perturber type=\"blitznetperturber\">" << endl ;
  // close the XML
  addSpacer(s) ; 
  *s << "</perturber>" << endl ;

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

