#ifndef NETEVALUATOR_HPP_
#  define NETEVALUATOR_HPP_

#include <vector>
using std::vector ; 

#include <iostream>
using std::ostream ; 

#include "XmlRenderable.hpp"

class NeuralNetwork ; 
class Feeder ; 
class EvalTrace ; 
class FeederSet ; 

/**  Base class that evaluates error for NeuralNetwork and its derivatives.
 *
 *  \todo Add a method which NeuralNetwork can call which will return a hash-list of options of the form hashset<key,value> which will have all of the optional pairs.
 */

class NetEvaluator : public XmlRenderable {

public:
    NetEvaluator() ;
    ~NetEvaluator() ;
    virtual double eval(NeuralNetwork* network) ; 
    virtual double evalNorml(NeuralNetwork* network) ; /// This class returns the error per second.
    virtual void setStimulus(Feeder* newStimulus,int inputNum=0) ;
    virtual void setTarget(Feeder* newTarget,int inputNum=0) ; 
    virtual double getSdev() { return 0 ; } 
    virtual double getHAvg() { return 0 ; }  /// This is the average input into the output neuron(s).
    virtual int getCount() { return 1 ; } 
    virtual Feeder* getStimulus(int inputNum=0) ;
    virtual Feeder* getTarget(int inputNum=0) ; 
    virtual vector<Feeder*>* getFullStimulus() ;
    virtual vector<Feeder*>* getFullTarget() ;
    virtual void setNetwork(NeuralNetwork* newNetwork) ;  
    virtual vector<double>* getLastTrace(int neuronNum=-1) ;   // defaults to last one
    virtual vector<vector<double>*>* getLastFullTrace() { return neuronTrace ; };  
    virtual vector<vector<double>*>* getLastFullTraceAsSeries()  ; 
    virtual vector<double>* getAllNeuronFinalTrace(int timePoint=-1)  ; 
    virtual vector<double>* getLastErrorTrace() { return errorTrace ; };  
    virtual void relaxNet(bool doTrace=false) ;  
//    virtual double getRelaxLimit() ; 
//    virtual void setRelaxLimit(double _mRelaxLimit) ; 
    virtual void setRelaxTime(double newRelaxTime) { mRelaxTime = newRelaxTime ;  }
    virtual void setRelaxDeltaT(double newRelaxDeltaT){ mRelaxDeltaT = newRelaxDeltaT ;  } ;  
    virtual void setRelaxTau(double newRelaxTau) ; 
    virtual void setRelaxValue(double newRelaxValue) ; 
    virtual void setRelaxValue(vector<double>* newRelaxValue) { mRelaxValueVector = newRelaxValue ;  };  
    virtual double getRelaxTime(){return mRelaxTime; } ; 
    virtual double getRelaxDeltaT(){return mRelaxDeltaT; } ; 
//    virtual double getRelaxValue(){return mRelaxValue; } ; 
    virtual vector<double>* getRelaxValueVector(){return mRelaxValueVector; } ; 
    virtual double getMinDeltaT() ; 
    virtual double evalPoint(vector<double>* stimVector,bool doTrace=true) ;  /// Calculates output 
    virtual double evalPoint(double newPoint,bool doTrace=true) ;
    virtual void toXML(ostream *s) ; 


protected:
    virtual void doBaseXML(ostream *s) ; /// This method handles feeders, etc.  
    virtual bool initEvaluator() { return true ; }     /// Internally resets any values of the NetEvaluator, if need be.
    virtual void resetTrace(int neuronPoints,int errorPoints) ;  
    virtual bool resetNet() { return true ;  }
    virtual void addNeuronTrace(vector<double>* newPoint) ;  
    virtual void addErrorTrace(double newError)  ;  
    FeederSet* stimulus ; 
    FeederSet* target ; 
    NeuralNetwork* network ; 
    vector<vector<double>*>* neuronTrace ;  // these may be something else, later
    vector<double>* errorTrace ;  // these may be something else later
    vector<double>*  outputVector ; 
    int currentNeuronPoint  ; 
    int currentErrorPoint; 
    double mRelaxTau ; 
//    double mRelaxLimit ; 
    double mRelaxTime ; 
    double mRelaxDeltaT ; 
//    double mRelaxValue  ; 
    vector<double>* mRelaxValueVector  ; 
    double localDt;  // loaded once and then used during calculations

    double maxTime ; 
    double mMinDeltaT; 
    int totalPoints ; 
    int theErrorPoints ; 
    double netOutput; 

    int numNeurons ;
    int numStimulus ; 
    int numTargets ; 
    int neuronCounter ; 
    int numSets ; 

    vector<double>* inputVector ; 
    vector<double>* tempVector ; 


} ;

#endif /* ifndef NETEVALUATOR_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

