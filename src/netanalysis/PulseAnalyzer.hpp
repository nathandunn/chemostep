/*
 * $Id$
 */
#ifndef PULSEANALYZER_HPP_
#  define PULSEANALYZER_HPP_


#include <vector>
using std::vector ; 

class PulseAnalyzer {

public:
    PulseAnalyzer() ; 
    vector<double>* getAmplitude( vector< vector<double>*>* fullTrace, int pulseLocation) ; 
    double getMaxAmplitude( vector<double>* timeSeries,int start) ; 

} ;

#endif /* ifndef PULSEANALYZER_H */
// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--prune--1.4.6--patch-20/src/netanalysis/PulseAnalyzer.hpp"
// LAST MODIFICATION: "Tue, 07 Sep 2004 17:57:00 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

