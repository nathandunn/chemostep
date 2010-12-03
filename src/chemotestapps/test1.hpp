/*
 * $Id: test1.hpp,v 1.2 2003/10/31 19:50:12 ndunn Exp $
 */
#ifndef TEST1_HPP_
#  define TEST1_HPP_

class TextEvalTrace ; 
class BlitzNet; 
class BlitzNetPerturber; 
class BlitzEulerNetEvaluator; 
class BinNetEvaluator ; 
class Feeder ; 
/**
 *
 *  This class is a series of checked-tests which ensure that neural networks
 *  function properly, both blitz and otherwise.
 *
 */
class test1 {

public:
    test1() ; 
    inline bool rendertests(string description, bool results) ; 
    bool initData() ; 
    int runtests() ; /// counts the number of tests it passes
    bool dotest1() ; 
    bool dotest2() ; 
    bool dotest3() ; 
    bool dotest4() ; 
    bool dotest5() ; 
    bool dotest6() ; 
    bool dotest7() ; 
    bool dotest8() ; 
    bool dotest9() ; 
    bool dotest10() ; 
    bool dotest11() ; 
    bool dotest12() ; 
    bool dotest13() ; 
    bool dotest14() ; 
    bool dotest15() ; 
    bool dotest16() ; 
    bool dotest17() ; 
    bool dotest18() ; 

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
    BlitzEulerNetEvaluator* blitzEval; 
    BinNetEvaluator* netEval ; 
    TextEvalTrace* tracer ; 
    Vector* tau ;
    Matrix* weights ;
    Vector* bias ;
    Vector* initNeuron ;


} ;

#endif /* ifndef TEST1_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto3/src/chemotestapps/test1.hpp"
// LAST MODIFICATION: "Wed, 29 Oct 2003 16:37:19 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: test1.hpp,v 1.2 2003/10/31 19:50:12 ndunn Exp $

