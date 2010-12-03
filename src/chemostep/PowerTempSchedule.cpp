
#include <iostream>
using std::cout ; 
using std::endl ; 


#include "PowerTempSchedule.hpp"

PowerTempSchedule::PowerTempSchedule(int numPoints, double newPower,double start, double stop):TempSchedule(numPoints,start,stop){
    hasInitTemps = false ; 
    power = newPower ; 
    initTemps() ; 
}; 

double PowerTempSchedule::getNextTemp(double deltaError,vector<double>* variables) {
  
  if(!hasInitTemps){
    cout << "temps not initiallized, initializing temps" << endl ;
    initTemps() ;
  }

  if(counter < numPoints){
    // this is something I was messing around with: seeing how
    //  the error changed with only a few of the temperatures being used.
    // if (counter > 3)
    //   counter = numPoints;
    // else
    //   counter++;
    // return (*tempSchedule)[counter] ; 
    return (*tempSchedule)[counter++] ; 
    
  }
  else{
    hasInitTemps= false ; 
    throw "Ran out of points in PowerTempSchedule" ; 
  }
}

void PowerTempSchedule::initTemps() 
{
  tempSchedule = new vector<double>(numPoints) ; 
  counter = 0 ; 
  double currentT = highTemp ; 
  currentTemp = highTemp ; 
  double ratio ; 
  double diff = (lowTemp - highTemp )/((double)  numPoints -1 ) ; 
  for(int i = 0  ; i < numPoints ; ++i ) {
      ratio = (currentT - lowTemp ) / (highTemp - lowTemp ) ; 
      if(ratio < 0) ratio = 0 ;   // can occur dueo to roundoff errors
      (*tempSchedule)[i] =  (double) ((pow(ratio,power)*(highTemp- lowTemp))  + lowTemp) ;  
      // cout << " tempSchedule[" << i << "] = " << (*tempSchedule)[i] << " " << endl ; 
      currentT += diff ; 
  }
  hasInitTemps=true ;  
}

void PowerTempSchedule::toXML(ostream *s) 
{
  addSpacer(s,1) ; 
  *s << "<tempschedule type=\"powertempschedule\">" << endl ;
  addSpacer(s) ; 
  *s << "<numpoints value=\"" << numPoints << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<hightemp value=\"" << highTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<lowtemp value=\"" << lowTemp << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<power value=\"" << power << "\" />" << endl ;
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
