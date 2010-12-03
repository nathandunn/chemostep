

#ifndef RAWSIGNAL_HPP_
#  define RAWSIGNAL_HPP_

#include <vector>
using std::vector ; 

#include "blitzdefs.hpp"

typedef vector<vector<double>*> StlSignal ;

/**  This class represents the raw signal vector of any blitz type.  Subclasses will have important points of note for it, like points of impulse, baseline amplitude, etc.
 *
 */
class RawSignal {

public:
    RawSignal(int numNeurons=0,int numTimePoints=0,double newTimeStep=1.0) ; 
    RawSignal(StlSignal* newSignal,double newTimeStep=1.0) ; 
    virtual double getTotalTime() ; 
    virtual int getNumNeurons() ; 
    virtual void setSignal(StlSignal* newSignal) ; 
    virtual Matrix* getData() ; 
    virtual double getTimeStep() ; 


protected:
    Matrix *mData ; /// This field defines an array of T.  The first type is the row is the time, and the second column data-point (neuron). 
    double mTimeStep ; /// This is the difference in time between points.
    
   

} ;

#endif /* ifndef RAWSIGNAL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

