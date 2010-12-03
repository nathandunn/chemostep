#include <iostream>
using std::cout ; 
using std::endl ; 

#include <sstream>
using std::ostringstream ; 

#include "SecondOrderImpulseFilter.hpp"
#include "blitzdefs.hpp"
#include "Label.hpp"


#include "SecondOrderLabel.hpp"

SecondOrderLabel::SecondOrderLabel(int newLabelCount) : Label(newLabelCount) 
{
}

SecondOrderLabel::SecondOrderLabel(int newLabelCount,double newDecay,double newAmpl,double newPeriod,double newPhaseShift,DataFilter* newDataFilter) : Label(newLabelCount) 
{
    mDecay = newDecay ; 
    mAmpl = newAmpl ;
    mPeriod = newPeriod ; 
    mPhaseShift = newPhaseShift ; 
}


double SecondOrderLabel::getAmplitude() 
{
    return mAmpl ; 
}

double SecondOrderLabel::getDecay() 
{
    return mDecay ; 
}

double SecondOrderLabel::getPeriod() 
{
    return mPeriod ; 
}

double SecondOrderLabel::getPhaseShift() 
{
    return mPhaseShift ; 
}




void SecondOrderLabel::setAmplitude(double newAmpl) 
{
    mAmpl = newAmpl ; 
}

void SecondOrderLabel::setPeriod(double newPeriod) 
{
    mPeriod = newPeriod ; 
}

void SecondOrderLabel::setPhaseShift(double newPhaseShift) 
{
    mPhaseShift = newPhaseShift ; 
}

void SecondOrderLabel::setDecay(double newDecay) 
{
    mDecay = newDecay ; 
}



string SecondOrderLabel::print() 
{
//    ostringstream* outputString = new ostringstream() ; 
    ostringstream outputString  ; 
    outputString << "SecondOrderLabel: " ; 
    outputString << "error[" << mError  << "] " ; 
    outputString << "avgerror[" << mError / (getErrorPoints()) << "] " ; 
    outputString << "points[" << (getErrorPoints())<< "] " ; 
    outputString << endl ; 
    outputString << "M[" << mAmpl << "] decay[" << mDecay << "] P[" << mPeriod << "] Phi[" << mPhaseShift << "]" ; 
    outputString << " -> M*exp(-decay*t)*sin(P*t+phi) [" << mAmpl << "*exp(-" << mDecay << "t)*sin(" << mPeriod << "*t+"<<mPhaseShift<< ") ]" ;
        
    return outputString.str()   ; 
}





/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


