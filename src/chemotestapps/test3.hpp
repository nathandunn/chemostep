#ifndef test3_HPP_
#  define test3_HPP_

class TextEvalTrace ; 
class BlitzNet; 
class BlitzNetPerturber; 
class BlitzEulerNetEvaluator; 
class BinNetEvaluator ; 
class Feeder ; 
class KineticBlitzEulerEval ; 
/**
 *
 * This class ensures that the double-input values are evaluated, and output
 * values evaluate k01 and k10 values to P0 and P1 values.    
 *
 */
class test3 {

public:
    test3() ; 
    inline bool rendertests(string description, bool results) ; 
    bool initData() ; 
    int runtests() ; /// counts the number of tests it passes
    bool dotest1() ; /// A sample test to make sure that its running tests right.  
    bool dotest2() ; /// This test confers that one input and output are being evaluated correctly using KineticBlitzEulerEval. 
    bool dotest3() ; /// Confirms that the two inputs and one output works.  
    bool dotest4() ; /// Two inputs, one interneuron. (done)
    bool dotest5() ; /// Two inputs, two interneurons.
    bool dotest6() ; /// Two inputs, two interneurons, test relax.
    bool dotest7() ; /// Test Shawn's static network
    bool dotest8() ; /// Test Shawn's dynamic network
    bool dotest9() ; /// test up and downstep used in our toy2 problem
//    bool dotest10() ; /// parallel  train to Shawn's network (restricted)
//    bool dotest11() ; /// parallel  train to Shawn's network (unrestricted (8 interneuonrs)

protected:
    int testsPassed ; 
    int testsRun ; 
    StepFeeder* stimA  ; 
    FileFeeder* targetA  ; 
    StepFeeder* stimB  ; 
    FileFeeder* targetB  ; 
    StepFeeder* stimC  ; 
    StepFeeder* stimD  ; 
    FileFeeder* stimE; 
    FileFeeder* stimF; 
    FileFeeder* targetC  ; 
    FileFeeder* targetE  ; 
    NeuralNetwork* regNet ; 
    BlitzNet* blitzNet ; 
    BlitzNet* blitzNet4 ; 
    BlitzEulerNetEvaluator* blitzEval; 
    KineticBlitzEulerEval* kineticEval; 
    BinNetEvaluator* netEval ; 
    TextEvalTrace* tracer ; 
    Vector* tau ;
    Matrix* weights ;
    Vector* bias ;
    Vector* initNeuron ;


} ;

#endif /* ifndef test3_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/active/auto3/src/chemotestapps/test3.hpp"
// LAST MODIFICATION: "Tue, 16 Dec 2003 10:49:02 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: test3.hpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

