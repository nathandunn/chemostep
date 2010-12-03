
#include <iostream>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include "ErrorModel.hpp"
#include "LiveNet.h"
#include "blitzdefs.h"
#include "RNGblitz.h"
 

/*  ***********************************************************************************
    Default Constructor */
   
//! Uses default size and initial array contents set by calls to static class interface
/*  *********************************************************************************** */
LiveNet::LiveNet()
{
  setSize(iSize);
  weight = iWeight;
  vmem = iVmem;
  biasMask = iBiasMask;
  tau = iTau;
  tauMask = iTauMask;
  mask = iMask;
  input.resize(iSize) ; 
  sigma.resize(iSize) ; 

  valid = false;
}


/*  ***********************************************************************************
    Main constructor */
   
//! Oobject with the number of neurons specified.
/** Leave the weights and most other arrays at 0
    (users can supply these later via calls to setWeights(), etc).
    *********************************************************************************** */
LiveNet::LiveNet(int n)
{
  setSize(n);
  input.resize(n) ; 
  sigma.resize(n) ; 
  valid = false;
}


/*  ***********************************************************************************
    Copy constructor and assignment operator (NeuralNet) */
   
//! Make sure the Blitz vectors are copied correctly
/*  *********************************************************************************** */
LiveNet::LiveNet(const NeuralNet &that)
{
  *this = that;
}

/*  ***********************************************************************************
    Operator override (= NeuralNet) */
   
//! Description here
/*  *********************************************************************************** */
LiveNet& LiveNet::operator=(const NeuralNet &net)
{
  setSize(net.size());
  setWeights(net.getWeights()) ; 
  setBias(net.getBias()) ; 
  setTau(net.getTau()) ; 
  setBiasMask(net.getBiasMask()) ; 
  setTauMask(net.getTauMask()) ; 
  setMask(net.getMask()) ; 
  setOriginalError(net.getOriginalError()) ; 

//  cout << "size of input: " << input.size() << endl ; 
  valid = false ; 
}


/*  ***********************************************************************************
    Copy constructor and assignment operator (LiveNet) */
   
//! Make sure the Blitz vectors are copied correctly
/*  *********************************************************************************** */
LiveNet::LiveNet(const LiveNet &that)
{
  *this = that;
}


/*  ***********************************************************************************
    Operator override (= LiveNet) */
   
//! Description here
/*  *********************************************************************************** */
LiveNet& LiveNet::operator=(const LiveNet &net)
{
  setSize(net.nNeurons);
  setWeights(net.getWeights()) ; 
  setBias(net.getBias()) ; 
  setTau(net.getTau()) ; 
  setBiasMask(net.getBiasMask()) ; 
  setTauMask(net.getTauMask()) ; 
  setMask(net.getMask()) ; 
  input.resize(net.nNeurons) ; 
  sigma.resize(net.nNeurons) ; 
  setOriginalError(net.getOriginalError()) ; 

  cout << "size of input: " << input.size() << endl ; 
//  input(net.nNeurons) ; 
//  sigma(net.nNeurons) ; 
  valid = false ; 
}


/*  ***********************************************************************************
    Operator override (<<) */
   
//! Description here
/*  *********************************************************************************** */
// Stream output operator
ostream& operator<<(ostream &s, const LiveNet &net) 
{
  net.print(s);
  return s;
}


/*  ***********************************************************************************
    setSize() */
   
//! Set the number of neurons and allocate storage for the arrays
/*  *********************************************************************************** */
int LiveNet::setSize(const int n) 
{
  if (n < 3) {
    cerr << "NeuralNet::setSize(): minimum network size is 3 neurons; ignored" << endl;
    return 0 ;
  }

  nNeurons = n;

  weight.resize(n,n);
  vmem.resize(n);
  iVmem.resize(n);
  bias.resize(n);
  biasMask.resize(n);
  tau.resize(n);
  tauMask.resize(n);
  mask.resize(n,n);
  sigma.resize(n) ; 
  input.resize(n) ; 

  valid = false;
  return nNeurons ; 
}



/*  ***********************************************************************************
    print() */
   
//! Methods for printing the current state of the network
/*  *********************************************************************************** */
void LiveNet::print(ostream &s) const {
  if (valid)
    s << value;
  else
    s << "[??]";
}


/*  ***********************************************************************************
    evalPt() */
   
//! Description here
/*  *********************************************************************************** */
double LiveNet::evalPt(double conc) {
    // note bias added to input...
    input = vmem * weight + bias; 		
    
    // load into the first input
    //input(0) += stim(t);
    input(0) += conc ;
    sigma = (1.0 / (1.0 + exp(-input)));
    
    // euler's portion of the method
    vmem += ((sigma - vmem) / tau) * dt;
    //val += errorModel->getError(vmem(nNeurons-1),resp(t),&mappedOutput) ; 
    
    return vmem(nNeurons-1) ; 
} 


/*  ***********************************************************************************
    copy() */
   
//! Description here.
/*  *********************************************************************************** */
LiveNet* LiveNet::copy() const {
   LiveNet *aNet = new LiveNet(3) ; 
   aNet->setSize(this->nNeurons);
   aNet->setWeights(this->getWeights().copy()) ; 
   aNet->setBias(this->getBias().copy()) ; 
   aNet->setTau(this->getTau().copy()) ; 
   aNet->setBiasMask(this->getBiasMask().copy()) ; 
   aNet->setTauMask(this->getTauMask().copy()) ; 
   aNet->setMask(this->getMask().copy()) ; 
   aNet->setNeurons(this->initVmem.copy()) ; 
   aNet->setInitVmem(this->initVmem.copy()) ; 
   aNet->setErrorModel(this->getErrorModel()) ; 
//   aNet.setEvalModel(this->getEvalModelo) ; 
   aNet->invalidate() ; 
   return aNet ; 
}




