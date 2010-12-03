/**
 * A feeder that has a start, stop, at step point
 */
#ifndef STEPFEEDER_HPP_
#  define STEPFEEDER_HPP_

#include "Feeder.hpp" 

class StepFeeder : public Feeder {

public:
    StepFeeder() ; 
    double getPreStepValue() {
        return(preStepValue);
    }
    void setPreStepValue(double _preStepValue) {
        preStepValue = _preStepValue;
        return;
    }
    double getPreStepTime() {
        return(preStepTime);
    }
    void setPreStepTime(double _preStepTime) {
        preStepTime = _preStepTime;
        stepAtTime = preStepTime ;  
        return;
    }
    double getPostStepValue() {
        return(postStepValue);
    }
    void setPostStepValue(double _postStepValue) {
        postStepValue = _postStepValue;
        return;
    }
    double getPostStepTime() {
        return(postStepTime);
    }
    void setPostStepTime(double _postStepTime) {
        postStepTime = _postStepTime;
        return;
    }
    double getStepAtTime() {
        return(stepAtTime);
    }

    virtual double getNextTimeStep(double newTimeStep=1.0, int pointAt=0) ;
//    virtual vector<double>* getNextTimeSteps(double newTimeStep=1.0) ; 
    virtual double getNextPoint(int pointAt=0) ; // defaults to the first datapoint
//    virtual vector<double>* getNextPoints() ;  
    virtual int getNumPoints() ; 
    virtual bool isTimePointValid() ; 
    virtual bool hasMorePoints() ; 
    virtual string getName() {  return FEEDER_NAME ; }  

    static const string FEEDER_NAME ; // name of feeder 

protected:
    double preStepValue ;
    double preStepTime;
    double postStepValue ; 
    double postStepTime; 
    double stepAtTime ;  // number of seconds to run the preStepValue



} ;

#endif /* ifndef STEPFEEDER_H */
// -*- C++ -*-

