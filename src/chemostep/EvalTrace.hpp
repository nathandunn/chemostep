/*
 * $Id: EvalTrace.hpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $
 * This is the base class for output network data from the 
 * evaluator.  
 */
#ifndef EVALTRACE_HPP_
#  define EVALTRACE_HPP_

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

class NetEvaluator ; 

class EvalTrace {

public:
    EvalTrace() {}; 
    virtual void setEvaluator(NetEvaluator *newEvaluator) ;  /// this should be a memory call, since we want the same evaluator used int he network
    virtual string allNeuronTrace()=0 ; 
    virtual string lastNeuronTrace()=0 ; 
    virtual string neuronTrace(int neuronNum)=0 ; 
    virtual string errorTrace()=0 ; 
    virtual string targetTrace()=0 ; 
    virtual string stimTrace()=0 ; 
    virtual string targetTimeTrace()=0 ; 
    virtual string stimTimeTrace()=0 ; 
    virtual string combineTrace(string trace1,string trace2)=0 ;  /// combines output traces 
                                                          /// as strings into a single
                                                          /// output trace
    virtual string lastTimeStepNeurons()=0 ;      /// enables to to observe what neurons are doing
    virtual string neuronsAtTargetPoint(int point)=0 ;  
                                                          



protected:
    NetEvaluator *evaluator ; 

} ;

#endif /* ifndef EVALTRACE_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/chemostepAUTO/source/EvalTrace.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 15:04:03 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: EvalTrace.hpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $

