#ifndef BLITZEULERNETEVALUATOR_HPP_
#  define BLITZEULERNETEVALUATOR_HPP_

#include "BlitzNetEvaluator.hpp" 
#include "blitzdefs.hpp"

/**  
 * Evaluates BlitzNet networks using Eulers method.
 *
 */

class BlitzEulerNetEvaluator : public BlitzNetEvaluator {

public:
    BlitzEulerNetEvaluator() ; 
    ~BlitzEulerNetEvaluator() ; 
    virtual void setNetwork(NeuralNetwork* newNetwork) ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;
    virtual double getMinDeltaT() ; 
    virtual void toXML(ostream *s) ; 

    static const double EULER_MIN_TAU ; 

protected:
    void checkTau() ;  // defines the min tau
    Vector *sigma ; 
    Vector *input ; 
    vector<double>* tempVector ; // for evalPoint(double,bool) 

} ;

#endif /* ifndef BLITZEULERNETEVALUATOR_H */
// -*- C++ -*-

