/*
 * $Id: netreader.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $
 */

//#include <iostream>
//using std::cout ; 
//using std::endl ; 

#include <fstream>
using std::ifstream ; 
using std::ofstream ; 
using std::ios ; 

#include <iomanip>


#include "blitzdefs.hpp"

#include <BlitzNet.hpp>
#include <BlitzXmlNetRenderer.hpp>
#include <TinyBzNetParser.hpp>

void fail(){
        cout << "failed" << endl ;
        exit(1) ; 
}


/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    cout << "I use the tinybzdir classes to read networks" << endl ; 

    // 1.  manually create a network
    BlitzNet* returnNet = new BlitzNet() ; 
    int numNeurons = 3 ; 
    returnNet->setNumNeurons(numNeurons) ; 
    Matrix* weights = new Matrix(numNeurons,numNeurons) ; 
    Matrix* weightMask  = new Matrix(numNeurons,numNeurons) ; 
    Vector* bias = new Vector(numNeurons) ; 
    Vector* tau = new Vector(numNeurons) ; 
    Vector* biasMask = new Vector(numNeurons) ; 
    Vector* tauMask = new Vector(numNeurons) ; 
    Vector* vinit = new Vector(numNeurons) ; 
    Vector* vmem = new Vector(numNeurons) ; 

    *weights = 
        	5,-7,3, 
        	-2,4,2, 
        	9,0,1; 
    *weightMask = 
            0,1,0,
    		1,0,1,
            0,0,0;
    *bias = -2,0,5 ; 
    *biasMask = 1,0,1 ; 
    *tau  = 3,21,7 ; 
    *tauMask  = 1,1,0 ; 
    *vinit = 0.5,0.5,1 ; 
    *vmem = 0,0.5,1 ; 

    
    returnNet->setWeights(weights) ; 
    returnNet->setWeightMask(weightMask) ; 
    returnNet->setBias(bias) ; 
    returnNet->setBiasMask(biasMask) ; 
    returnNet->setTau(tau) ; 
    returnNet->setTauMask(tauMask) ; 
    returnNet->setNeurons(vmem) ; 
    returnNet->setInitNeuron(vinit) ; 



    // 2.  use network render xml to render it to file
	BlitzXmlNetRenderer* netRenderer = new BlitzXmlNetRenderer() ; 
    netRenderer->render(returnNet); 
    ofstream streamWriter ; 
    streamWriter.open("testnet1.xml",ios::out) ; 
    streamWriter << netRenderer->render(returnNet) << endl ; 
    streamWriter.close() ; 

    
    // 3.  read that file using an xml renderer into a different network
    BlitzNet* readNet = NULL ; 
    TinyBzNetParser* netParser = new TinyBzNetParser() ; 
    readNet = netParser->parseFile("testnet1.xml") ; 
    
    // 4.  with luck, the network in 1 should agree with the network in 3

    if(readNet==NULL){
        fail() ; 
    }

    // compare size
    if(readNet->getNumNeurons()==returnNet->getNumNeurons()){
        cout << "same size" << endl ; 
    }

    cout << "read network: " << netRenderer->render(readNet) << endl ; 
    

   
    
    // compare bias 
    if( (*(readNet->getBias())) ==  (*(returnNet->getBias()))  ){
        cout << "biases match" << endl ; 
    }
    else{
        cout << "bias DO NOT match" << endl ; 
        fail() ; 
    }

    // compare bias mask
    if( (*(readNet->getBiasMask())) ==  (*(returnNet->getBiasMask()))  ){
        cout << "biasMaskes match" << endl ; 
    }
    else{
        cout << "biasMask DO NOT match" << endl ; 
        fail() ; 
    }


    // compare tau mask 
    if( (*(readNet->getTauMask())) ==  (*(returnNet->getTauMask()))  ){
        cout << "tauMasks match" << endl ; 
    }
    else{
        cout << "tauMasks DO NOT match" << endl ; 
        fail() ; 
    }

	
    
    // compare tau 
    if( (*(readNet->getTau())) ==  (*(returnNet->getTau()))  ){
        cout << "taus match" << endl ; 
    }
    else{
        cout << "taus DO NOT match" << endl ; 
        fail() ; 
    }
   
    // compare weight 
    if( *(readNet->getWeights()) == *(returnNet->getWeights()) ){
        cout << "weights pass" << endl ; 
    }
    else{
        cout << "weights fail" << endl ; 
        fail() ; 
    }

    // compare weight  mask 
    if( *(readNet->getWeightMask()) == *(returnNet->getWeightMask()) ){
        cout << "weightMask pass" << endl ; 
    }
    else{
        cout << "weightMask fail" << endl ; 
        fail() ; 
    }



    return 0;
} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--dev--1.4--patch-3/src/chemotestapps/netreader.cpp"
// LAST MODIFICATION: "Tue, 22 Jun 2004 15:37:21 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: netreader.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

