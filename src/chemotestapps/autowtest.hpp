#ifndef autowtest_HPP_
#  define autowtest_HPP_

class TextEvalTrace ; 
class BlitzNet; 
class BlitzNetPerturber; 
class BlitzEulerNetEvaluator; 
class BinNetEvaluator ; 
class Feeder ; 
class AutoWKineticBlitzEulerEval; 
/**
 *
 * This class ensures that the double-input values are evaluated, and output
 * values evaluate k01 and k10 values to P0 and P1 values.    
 *
 */
class autowtest {

public:
    autowtest() ; 
    inline bool rendertests(string description, bool results) ; 
    bool initData() ; 
    int runtests() ; /// counts the number of tests it passes
    bool dotest1() ; 
    bool dotest2() ; 

protected:
    int testsPassed ; 
    int testsRun ; 
    BlitzNet* blitzNet ; 
    BlitzEulerNetEvaluator* blitzEval; 
    AutoWKineticBlitzEulerEval* evaluator ; 
    BinNetEvaluator* netEval ; 
    TextEvalTrace* tracer ; 
    Vector* tau ;
    Vector* tauMask ;
    Matrix* weights ;
    Matrix* weightMask ;
    Vector* bias ;
    Vector* biasMask ;
    Vector* initNeuron ;
    Vector* initNeuronMask ;
    FileFeeder* stimLeft ; 
    FileFeeder* stimRight ; 
    FileFeeder* targetSet ; 


} ;

#endif /* ifndef autowtest_H */
// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemotestapps/autowtest.hpp"
// LAST MODIFICATION: "Sun, 14 Dec 2003 00:16:05 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: autowtest.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

