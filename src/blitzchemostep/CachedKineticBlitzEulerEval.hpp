#ifndef CACHEDKINETICBLITZEULEREVAL_HPP_
#  define CACHEDKINETICBLITZEULEREVAL_HPP_

#include "KineticBlitzEulerEval.hpp" 


/** This class is responsible for evaluating a stochastic output network.
 */
class CachedKineticBlitzEulerEval : public KineticBlitzEulerEval {

public:
    CachedKineticBlitzEulerEval() ; 
    ~CachedKineticBlitzEulerEval() ; 
    virtual double eval(NeuralNetwork* evalNetwork) ;
    virtual bool cacheFeeders() ; 
    virtual void toXML(ostream *s) ;

protected:
    Matrix* cacheStimulusVector ; 
    Matrix* cacheTargetVector; 
    Vector* cacheSetLengthsVector ; 


} ;

#endif /* ifndef CACHEDKINETICBLITZEULEREVAL_HPP_*/
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: CachedKineticBlitzEulerEval.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

