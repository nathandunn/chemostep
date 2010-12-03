/*
 * $Id: BlitzEulerPerturber.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */
#ifndef BLITZEULERPERTURBER_HPP_
#  define BLITZEULERPERTURBER_HPP_

#include "BlitzNetPerturber.hpp" 
#include "RNG.hpp" 

class BlitzEulerPerturber : public BlitzNetPerturber {

public:
    BlitzEulerPerturber():BlitzNetPerturber(){ }   // the first call, calls initSeed() 
    virtual NeuralNetwork* perturb(double temp,NeuralNetwork* newNet) ; 
    virtual void toXML(ostream *s) ; 


protected:
    static double TAU_MIN ; 
} ;

#endif /* ifndef BLITZNETPERTURBER_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/blitzchemostep/BlitzEulerPerturber.hpp"
// LAST MODIFICATION: "Mon, 29 Nov 2004 16:09:50 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzEulerPerturber.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

