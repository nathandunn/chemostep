/*
 * $Id: BlitzEulerWrapPerturber.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */
#ifndef BLITZEULERWRAPPERTURBER_HPP_
#  define BLITZEULERWRAPPERTURBER_HPP_

#include <float.h>

#include "BlitzEulerPerturber.hpp" 

// This class applies high and low limits to each variable from a wrap value, uniformly.
class BlitzEulerWrapPerturber : public BlitzEulerPerturber {

public:
    BlitzEulerWrapPerturber(double newWrapValue=DBL_MAX) ; // the first call, calls initSeed() 
    virtual NeuralNetwork* perturb(double temp,NeuralNetwork* newNet) ; 
    virtual void toXML(ostream *s) ; 


protected:
    virtual double checkValue(double checkValue) ; 
    double mWrapValue ; 

} ;

#endif /* ifndef BLITZNETPERTURBER_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzEulerWrapPerturber.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

