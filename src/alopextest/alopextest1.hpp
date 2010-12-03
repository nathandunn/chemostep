
#ifndef ALOPEXTEST1_HPP_
#  define ALOPEXTEST1_HPP_



class TextEvalTrace ; 
class BlitzNet; 
class BlitzNetAlopexPerturber;
class BlitzNetAlopexer;
class BlitzEulerNetEvaluator; 
class BinNetEvaluator ; 
class Feeder ;


class alopextest1 {

public:
    alopextest1()  ; 
    bool test2() ;  // Try the alopexPerturber.
		bool test3() ;

protected:
    BlitzNet* net  ; 
    Feeder* stimFeeder ; 
    Feeder* targetFeeder ; 
    BinNetEvaluator* evaluator  ; 
    BlitzNetAlopexPerturber* perturber ; 
		BlitzNetAlopexer* optimizer;
    TextEvalTrace* tracer ; 

} ;

#endif /* ifndef ALOPEXTEST1_H */

