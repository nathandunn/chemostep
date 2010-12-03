/*
 * $Id: MomentumTempSchedule.cpp,v 1.1.4.6 2004/02/13 19:52:25 joel Exp $
 */

#include "MomentumTempSchedule.hpp"

MomentumTempSchedule::MomentumTempSchedule(double newConstant, double start, double stop):TempSchedule(0,start,stop){

    hasInitTemps = false ; 
    constant = newConstant ;
    initTemps() ; 
}; 

double MomentumTempSchedule::getNextTemp(double deltaError,vector<double>* variables) {

  if(counter > 0){
      counter++ ; 
      currentTemp = (deltaError + 1) * (currentTemp / constant);
      
      return currentTemp ;
      
  } else{
      counter++ ; 
      return currentTemp ; 
  }
}

void MomentumTempSchedule::initTemps() 
{
    counter = 0 ; 
    currentTemp = highTemp ; 
    hasInitTemps = true ;  
}

bool MomentumTempSchedule::hasMoreTemps() 
{
    return (currentTemp > lowTemp)  ; 
}

void MomentumTempSchedule::toXML(ostream *s) {
  addSpacer(s,1) ; 
  *s << "<tempschedule type=\"momentumtempschedule\">" << endl ;
  addSpacer(s) ; 
  *s << "<hightemp value=\"" << highTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<lowtemp value=\"" << lowTemp << "\" />" << endl ;
  addSpacer(s) ; 
  *s << "<numpoints value=\"" << numPoints << "\" />" << endl ;
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
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/MomentumTempSchedule.cpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 09:50:26 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: MomentumTempSchedule.cpp,v 1.1.4.6 2004/02/13 19:52:25 joel Exp $

