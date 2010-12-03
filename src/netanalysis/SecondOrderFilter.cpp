#include <iostream>
using std::cout ; 
using std::endl ; 


#include "blitzdefs.hpp"
#include "SecondOrderFilter.hpp"

SecondOrderFilter::SecondOrderFilter() : DataFilter() 
,mSecondOrderDecay(NULL)
,mSecondOrderAmplitude(NULL)
,mSecondOrderPeriod(NULL)
,mSecondOrderPhaseShift(NULL)
{
    
}


double SecondOrderFilter::getAmplitude(int signalNumber) 
{
    return (*mSecondOrderAmplitude)(signalNumber) ; 
}


double SecondOrderFilter::getDecay(int signalNumber) 
{
    return (*mSecondOrderDecay)(signalNumber) ; 
}

double SecondOrderFilter::getPeriod(int signalNumber) 
{
    return (*mSecondOrderPeriod)(signalNumber) ; 
}

double SecondOrderFilter::getPhaseShift(int signalNumber) 
{
    return (*mSecondOrderPhaseShift)(signalNumber) ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


