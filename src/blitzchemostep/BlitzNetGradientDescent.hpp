#ifndef BLITZNETGRADIENTDESCENT_HPP_
#  define BLITZNETGRADIENTDESCENT_HPP_

#include "GradDescent.hpp"

class TrainingTarget ; 

/** A class that implements simple local-search.  
 *  Probably use an iterative line-optimization algorithm
 *  with or without back-prop.
 *
 *  \todo Finish implementation.  
 *
 */
class BlitzNetGradientDescent : public GradDescent {

public:
    BlitzNetGradientDescent() ; 
    TrainingTarget* train() ; 
    void setNetwork(BlitzNet* newNet) ; 
    void setMaxIters(int newMaxIters) ; 
    void setFudgeValue(double newFudgeValue) ; 
    void setMinImprovement(double newMinImprovment) ; 

protected:
    BlitzNet* network ; 
    int maxIters ; 
    double fudgeValue ; 
    double minImprovmement ; 


} ;

#endif /* ifndef BLITZNETGRADIENTDESCENT_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto3TWOINPUTSTEP/src/blitzchemostep/BlitzNetGradientDescent.hpp"
// LAST MODIFICATION: "Fri, 09 Jan 2004 18:39:23 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: BlitzNetGradientDescent.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

