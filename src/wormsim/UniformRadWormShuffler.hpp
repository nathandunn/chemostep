/*
 * $Id$
 */
#ifndef UNIFORMRADWORMSHUFFLER_HPP_
#  define UNIFORMRADWORMSHUFFLER_HPP_

#include <iostream>
using std::ostream ; 

#include "WormShuffler.hpp"


/// This class extends WormShuffler and uses the RNG class to give a uniform distribution of worms on a radial plate with a uniform distribution of initial orientations.
class UniformRadWormShuffler : public WormShuffler {

public:
    UniformRadWormShuffler(double diameter) ; 
    virtual void shuffleWorm(BaseWorm* aWorm) ; 
    virtual void toXML(ostream *s) ; 

protected:
    double mDiameter ; 

} ;

#endif /* ifndef UNIFORMRADWORMSHUFFLER_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemostep-square/src/wormsim/UniformRadWormShuffler.hpp"
// LAST MODIFICATION: "Fri, 17 Dec 2004 15:24:15 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

