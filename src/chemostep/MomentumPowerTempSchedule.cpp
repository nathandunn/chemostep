#include "MomentumPowerTempSchedule.hpp"


MomentumPowerTempSchedule::MomentumPowerTempSchedule(int numPoints, double newPower, double newConstant, double start, double stop):PowerTempSchedule(numPoints,newPower,start,stop){
    if(newConstant<=1.0){
        cerr << "Constant must be > 1.0!!!.  Throwing error." << endl ; 
        cout << "Constant must be > 1.0!!!.  Throwing error." << endl ; 
        throw  "Constant must be > 1.0!!!.  Throwing error." ; 
    }
  currentTemp = start ; 
  hasInitTemps = false ; 
  power = newPower ; 
  constant = newConstant ;
  deltaErrorSum = 0.0 ; 
  initTemps() ; 
}; 

double MomentumPowerTempSchedule::getNextTemp(double deltaError,vector<double>* variables) {
  if(!hasInitTemps){
    cout << "temps not initiallized, initializing temps" << endl ;
    initTemps() ;
  }

  deltaErrorSum = ( deltaErrorSum +  deltaError ) / constant ; 
  if(deltaErrorSum <0) {
      deltaErrorSum = 0 ; 
  }

  if(counter < numPoints  ){
      currentTemp = (*tempSchedule)[counter++] + ( deltaErrorSum  ) ; 
  }
  else{
      // Don't reduce the temperature the first time through.
      if (counter++ != 0) {
	  currentTemp = (currentTemp / constant) + deltaErrorSum ;
      }
  }
  return currentTemp ; 

}


bool MomentumPowerTempSchedule::hasMoreTemps() 
{
    return (currentTemp > lowTemp)  ; 
}

void MomentumPowerTempSchedule::toXML(ostream *s) {

  addSpacer(s,1) ; 
  *s << "<tempschedule type=\"momentumpowertempschedule\">" << endl ;
  addSpacer(s) ; 
  *s << "<numpoints value=\"" << numPoints << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<hightemp value=\"" << highTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<lowtemp value=\"" << lowTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<power value=\"" << power << "\" />" << endl ;
  addSpacer(s,-1) ; 
  *s << "<constant value=\"" << constant << "\" />" << endl ;
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
// $Id: MomentumPowerTempSchedule.cpp,v 1.1.4.6 2004/02/13 19:52:25 joel Exp $

