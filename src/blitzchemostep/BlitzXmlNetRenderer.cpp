#include <iostream>
using std::endl ; 
using std::cout ; 

#include <sstream>
using std::ostringstream ; 

#include "BlitzXmlNetRenderer.hpp"
#include "BlitzNet.hpp"
#include "Note.hpp"
#include <XmlRenderable.hpp>

BlitzXmlNetRenderer::BlitzXmlNetRenderer() : BlitzNetRenderer()
,mOutputStream(new ostringstream()) 
{
}


string BlitzXmlNetRenderer::render(BlitzNet* net) 
{
    int nNeurons = net->getNumNeurons() ; 
    Vector* bias = net->getBias() ; 
    Vector* tau = net->getTau() ; 
    Vector* initVmem= net->getInitNeuron() ; 
    Matrix* weight = net->getWeights() ; 
    Vector* biasMask = net->getBiasMask() ; 
    Vector* tauMask = net->getTauMask() ; 
    Vector* vmem = net->getNeurons() ; 
    Matrix* mask = net->getWeightMask() ; 
    Vector* gain = net->getGain() ; 
    Vector* gainMask = net->getGainMask() ; 


    mOutputStream->str("") ; 

 
  // dump the network start tag
  *mOutputStream << "<" << NET_NETWORK << " " << NET_SIZE << "=\"" << nNeurons << "\" >\n" ;
  
  XmlRenderable::setNumTabs(1) ; 
//  // add evaluation note

  if(net->getNote()!=NULL){
      *mOutputStream <<   (net->getNote()->toXML())   ; 
  }

  if(net->getPerturber()!=NULL){
      (net->getPerturber()->toXML(mOutputStream))   ; 
  }

  if(net->getEvaluator()!=NULL){
      (net->getEvaluator())->toXML(mOutputStream)  ; 
  }


//  // dump the neurons
  for(int i = 0 ; i < nNeurons ; i++ ) {
    *mOutputStream << "<" << NET_NODE << " " << NET_NODE_NUMBER << "=\"" << i <<"\">\n" ;
    *mOutputStream << "  <" << NET_BIAS << " " << NET_VALUE << "=\"" << (*bias)(i) <<"\" " << NET_MASK << "=\""<<(*biasMask)(i)<<"\"/>" << endl  ;
    *mOutputStream << "  <" << NET_TAU << " " << NET_VALUE << "=\"" << (*tau)(i) <<"\" " << NET_MASK << "=\""<<(*tauMask)(i)<<"\"/>" << endl;  
    if(gainMask!=NULL && i < gainMask->size()) { 
        *mOutputStream << "  <" << NET_GAIN << " " << NET_VALUE << "=\"" << (*gain)(i) <<"\" " << NET_MASK << "=\""<<(*gainMask)(i)<<"\"/>" << endl;  
    }
    else{
        *mOutputStream << "  <" << NET_GAIN << " " << NET_VALUE << "=\"" << 1.0 <<"\" " << NET_MASK << "=\""<< 0.0 <<"\"/>" << endl;  

    }
    *mOutputStream << "  <" << NET_VMEM << " " << NET_VALUE << "=\"" << (*vmem)(i) <<"\"/>" << endl ;
    *mOutputStream << "  <" << NET_VINIT << " " << NET_VALUE << "=\"" << (*initVmem)(i) <<"\"/>" << endl ;
    *mOutputStream << "</" << NET_NODE << ">\n" ;
  }

  // dump the weights
  for(int i = 0 ; i < nNeurons ; i++) {
    for(int j = 0 ; j < nNeurons ; j++) {
        *mOutputStream << "<" << NET_WEIGHT  ;
        *mOutputStream << " " << NET_NODE_FROM << "=\"" << i << "\""  ;
        *mOutputStream << " " << NET_NODE_TO << "=\"" << j << "\""  ;
        *mOutputStream << " " << NET_WEIGHT << "=\"" << (*weight)(i,j) << "\""  ;
        *mOutputStream << " " << NET_MASK << "=\"" << (*mask)(i,j) << "\""  ;
        *mOutputStream << "/>" << endl ; 
    }
  }
  


  // end the network
  *mOutputStream <<  "</" << NET_NETWORK << ">" << endl  ;
  mOutputStream->flush() ; 
  return mOutputStream->str() ; 
}






