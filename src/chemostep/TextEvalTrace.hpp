/**
 *   Creates a text output for text.  
 *
 *   \todo Implement combineTrace(string output1,string output2).
 */
#ifndef TEXTEVALTRACE_HPP_
#  define TEXTEVALTRACE_HPP_

#include "EvalTrace.hpp" 

#include <vector>
using std::vector ; 

class Feeder ; 


/**
 *   Creates a text output for text.  
 *
 *   \todo Implement combineTrace(string output1,string output2).
 */

class TextEvalTrace : public EvalTrace {

public:
    TextEvalTrace() ;
    virtual string allNeuronTrace() ; 
    virtual string lastNeuronTrace() ; 
    virtual string neuronTrace(int neuronNum) ; 
    virtual string errorTrace() ; 
    virtual string targetTrace() ; 
    virtual string stimTrace() ; 
    virtual string targetTimeTrace() ; 
    virtual string stimTimeTrace() ; 
    virtual string combineTrace(string trace1,string trace2) ;  // combines output traces 
                                                          // as strings into a single
                                                          // output trace
    virtual string lastTimeStepNeurons() ;  // enables to to observe what neurons are doing
    virtual string neuronsAtTargetPoint(int point) ;  // enables to to observe what neurons are doing

    string getTimeDelimiter() {
        return(timeDelimiter);
    }
    void setTimeDelimiter(string _timeDelimiter) {
        timeDelimiter = _timeDelimiter;
        return;
    }

    string getValueDelimiter() {
        return(valueDelimiter);
    }
    void setValueDelimiter(string _valueDelimiter) {
        valueDelimiter = _valueDelimiter;
        return;
    }



protected:
    string dumpFeederTrace(Feeder* feeder) ; 
    string dumpTimeStep(double timeStep) ; 
    string dumpSingleTrace() ; 
    vector<vector<double>*>* fullTrace ; 
    vector<double>* singleTrace ; 


    static string timeDelimiter  ; 
    static string valueDelimiter ; 
} ;

#endif /* ifndef TEXTEVALTRACE_H */
// -*- C++ -*-

