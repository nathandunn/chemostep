/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include <math.h>

#include "WindowFunction.hpp"
#include "PowerWindowFunction.hpp"

PowerWindowFunction::PowerWindowFunction( double newLowInput,double newHighInput, double newPower,double newLowOutput/*1.0*/,double  newHighOutput/*1.0*/) : WindowFunction() 
{
    mLowInput = newLowInput ; 
    mHighInput = newHighInput ; 
    mPower = newPower ; 
    mLowOutput = newLowOutput ; 
    mHighOutput = newHighOutput ; 
}


void PowerWindowFunction::setLowValue(double newLowValue) 
{
    mLowOutput = newLowValue ; 
}


void PowerWindowFunction::setHighValue(double newHighValue) 
{
    mHighOutput = newHighValue ; 
}


void PowerWindowFunction::setLowInput(double newLowInput) 
{
    mLowInput = newLowInput ; 
}


void PowerWindowFunction::setHighInput(double newHighInput) 
{
    mHighInput = newHighInput ; 
}



/// Naive window function.
double PowerWindowFunction::getValue( double inputValue) 
{
    if(inputValue > mHighInput){
        return 0.0 ; 
    }
    else{
        // Reversed order here since its hard to take the value of a power going the other way.
        return    mLowOutput * pow(  (inputValue-mHighInput)/(mLowInput-mHighInput),mPower)  + mHighOutput; 
    }
}

double PowerWindowFunction::getHighInput() 
{
    return mHighInput ; 
}

void PowerWindowFunction::toXML(ostream* s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<windowfunction type=\"powerwindowfunction\">" << endl ;
  addSpacer(s) ; 
  *s << "<lowinput value=\"" << mLowInput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<highinput value=\"" << mHighInput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<lowoutput value=\"" << mLowOutput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<highoutput value=\"" << mHighOutput << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<power value=\"" << mPower << "\" />" << endl ;
  addSpacer(s) ; 
  // close the XML
  *s << "</windowfunction>" << endl ;
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

