#ifndef AUTOWKINETICBLITZEULEREVAL_HPP_
#  define AUTOWKINETICBLITZEULEREVAL_HPP_

#include "KineticBlitzEulerEval.hpp" 
/**
 *  This class . . . 
 */
class AutoWKineticBlitzEulerEval : public KineticBlitzEulerEval {

public:
    AutoWKineticBlitzEulerEval() ; 
    ~AutoWKineticBlitzEulerEval() ; 
    virtual double eval(NeuralNetwork* newNetwork) ;  /// Evaluate a given trace.  Optimize w., and then return that error with the w.
    virtual double getBestW() ; 
    virtual double setBestW(double newBestW) ; 
    virtual double getInitDeltaW() ; 
    virtual void setInitDeltaW(double newInitDeltaW) ; 
    virtual void setLowDeltaValue(double newLowDeltaValue) ; 

protected:
    virtual double eval(vector<double>* stimVector,bool doTrace=true) ;
    virtual double calculateError(double currentW,bool doTrace=false) ; /// Determine error for a given w.
    virtual double findBestError(double initW) ; /// Optimize w for the target using gradient descent (or a variation thereof). 
    double bestW ; 
    vector<double>* hVector ; 
    double testW, bestTestW, testError ; 
    bool doTrace ; 
    double initDeltaW ; 
    double initLowDeltaValue ; 



} ;

#endif /* ifndef KINETICBLITZEULEREVAL_H */
// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/blitzchemostep/AutoWKineticBlitzEulerEval.hpp"
// LAST MODIFICATION: "Fri, 12 Dec 2003 23:01:19 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AutoWKineticBlitzEulerEval.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

