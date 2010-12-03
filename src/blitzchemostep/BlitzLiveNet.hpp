
#ifndef _BlitzLiveNet_h_
#define _BlitzLiveNet_h_

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include "BlitzNet.hpp" 



class BlitzLiveNet : public BlitzNet {
public:

  BlitzLiveNet();
  BlitzLiveNet(BlitzLiveNet *n);
  BlitzLiveNet(BlitzNet *n);
  BlitzLiveNet& operator=(BlitzLiveNet &n);
  BlitzLiveNet& operator=(BlitzNet &n);
  virtual double evalPoint(double conc ,int numInputs=1) ; 


protected:
  vector<double>* concentrationPoint ; 

};

// Print-to-stream operator...


#endif


