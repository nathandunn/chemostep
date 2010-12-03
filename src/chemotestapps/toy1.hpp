#ifndef TOY1_HPP_
#  define TOY1_HPP_

class BlitzNet ; 
class StepFeeder ; 
class FileFeeder ; 
class SetFeeder; 
class BlitzEulerNetEvaluator ; 
class TextEvalTrace ; 
class PowerTempSchedule ; 
class BlitzNetAnnealer ; 

#include "blitzdefs.hpp" 

/**
 *  \brief A class for creating toy problems, and possibly solving for them.
 *
 *  1.  This test puts together a net that gives the desired property (quick proportional change).  
 *  2.  It confirms that the desired net output is given (confirmed with igor).
 *  3.  Using an empty network, it tries to train for our network using the appopriate data.   
 *
 */
class toy1 {

public:
    toy1() ; 
    bool createToy() ; 
    bool createEvaluator() ; 
    bool createAnnealer() ; 
    bool anneal() ; 

protected:
    BlitzNet* toyNet ; 
    BlitzEulerNetEvaluator* blitzEval ; 
    TextEvalTrace* tracer ; 
    SetFeeder* stimulus ; 
    SetFeeder* target ; 
    StepFeeder* stimA; 
    StepFeeder* stimB; 
    FileFeeder* targetA ; 
    FileFeeder* targetB ; 
    Matrix* weights ; 
    Vector* tau ; 
    Vector* bias ; 
    Vector* initNeuron ; 
    PowerTempSchedule* tempSchedule ; 
    BlitzNetPerturber* perturber ; 
    BlitzNet* trainNet ; 
    BlitzNetAnnealer* annealer ; 

} ;

#endif /* ifndef TOY1_H */
// -*- C++ -*-
// FILE: "/home/ndunn/cvs/auto3/src/chemotestapps/toy1.hpp"
// LAST MODIFICATION: "Sun, 02 Nov 2003 18:26:31 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: toy1.hpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

