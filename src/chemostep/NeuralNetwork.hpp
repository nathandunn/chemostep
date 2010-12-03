// -*- C++ -*-

#ifndef _NEURALNETWORK_HPP_
#define _NEURALNETWORK_HPP_

#include "AnnealingTarget.hpp" 


#include <string>
using std::string ; 

class NetPerturber ; 
class NetEvaluator ; 
class Note ; 

/**The base neural network class.  
 *  Although the "valid" flag is used, most calls made occur after a change to the neural network has already been made.
 *  
 */

class NeuralNetwork: public AnnealingTarget{

public:
    NeuralNetwork()   ; 
    virtual AnnealingTarget* perturb(double temp) ; 
    virtual double eval() ; 
    virtual double getSdev() ; 
    virtual int getCount() ; 
    virtual double evalNorml() ;   /// gives the evaluation normal to the number of evaluation points
    virtual void setPerturber(NetPerturber *newPerturber) { perturber = newPerturber ; } 
    virtual NetPerturber* getPerturber() { return perturber ; } 
    virtual void setEvaluator(NetEvaluator *newEvaluator)  ; 
    virtual NetEvaluator* getEvaluator() { return evaluator ; } 
    virtual bool reset() { return true ;  }  ///  returns neurons to their original values
    virtual bool relax() { return true ;  }  ///  allows neurons to change for a period of time based on a constant input in order to relax between evaluations.
    virtual int getNumNeurons() { return 0;  }  /// returns the number of neurons 
    virtual void setValue(double _value) ;
    virtual Note* getNote() ; 
    virtual void setNote(Note* newNote) ; 

    
    virtual bool getValid() ;
    virtual void setValid(bool _valid) ;
    virtual double getValue() ;



protected:
    NetPerturber* perturber ; 
    NetEvaluator* evaluator ; 
    bool valid ; 
    double value ; 
    Note* mNote ; 

} ; 


#endif

