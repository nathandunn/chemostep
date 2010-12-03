
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <math.h>

#include "PowerWindowFunction.hpp"

#include "InflectionWindowFunction.hpp"

InflectionWindowFunction::InflectionWindowFunction( double newLowInput,double newHighInput, double newPower/*1.0*/,double newLowOutput/*1.0*/,double  newHighOutput/*1.0*/,double newRatio) 
    :PowerWindowFunction( newLowInput,newHighInput,newPower,newLowOutput,newHighOutput)
    ,mRatio(newRatio)  
{ }

/// Returns PowerWindowFunction for points less than the inflection point (mHighInput), a negative function of the same if greater, and -mLowOutput if greater than 2*mHighInput.  
double InflectionWindowFunction::getValue( double inputValue) 
{
    // pre-inflection point
    if(inputValue < mHighInput ){
        // Reversed order here since its hard to tae the value of a power going the other way.
        return    mLowOutput * pow(  (inputValue-mHighInput)/(mLowInput-mHighInput),mPower)  + mHighOutput; 
    }
    // post-inflection point
    else
    if(inputValue >= mHighInput && inputValue < 2* mHighInput){
        return   mRatio * ( - mLowOutput * pow(  (inputValue- mHighInput)/(mHighInput-mLowInput),mPower)  + mHighOutput ) ; 
    }
    // post-symmetry point
    else
    if(inputValue >= 2*mHighInput ){
        return mRatio * ( -mLowOutput ) ; 
    }

}

void InflectionWindowFunction::toXML(ostream* s) 
{
  // open the XML
  addSpacer(s,1) ; 
  *s << "<windowfunction type=\"inflectionwindowfunction\">" << endl ;
  addSpacer(s) ; 
  *s << "<lowinput value=\"" << mLowInput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<highinput value=\"" << mHighInput << "\" description=\"inflectionpoint\" />" << endl ;
  addSpacer(s) ; 
  *s << "<lowoutput value=\"" << mLowOutput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<highoutput value=\"" << mHighOutput << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<invlectionratio value=\"" << mRatio << "\" />" << endl ;
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

