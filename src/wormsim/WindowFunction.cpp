/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "WindowFunction.hpp"

WindowFunction::WindowFunction(double newMaxInputWindow,double newMaxOutput /*1.0 */) 
    : mLowOutput(0)  
{
    mHighInput= newMaxInputWindow ; 
    mHighOutput = newMaxOutput ; 
    mLowOutput = newMaxOutput ; 
}

/// Basically returns the mHighOutput and mLowOutput (should be the same) if less than the window size.  So a square WindowFunction.  
double WindowFunction::getValue( double inputValue) 
{
    if(inputValue < mHighInput){
        return mHighOutput ; 
    }
    else{
        return 0 ; 
    }
}

void WindowFunction::toXML(ostream* s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<windowfunction type=\"windowfunction\">" << endl ;
  addSpacer(s) ; 
  *s << "<lowinput value=\"" << mLowInput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<highinput value=\"" << mHighInput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<lowoutput value=\"" << mLowOutput << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<highoutput value=\"" << mHighOutput << "\" />" << endl ;
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
// FILE: "/Users/nathandunn/svn/chemotrunk/src/wormsim/WindowFunction.cpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 12:27:15 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

