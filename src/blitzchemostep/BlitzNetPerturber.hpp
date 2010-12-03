/*
 * $Id: BlitzNetPerturber.hpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $
 */
#ifndef BLITZNETPERTURBER_HPP_
#  define BLITZNETPERTURBER_HPP_

#include "NetPerturber.hpp" 
#include "RNG.hpp" 

class BlitzNetPerturber : public NetPerturber {

public:
    BlitzNetPerturber():NetPerturber(){ }   // the first call, calls initSeed() 
    virtual NeuralNetwork* perturb(double temp,NeuralNetwork* newNet) ; 
    virtual void toXML(ostream *s) ; 

} ;

#endif /* ifndef BLITZNETPERTURBER_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemotrunk/src/blitzchemostep/BlitzNetPerturber.hpp"
// LAST MODIFICATION: "Mon, 29 Nov 2004 16:18:56 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzNetPerturber.hpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $

