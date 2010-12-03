#ifndef FEEDERSET_HPP_
#  define FEEDERSET_HPP_

#include <vector>
using std::vector ; 

#include "Feeder.hpp" 

/**
 * This class defines multiple feeder inputs/outputs.  It is a wrapper around a vector of feeders, but its methods
 * look at all values. 
 * Because it mirrors all of the same functionality as a regular singular feeder class, it extends Feeder.
 */
class FeederSet : public Feeder {

public:
    FeederSet() ; 

    virtual bool reset() ; 
    virtual bool hasMorePoints() ; 
    virtual void setFeeder(Feeder* newFeeder, int inputNum=0) ; 
    virtual Feeder* getFeeder(int inputNum=0) ; 
    virtual vector<Feeder*>* getFeederVector() { return feedVector ;  }
    virtual double getDeltaT() ; 
    virtual double getTotalTime() ; 
    virtual double getCurrentTime() ; 
    virtual bool isNewSet() ; 
    virtual bool isTimePointValid() ; 
    virtual double getNextTimeStep(double newTimeStep=1.0, int inputNum=0) ; 
    virtual vector<double>* getNextTimeStepVector(double newTimeStep=1.0) ; 
    virtual int getNumInputs() ; 
    virtual double getNextPoint(int inputNum=0.0) ; 
    virtual int getNumPoints() ; 
    virtual double getNextSigTimeStep(double newTimeStep,int inputNum  ) ; 
    virtual string getName() {  return FEEDER_NAME ; }  
    virtual int getNumSets() ;  /// Gets the offset of from the feeder outp
    


    static const string FEEDER_NAME ; // name of feeder 

protected:
    vector<Feeder*>* feedVector ; 
    vector<double>* timeStepVector ; 

} ;

#endif /* ifndef FEEDERSET_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/FeederSet.hpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 10:03:24 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: FeederSet.hpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

