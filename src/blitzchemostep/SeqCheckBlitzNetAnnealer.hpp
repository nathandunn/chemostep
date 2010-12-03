
#ifndef SEQCHECKBLITZNETANNEALER_HPP_
#  define SEQCHECKBLITZNETANNEALER_HPP_

#include "SeqBlitzNetAnnealer.hpp" 

#include <iostream>
using std::ostream ;


class SeqCheckBlitzNetAnnealer : public SeqBlitzNetAnnealer {

public:
    SeqCheckBlitzNetAnnealer() ;
    // virtual void compareNet(double *acceptVars) ;

    // virtual AnnealingTarget* anneal( ostream *toXML=NULL) ; 

    void setNumChecks(int _mNumChecks) { mNumChecks = _mNumChecks; } ;

    void setMinInitialImprovement(double _mMinInitialImprovement) {
	mMinInitialImprovement = _mMinInitialImprovement;
    } ;
    
private:
    // mNumChecks is the number of verifications the annealer does
    //  to make sure the results aren't a fluke
    int mNumChecks ;

    // mMinInitialImprovement, if set to < 1.0, requires the network
    //  to improve at the initial temperature by the given percentage
    //  before continuing to additional temperatures.
    double mMinInitialImprovement ;
} ;

#endif 
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

