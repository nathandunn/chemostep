/**
 *  \brief  A test-suite of applications.  
 *
 *  \todo  Make tests parallel, so that each node must come in with an answer. 
 */
#ifndef test2_HPP_
#  define test2_HPP_

class TextEvalTrace ; 
class BlitzNet; 
class PowerTempSchedule ; 
class BlitzNetPerturber; 
class BlitzEulerNetEvaluator; 
class BlitzNetAnnealer ; 
class BlitzNetPerturber ; 
class BinNetEvaluator ; 
class Feeder ; 
/**
 *
 *  This class is a series of checked-tests which ensure that neural networks
 *  function properly, both blitz and otherwise.
 *
 *  \test Init neuron should be carried around through annealing.
 *  \test Relax-neuron should be set to first-value of each stim-session. 
 *  \test Set output for tau to min.
 *
 */
class test2 {

public:
    test2() ; 
    inline bool rendertests(string description, bool results) ; 
    bool initData() ; 
    int runtests() ; /// counts the number of tests it passes
    bool dotest1() ; 
    bool dotest2() ; 
    bool dotest3() ; 

protected:
    int testsPassed ; 
    int testsRun ; 
    StepFeeder* stimA  ; 
    FileFeeder* targetA  ; 
    StepFeeder* stimB  ; 
    FileFeeder* targetB  ; 
    StepFeeder* stimC  ; 
    FileFeeder* targetC  ; 
    NeuralNetwork* regNet ; 
    BlitzNet* blitzNet ; 
    PowerTempSchedule* tempSchedule ; 
    BlitzNetAnnealer* annealer ; 
    BlitzNetPerturber* perturber ; 
    BlitzEulerNetEvaluator* blitzEval; 
    BinNetEvaluator* netEval ; 
    TextEvalTrace* tracer ; 
    Vector* tau ;
    Matrix* weights ;
    Vector* bias ;
    Vector* initNeuron ;


} ;

#endif /* ifndef test2_H */
// -*- C++ -*-
// LAST MODIFICATION: "Mon, 03 Nov 2003 18:13:52 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: test2.hpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

