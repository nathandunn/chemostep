#ifndef KINETICBLITZEULEREVAL_HPP_
#  define KINETICBLITZEULEREVAL_HPP_

#include <fstream>
using std::ofstream ; 

#include "BlitzEulerNetEvaluator.hpp" 


/** This class is responsible for evaluating a stochastic output network.
 */
class KineticBlitzEulerEval : public BlitzEulerNetEvaluator {

public:
    KineticBlitzEulerEval() ; 
    ~KineticBlitzEulerEval() ; 
    virtual void setK01(double newK01) ; 
    virtual void setK10(double newK10) ; 
    virtual void setP1(double newP1) ; 
    virtual void setP0(double newP0) ; 
    virtual void toXML(ostream *s) ;

protected:
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;
    virtual bool initEvaluator() ;

    double k01 ; 
    double k10 ; 
    double P1 ; 
    double P0 ; 
    double initP0 ; 
    double initP1 ; 
    double sumh  ; 

    static const int RIGHT = 1;
    static const int LEFT = 0;

} ;

#endif /* ifndef KINETICBLITZEULEREVAL_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: KineticBlitzEulerEval.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

