// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--nathanevo--1.4.2--base-0/src/blitzchemostep/BlitzFlatCSVNetRenderer.cpp"
// LAST MODIFICATION: "Wed, 30 Jun 2004 13:42:16 -0700 (ndunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: BlitzFlatCSVNetRenderer.cpp,v 1.1.1.1 2003/10/24 19:59:25 ndunn Exp $

#include <sstream>
using std::ostringstream;

#include "BlitzFlatCSVNetRenderer.hpp"
#include "BlitzNet.hpp"


string BlitzFlatCSVNetRenderer::render(BlitzNet* net) {

    ostringstream outputStream  ; 
   double normal = 1.0 ; 
  int size = net->getNumNeurons() ; 

  // dump the header for the file, if there is a lot of detail


      
      // dump any addiotional info, like error or model type
      for(int from = 0 ; from < size  ; from++){
          for(int to = 0 ; to < size  ; to++){
             outputStream << "wt" <<  from << to << delimiter   ; 
          }
      }
      // dump the bias values
      for(int from = 0 ; from < size  ; from++){
         outputStream <<    "bias" << from  << delimiter ; 
      }

      // dump the tau values
      Vector *tau = net->getTau() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream <<    "tau" << from  << delimiter ; 
      }
      
      // dump the vinit values
      Vector *vinit = net->getInitNeuron() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream <<    "vinit" << from  << delimiter ; 
      }

      outputStream << endl ;


  // dump the weight values
  Matrix *weights = net->getWeights() ; 

  if(normal>0){
      double theMax = getMax( (*weights)) ; 
      double theMin = getMin( (*weights) ) ; 

      if(theMax>fabs(theMin)){
         (*weights) = normal * (*weights) / theMax ; 
      }else{
         (*weights) = normal * (*weights) / fabs(theMin) ; 
      }
  }

  for(int from = 0 ; from < size  ; from++){
      for(int to = 0 ; to < size  ; to++){
         outputStream << (*weights)(from,to) << delimiter   ; 
      }
  }

 

      // dump the bias values
      Vector *bias = net->getBias() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream <<    (*bias)(from)  << delimiter ; 
      }

      // dump the tau values
//      Vector *tau = net->getTau() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream <<   (*tau)(from)  << delimiter ; 
      }
      
      // dump the vinit values
//      Vector *vinit = net->getInitNeuron() ; 
      for(int from = 0 ; from < size  ; from++){
         outputStream <<   (*vinit)(from)  << delimiter ; 
      }

  outputStream << endl ; 

  return outputStream.str() ; 

}



