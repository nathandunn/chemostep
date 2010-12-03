// -*- C++ -*-
//
#ifndef ANNEALTEST1_HPP_
#  define ANNEALTEST1_HPP_


class TextEvalTrace ; 
class BlitzNet; 
class BlitzNetPerturber; 
class BlitzEulerNetEvaluator; 
class BinNetEvaluator ; 
class Feeder ; 

/**  A test class to verify annealing.  
 *
 *  \todo  Try the same using Huen's evaluation (R-K 2nd) (14.8, p. 574)
 *  \todo  Trapezoid rule, back and forward avg (14.16, p.577)
 *  
 */

class annealtest1 {

public:
    annealtest1()  ; 
    bool test1() ;  // add evaluator tracer
    bool test2() ;  // add the average error
    bool test3() ;  // add the significance finder
    bool test4() ;  // add a network reader in tinyxml
    bool test5() ;  // try small deltaT

protected:
    BlitzNet* net  ; 
    Feeder* stimFeeder ; 
    Feeder* targetFeeder ; 
    BinNetEvaluator* evaluator  ; 
    BlitzNetPerturber* perturber ; 
    TextEvalTrace* tracer ; 

} ;

#endif /* ifndef ANNEALTEST1_H */

