
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "StepSignal.hpp"

StepSignal::StepSignal(StepSignal* newSignal) 
{
   mData = new Matrix( *(newSignal->getData())  ) ; 
   mAmplitude = newSignal->getAmplitude() ; 
   mBaseline = newSignal->getBaseline() ; 
   mStepTime = newSignal->getStepTime() ; 
   mTimeStep = newSignal->getTimeStep() ; 
}


StepSignal::StepSignal(StlSignal* newSignal, double newAmplitude,double newBaseline,double newStepTime,double newTimeStep)  : RawSignal( newSignal,newTimeStep)
{
    mAmplitude = newAmplitude ; 
    mBaseline = newBaseline ; 
    mStepTime = newStepTime ; 
}


StepSignal::StepSignal(double newAmplitude,double newBaseline,double newStepTime,int numTimePoints,int numNeurons,double newTimeStep): RawSignal(numTimePoints,numNeurons,newTimeStep) 
{
    mAmplitude = newAmplitude ; 
    mBaseline = newBaseline ; 
    mStepTime = newStepTime ; 

//    mData = new Matrix(numTimePoints,numNeurons) ; 
//    mTimeStep = newTimeStep ; 
}


double StepSignal::getAmplitude() 
{
    return mAmplitude ; 
}

double StepSignal::getBaseline() 
{
    return mBaseline ; 
}

double StepSignal::getStepTime() 
{
    return mStepTime ; 
}




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
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

