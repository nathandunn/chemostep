
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "ImpulseSignal.hpp"

ImpulseSignal::ImpulseSignal(ImpulseSignal* newSignal) 
{
   mData = new Matrix( *(newSignal->getData())  ) ; 
   mAmplitude = newSignal->getAmplitude() ; 
   mBaseline = newSignal->getBaseline() ; 
   mImpulseTime = newSignal->getImpulseTime() ; 
   mTimeStep = newSignal->getTimeStep() ; 
}


ImpulseSignal::ImpulseSignal(StlSignal* newSignal, double newAmplitude,double newBaseline,double newImpulseTime,double newTimeStep)  : RawSignal( newSignal,newTimeStep)
{
    mAmplitude = newAmplitude ; 
    mBaseline = newBaseline ; 
    mImpulseTime = newImpulseTime ; 
}


ImpulseSignal::ImpulseSignal(double newAmplitude,double newBaseline,double newImpulseTime,int numTimePoints,int numNeurons,double newTimeStep): RawSignal(numTimePoints,numNeurons,newTimeStep) 
{
    mAmplitude = newAmplitude ; 
    mBaseline = newBaseline ; 
    mImpulseTime = newImpulseTime ; 

//    mData = new Matrix(numTimePoints,numNeurons) ; 
//    mTimeStep = newTimeStep ; 
}


double ImpulseSignal::getAmplitude() 
{
    return mAmplitude ; 
}

double ImpulseSignal::getBaseline() 
{
    return mBaseline ; 
}

double ImpulseSignal::getImpulseTime() 
{
    return mImpulseTime ; 
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

