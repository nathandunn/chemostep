#include <iostream>
using std::cout ; 
using std::endl ; 

#include <sstream>
using std::ostringstream ; 

#include "FirstOrderImpulseFilter.hpp"
#include "blitzdefs.hpp"
#include "Label.hpp"


#include "FirstOrderLabel.hpp"

FirstOrderLabel::FirstOrderLabel(int newLabelCount) : Label(newLabelCount) 
{
}

FirstOrderLabel::FirstOrderLabel(int newLabelCount,double newTau,double newAmpl,DataFilter* newDataFilter) : Label(newLabelCount) 
{
    mTau = newTau ; 
    mAmpl = newAmpl ;
}


double FirstOrderLabel::getAmplitude() 
{
    return mAmpl ; 
}

double FirstOrderLabel::getTau() 
{
    return mTau ; 
}



void FirstOrderLabel::setTau(double newTau) 
{
    mTau = newTau ; 
}

void FirstOrderLabel::setAmplitude(double newAmpl) 
{
    mAmpl = newAmpl ; 
}



string FirstOrderLabel::print() 
{
//    ostringstream* outputString = new ostringstream() ; 
    ostringstream outputString  ; 
    outputString << "FirstOrderLabel: " ; 
    outputString << "error[" << mError  << "] " ; 
    outputString << "avgerror[" << mError / (getErrorPoints()) << "] " ; 
    outputString << "points[" << (getErrorPoints())<< "] " ; 
    outputString << endl ; 
    outputString << "M[" << mAmpl << "] tau[" << mTau << "]" ; 
    outputString << " -> M/tau * exp(-t/tau)  [" << mAmpl/mTau << " * exp(-t/" << mTau << ") ]" ;
        
    return outputString.str()   ; 
}





/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


