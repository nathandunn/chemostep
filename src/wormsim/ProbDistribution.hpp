
#ifndef PROBDISTRIBUTION_HPP_
#  define PROBDISTRIBUTION_HPP_

#include <vector>
using std::vector ; 

#include <utility>
using std::pair ; 

typedef pair<double,double> Bin ;  /// Defined as lowBin, highBin


class ProbDistribution {

public:
    ProbDistribution(double newBinSize,double maxSize=1,double minSize=0)  ; 
    virtual void setDistribution( Vector* wormRadii) ; 
    virtual int getNumBins() ; 
    virtual Bin getBin(int binNumber) ; 
    virtual double getBinMax(int binNumber) ; 
    virtual int getBinForValue(double value) ; 
    virtual double getValueForBin(int binNumber) ; 

    // for plotting
    virtual vector<double>* getDoublePlot() ; 

protected:
    virtual void initBins() ; 
    double mBinSize ; 
    double mMaxSize ; 
    double mMinSize ; 
    Matrix* mBinVector ;  /// column 0 are the low bin values, column2 are the high bin values, and column 3 are the actual bin values

    #ifdef DOMPI
    int probDistProcSize ; 
    double* probDenst ; 
    Vector* mTransferVector ; 
    #endif

} ;

#endif /* ifndef PROBDISTRIBUTION_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.4.8--base-0/src/wormsim/ProbDistribution.hpp"
// LAST MODIFICATION: "Mon, 20 Sep 2004 16:33:18 -0700 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

