/*
 * $Id$
 */
#ifndef PULSEFEEDER_HPP_
#  define PULSEFEEDER_HPP_

#include "Feeder.hpp" 

class PulseFeeder : public Feeder{

public:
    PulseFeeder() ; 
    virtual double getNextTimeStep(double newTimeStep=1.0, int pointAt=0) ;
//    virtual vector<double>* getNextTimeSteps(double newTimeStep=1.0) ; 
    virtual double getNextPoint(int pointAt=0) ; // defaults to the first datapoint
//    virtual vector<double>* getNextPoints() ;  
    virtual int getNumPoints() ; 
    virtual bool isTimePointValid() ; 
    virtual bool hasMorePoints() ; 
    virtual string getName() {  return FEEDER_NAME ; }  

    static const string FEEDER_NAME ; // name of feeder 



    double getBaseline() {
        return(mBaseline);
    }
    void setBaseline(double _mBaseline) {
        mBaseline = _mBaseline;
        return;
    }
    double getPulse() {
        return(mPulse);
    }
    void setPulse(double _mPulse) {
        mPulse = _mPulse;
        return;
    }
    double getPulseDuration() {
        return(mPulseDuration);
    }
    void setPulseDuration(double _mPulseDuration) {
        mPulseDuration = _mPulseDuration;
        return;
    }
    double getPulseAt() {
        return(mPulseAt);
    }
    void setPulseAt(double _mPulseAt) {
        mPulseAt = _mPulseAt;
        return;
    }
    double getTotalTime() {
        return(mTotalTime);
    }
    void setTotalTime(double _mTotalTime) {
        mTotalTime = _mTotalTime;
        return;
    }



protected:
    double  mBaseline ; 
    double  mPulse ; 
    double  mPulseDuration ; 
    double  mPulseAt  ; 
    double  mTotalTime ; 

} ;

#endif /* ifndef PULSEFEEDER_H */
// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--prune--1.4.6--base-0/src/chemostep/PulseFeeder.hpp"
// LAST MODIFICATION: "Tue, 31 Aug 2004 13:52:07 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

