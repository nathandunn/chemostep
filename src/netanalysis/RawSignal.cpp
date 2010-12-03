
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "blitzdefs.hpp"

#include "RawSignal.hpp"


RawSignal::RawSignal(int numTimePoints,int numNeurons,double newTimeStep) 
{
    mData = new Matrix(numTimePoints,numNeurons) ; 
    mTimeStep = newTimeStep ; 
}

RawSignal::RawSignal(StlSignal* newSignal,double newTimeStep) 
{
    mTimeStep = newTimeStep ; 
    setSignal( newSignal) ; 
}

Matrix* RawSignal::getData() 
{
    return mData ; 
}

double RawSignal::getTimeStep() 
{
    return mTimeStep ; 
}



/**  This method sets mData from an StlSignal; 
 *
 */
void RawSignal::setSignal(StlSignal* newSignal) 
{
    // rows are time, columns are neuron number
    mData = new Matrix( ((*newSignal)[0])->size(),  newSignal->size()  ) ; 

    for(int timeCount = 0 ; timeCount < mData->rows() ; timeCount++){
        for(int neuronCount = 0 ; neuronCount < mData->columns() ; neuronCount++){
            (*mData)(timeCount,neuronCount) = (*((*newSignal)[neuronCount]))[timeCount]  ; 
        }
    }
}




double RawSignal::getTotalTime() 
{
    if(mData==NULL){
        return 0.0 ; 
    }
    return mData->rows() * mTimeStep ; 
}

int RawSignal::getNumNeurons() 
{
    if(mData==NULL){
        return 0 ; 
    }
    return mData->columns() ; 
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

