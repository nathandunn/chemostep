#ifndef WORSTPAIRONEWORMSIMEVAL_HPP_
#  define WORSTPAIRONEWORMSIMEVAL_HPP_

class WormLogger ;
#include "OneWormSimEval.hpp"
#include "blitzdefs.hpp"

/// This class takes the worst of two worms runs (assuming alternating pairs) and uses that in the average score.  
class WorstPairOneWormSimEval : public OneWormSimEval {

public:
    WorstPairOneWormSimEval() ;
    virtual void toXML(ostream *s) ; 

protected:
    virtual void calculateDistances( WormLogger* theLogger) ; 
    Vector* mDistVector1 ;
    Vector*  mDistVector2  ; 

    #ifdef DOMPI
    struct {
        double count1 ; 
        double sum1 ; 
        double count2 ; 
        double sum2 ; 
    } fromValues,toValues; 
    #endif
} ;

#endif /* ifndef WORSTPAIRONEWORMSIMEVAL_H */
// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


