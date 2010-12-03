
#ifndef _LiveNet_h_
#define _LiveNet_h_

#include <iostream>
using std::ostream;
using std::cout;
using std::endl;

#include "blitzdefs.h" 
#include "NeuralNet.h" 



class LiveNet : public NeuralNet  {
public:

  LiveNet();
  LiveNet(int n);
  LiveNet(const LiveNet &n);
  LiveNet(const NeuralNet &n);
  virtual double evalPt(double conc ) ; 
  virtual int setSize(const int newSize) ; 
  virtual void print(ostream &s) const;
  virtual LiveNet *copy() const ; 
  virtual LiveNet& operator=(const LiveNet &n);
  virtual LiveNet& operator=(const NeuralNet &n);

protected:
  Vector input;	// calculated input to each neuron
  Vector sigma;
};

// Print-to-stream operator...

ostream& operator<<(ostream &s, const LiveNet &n);

#endif


