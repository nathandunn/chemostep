// -*- C++ -*-
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>




#include <sstream>
using std::ostringstream;


#include <string>
using std::string; 


#include "BlitzReportNetRenderer.hpp"
#include "BlitzNet.hpp" 


string BlitzReportNetRenderer::render(BlitzNet *net){

ostringstream outputStream(ostringstream::out)  ; 


    cout << "----- Notes from BlitzReportNetRenderer\t-----------------------------" << endl;
    outputStream << "  neurons:\t "     << net->getNumNeurons()    << endl << endl;
    outputStream << "  value:\t "       << net->eval()             << endl << endl;
    outputStream << "  weights:\t "     << *(net->getWeights())    << endl << endl;
    outputStream << "  bias:\t "        << *(net->getBias())       << endl << endl;
    outputStream << "  tau:\t "         << *(net->getTau())        << endl << endl;
    outputStream << "  vmem:\t "        << *(net->getNeurons())    << endl << endl;
    outputStream << "  init vmem:\t "   << *(net->getInitNeuron()) << endl << endl;
    outputStream << "  weight mask:\t " << *(net->getWeightMask()) << endl << endl;
    outputStream << "  biasMask:\t "    << *(net->getBiasMask())   << endl << endl;
    outputStream << "  tauMask:\t "     << *(net->getTauMask())    << endl << endl;
    
    //      cout << "returning: " << outputStream.str() << endl ;  
    return outputStream.str() ; 
    
}



