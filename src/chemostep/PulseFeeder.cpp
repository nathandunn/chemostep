/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "PulseFeeder.hpp"
#include "Feeder.hpp"

PulseFeeder::PulseFeeder() : Feeder(), mBaseline(0),mPulse(0),mPulseDuration(1), mPulseAt(0)
{
}

double PulseFeeder::getNextTimeStep(double newTimeStep/*1.0*/, int pointAt/*0*/) 
{
    double returnPoint ; 
    if(timeCounter< mPulseAt ||
        timeCounter >= (mPulseAt + mPulseDuration) ){
        returnPoint = mBaseline ; 
    }
    else{
        returnPoint = mPulse ; 
    }
    timeCounter = timeCounter + newTimeStep ; 
    pointCounter =  ((int) (timeCounter/deltaT)) ; 
    return ((returnPoint*scale) + offset)  ; 
}

double PulseFeeder::getNextPoint(int pointAt/*0*/) 
{
    double returnPoint ; 
    if(timeCounter< mPulseAt ||
        timeCounter >= (mPulseAt + mPulseDuration) ){
        returnPoint = mBaseline ; 
    }
    else{
        returnPoint = mPulse ; 
    }
    pointCounter++ ; 
    sigCounter++ ; 
    timeCounter = timeCounter + deltaT  ; 
    return ((returnPoint*scale) + offset)  ; 
}

int PulseFeeder::getNumPoints() 
{
    return (int) ceil( ( mTotalTime )/  deltaT )  ;  // make a call to ceiling to counter rounding-off errors on x86 
}

bool PulseFeeder::isTimePointValid() 
{
     float div = timeCounter/deltaT ; // for some stupid reason, this HAS to be a float, otherwise it performs floor wrong
     double floordiv = floor(div) ; 
     double ceildiv = ceil(div) ; 
     return (floordiv==ceildiv) ;
}

bool PulseFeeder::hasMorePoints() 
{
   return ( timeCounter < mTotalTime)  ; 
}

const string PulseFeeder::FEEDER_NAME = "PULSE_FEEDER" ; 






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
// FILE: "/Users/nathandunn/svn/chemostep-nathan/src/chemostep/PulseFeeder.cpp"
// LAST MODIFICATION: "Fri, 22 Jul 2005 08:45:09 -0700 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

