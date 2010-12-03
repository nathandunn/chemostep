/*
 * $Id: BlitzGainWrapPerturber.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */
#ifndef BLITZGAINWRAPPERTURBER_HPP_
#  define BLITZGAINWRAPPERTURBER_HPP_

#include "BlitzEulerWrapPerturber.hpp" 

#include <float.h>

/// This class applies high and low limits to each variable from a wrap value, uniformly, and perturbs the gain function, as well.This class also makes the assumption that its it uses a BlitzGainNet.
class BlitzGainWrapPerturber : public BlitzEulerWrapPerturber {

public:
    BlitzGainWrapPerturber(double newWrapValue=DBL_MAX) ; // the first call, calls initSeed() 
    virtual NeuralNetwork* perturb(double temp,NeuralNetwork* newNet) ; 
    virtual void toXML(ostream *s) ; 


} ;

#endif 
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzGainWrapPerturber.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

