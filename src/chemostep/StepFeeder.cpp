#include <vector>
using std::vector ; 

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "StepFeeder.hpp"

StepFeeder::StepFeeder() : Feeder(), preStepValue(0),postStepValue(0),postStepTime(0),preStepTime(0),stepAtTime(0)
{
}


double StepFeeder::getNextTimeStep(double newTimeStep, int inputNum) 
{
    double returnPoint ; 
    if(timeCounter>=stepAtTime){
        returnPoint = postStepValue; 
    }
    else{
        returnPoint = preStepValue ; 
    }
    timeCounter = timeCounter + newTimeStep ; 
    pointCounter =  ((int) (timeCounter/deltaT)) ; 
    return ((returnPoint*scale) + offset)  ; 
}

//vector<double>* StepFeeder::getNextTimeSteps(double newTimeStep) 
//{
//    double returnPoint ; 
//    vector<double>* returnVector  = new vector<double>(); 
//    if(timeCounter>=stepAtTime){
//        returnPoint = postStepValue ; 
//    }
//    else{
//        returnPoint = preStepValue ; 
//    }
//    returnVector->push_back(returnPoint) ; 
//    timeCounter = timeCounter + newTimeStep ; 
//    pointCounter =  ((int) (timeCounter/deltaT)) ; 
//    return returnVector ; 
//}

double StepFeeder::getNextPoint(int pointAt) 
{
    double returnPoint ; 
    if(timeCounter>=stepAtTime){
        returnPoint = postStepValue; 
    }
    else{
        returnPoint = preStepValue ; 
    }
    pointCounter++ ; 
    sigCounter++ ; 
    timeCounter = timeCounter + deltaT  ; 
    return ((returnPoint*scale) + offset)  ; 
}


//vector<double>* StepFeeder::getNextPoints() 
//{
//    double returnPoint ; 
//    vector<double>* returnVector  = new vector<double>(); 
//    if(timeCounter>=stepAtTime){
//        returnPoint = postStepValue; 
//    }
//    else{
//        returnPoint = preStepValue; 
//    }
//    returnVector->push_back(returnPoint) ; 
//    pointCounter++ ; 
//    timeCounter = timeCounter + deltaT  ; 
//    return returnVector ; 
//}


int StepFeeder::getNumPoints() 
{
    return (int) ceil( ( preStepTime+postStepTime)/  deltaT )  ;  // make a call to ceiling to counter rounding-off errors on x86 
}

/// We need to see if the current time point is divisible by deltaT.  This is more often the case for the stimulus versus the target.  
bool StepFeeder::isTimePointValid() 
{
     float div = timeCounter/deltaT ; // for some stupid reason, this HAS to be a float, otherwise it performs floor wrong
     double floordiv = floor(div) ; 
     double ceildiv = ceil(div) ; 
     return (floordiv==ceildiv) ;
}


bool StepFeeder::hasMorePoints() 
{
    return (timeCounter< (preStepTime+postStepTime)) ; 
}

const string StepFeeder::FEEDER_NAME = "STEP_FEEDER" ; 


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/home/ndunn/cvs/auto3TWOINPUTSTEP/src/chemostep/StepFeeder.cpp"
// LAST MODIFICATION: "Tue, 16 Dec 2003 16:45:59 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

