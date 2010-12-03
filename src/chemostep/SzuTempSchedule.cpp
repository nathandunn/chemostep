
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "GeometricTempSchedule.hpp"
#include "SzuTempSchedule.hpp"

SzuTempSchedule::SzuTempSchedule(int newNumPoints, double newHighTemp,double newLowTemp)  : GeometricTempSchedule(newNumPoints,newHighTemp,newLowTemp)
{
}

SzuTempSchedule::SzuTempSchedule() : GeometricTempSchedule()  
{
}


void SzuTempSchedule::initTemps() 
{
    double f = ( highTemp - lowTemp) / (lowTemp *  ( numPoints - 1.0) ) ; 
    tempSchedule = new vector<double>(numPoints) ; 

    for(int i = 0 ; i < numPoints ; i++){
        (*tempSchedule)[i] = highTemp / ( 1.0  +  (  f * i ) )  ; 
    }

    counter = 0 ; 

    return ; 


}



void SzuTempSchedule::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<tempschedule type=\"szutempschedule\">" << endl ;
  addSpacer(s) ; 
  *s << "<numpoints value=\"" << numPoints << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<hightemp value=\"" << highTemp << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<lowtemp value=\"" << lowTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "</tempschedule>" << endl ;
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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

