#ifndef BINNETEVALUATOR_HPP_
#  define BINNETEVALUATOR_HPP_

#include "NetEvaluator.hpp" 

/**  
 * 
 * \brief This class is responsible for evaluating neural networks
 *        by averaging data when the number of stimulus inputs is
 *        greater than the number of output inputs.  
 * \bug   Need to fix a bug, whereby the stimulus deltaT < 0.1, the
 *        error reduces, and the number of evaluated points doesn't
 *        finish.
 * \todo  During relaxation, use the value of the first input as the relaxation value.
 *
 Evaluates networks averaging target data.  This method is essentially the same as the NetEvaluator, but it avareges the network output if there is more than one stimulus (and therefore network output) per target  timestep.   asdf
 */


class BinNetEvaluator : public NetEvaluator {

public:
    BinNetEvaluator() ; 
    virtual double eval(NeuralNetwork* network) ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ; 
    virtual void toXML(ostream *s) ; 

protected:
    virtual bool resetRelax()   ; 
    int stimCount  ; 
    int targetCount; 
    double totalNetOutput  ; 
} ;

#endif /* ifndef BINNETEVALUATOR_H */
// -*- C++ -*-

