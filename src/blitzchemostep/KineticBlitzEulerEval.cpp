
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "BlitzEulerNetEvaluator.hpp"
#include "KineticBlitzEulerEval.hpp"
#include "SetFeeder.hpp"

KineticBlitzEulerEval::KineticBlitzEulerEval() : BlitzEulerNetEvaluator()
    ,initP0(-1)
    ,initP1(-1)
{
//    cout << "constructing KineticBlitzEulerEval" << endl ; 
    P0 = initP0 ; 
    P1 = initP1 ; 
}

KineticBlitzEulerEval::~KineticBlitzEulerEval() {
    delete input ; 
    delete sigma ; 
}

// note we may lose this later if not quick enough
//double BlitzEulerNetEvaluator::eval(double stim,double target,bool doTrace) 
double KineticBlitzEulerEval::evalPoint(vector<double>* stimVector,bool doTrace) 
{
    // eval for the point 
    (*input) = (*evalNeurons) * (*evalWeights) + (*evalBias) ; 		// note bias added to input...

    sigma = sigLimitVector( input ,mGlobalSigLimit) ; 


    // this is basically two iterations
    for(int i = 0 ; i < stimVector->size() ; i++){
        (*sigma)(i) = (*stimVector)[i];
        (*evalNeurons)(i) = (*stimVector)[i];
    }
    (*evalNeurons) += ( ( (*sigma) - (*evalNeurons) ) / (*evalTau) ) * localDt;

    // sum all interneurons going onto the output neuron
    // or implement but last one:    
    sumh = 0 ;
    for(int i = 0  ; i < numNeurons-1 ; i++){ // allow kinections from initial neuron
        sumh += (*evalNeurons)(i) * (*evalWeights)(i,numNeurons-1); 
    }

    // calculated P_forward or P_0 from h and w
	k01 = sigLimit(sumh) ;   // k01 = sigma(h) 
    //  IS THIS A MISTAKE?  should be (*evalWeights) (evalNeurons->size()-1,evalNeurons->size()-1)* (*evalNeurons)(evalNeurons->size()-1)
	k10 = 1 - sigLimit(sumh+ (*evalWeights)(evalNeurons->size()-1,evalNeurons->size()-1) )     ;   // k10 = sigma(h+w) ; 

    
    // set the values to their initial steady-state values
    if(P1 < 0 || P0 < 0){ // we are at the starting condition
        P1 =   k01 / (k01+k10) ; 
    }
    else{
        P1 = P1 + mMinDeltaT* ( k01 + k10) * ( -P1 + ( k01 / (k01+k10))) ; 
    }
    P0 = 1 - P1 ; 

    for(int i = 0  ; i < evalNeurons->size() ; i++){
        (*outputVector)[i] = (*evalNeurons)(i) ; 
    }
    (*outputVector)[evalNeurons->size()-1] = P0 ; 

    if(doTrace){
        addNeuronTrace(outputVector) ;  // I think this is a vector of one, called outputVector
    }

    return P0 ; 

}

void KineticBlitzEulerEval::setK01(double newK01) 
{
    k01 = newK01 ; 
}


void KineticBlitzEulerEval::setK10(double newK10) 
{
    k10 = newK10 ; 
}

void KineticBlitzEulerEval::setP1(double newP1) 
{
    P1 = newP1 ; 
}

void KineticBlitzEulerEval::setP0(double newP0) 
{
    P0 = newP0 ; 
}

/// Resets the network
bool KineticBlitzEulerEval::initEvaluator() 
{
    P0 = -1 ; 
    P1 = -1 ; 
    return true ; 
}

// outpout pertinent information to an XML file
void KineticBlitzEulerEval::toXML(ostream *s) {
  // open the XML
  addSpacer(s,1) ; 
  *s << "<evaluator type=\"kineticblitzeulereval\">" << endl ;
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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

