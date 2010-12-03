// -*- C++ -*-
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: BlitzCSVNetRenderer.cpp,v 1.1.1.1 2003/10/24 19:59:24 ndunn Exp $

#include <sstream>
using std::ostringstream;

#include "BlitzNet.hpp"
#include "BlitzCSVNetRenderer.hpp"

BlitzCSVNetRenderer::BlitzCSVNetRenderer(string aDelimiter){
   delimiter = aDelimiter ; 
}

string BlitzCSVNetRenderer::render(BlitzNet* net) {

ostringstream outputStream  ; 

  // dump the weight values
  Matrix *weights = net->getWeights() ; 
  int size = net->getNumNeurons() ; 
  for(int from = 0 ; from < size  ; from++){
      for(int to = 0 ; to < size  ; to++){
         outputStream << from << delimiter << to << delimiter << (*weights)(from,to)  << endl ; 
      }
  }
 

      // dump the bias values
      Vector *bias = net->getBias() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream << from << delimiter <<  (*bias)(from)  << endl ; 
      }

      // dump the tau values
      Vector *tau = net->getTau() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream << from << delimiter << (*tau)(from)  << endl ; 
      }
      
      // dump the vinit values
      Vector *vinit = net->getInitNeuron() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream << from << delimiter <<  (*vinit)(from)  << endl ; 
      }


      // dump any addiotional info, like error or model type
      outputStream << "error: " << net->eval() << endl ; 
      outputStream << "  init vmem:    " << net->getInitNeuron()<< endl;
      outputStream << "  weight mask:    " << net->getWeightMask() << endl;
      outputStream << "  biasMask:    " << net->getBiasMask() << endl;
      outputStream << "  tauMask:     " << net->getTauMask() << endl;

return outputStream.str() ; 

}



