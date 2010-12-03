
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "TempSchedule.hpp"

#include "GeometricTempSchedule.hpp"

GeometricTempSchedule::GeometricTempSchedule() : TempSchedule() 
{
}


GeometricTempSchedule::GeometricTempSchedule(int newNumPoints, double newHighTemp,double newLowTemp) : TempSchedule(newNumPoints,newHighTemp,newLowTemp) 
{

}


double GeometricTempSchedule::getNextTemp(double deltaError/*0.0*/,vector<double>* variables)
{
    return (*tempSchedule)[counter++] ; 
}

void GeometricTempSchedule::initTemps() 
{
    double f = pow ( (highTemp/lowTemp) , ( 1.0 / numPoints ) ) ; 
    tempSchedule = new vector<double>(numPoints) ; 

    (*tempSchedule)[0] = highTemp ; 
    for(int i = 1 ; i < numPoints ; i++){
        (*tempSchedule)[i] = (*tempSchedule)[i-1] / f ; 
    }

    counter = 0 ; 

    return ; 
}






void GeometricTempSchedule::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<tempschedule type=\"geometrictempschedule\">" << endl ;
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

