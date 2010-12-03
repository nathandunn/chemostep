// -*- C++ -*-
//
/// A class which provides methods which could be called by the Annealer.  
// 
#ifndef ANNEALING_TARGET_HPP_
#  define ANNEALING_TARGET_HPP_

#include "TrainingTarget.hpp"

class AnnealingTarget : public TrainingTarget {

public:
    AnnealingTarget(){} ; 
    virtual AnnealingTarget* perturb(double temp)=0 ; 

} ;

#endif /* ifndef ANNEALING_TARGET_H */

