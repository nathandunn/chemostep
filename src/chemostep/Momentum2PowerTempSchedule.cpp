
#include "Momentum2PowerTempSchedule.hpp"


Momentum2PowerTempSchedule::Momentum2PowerTempSchedule(int numPoints, double newPower, double newConstant, double start, double stop):MomentumPowerTempSchedule(numPoints,newPower,newConstant,start,stop)
{
} 

double Momentum2PowerTempSchedule::getNextTemp(double deltaError,vector<double>* variables) {
  if(!hasInitTemps){
    cout << "temps not initiallized, initializing temps" << endl ;
    initTemps() ;
    deltaTemp = 0 ; 
    prevTemp = (*tempSchedule)[0] ; 
  }

//  deltaErrorSum = ( deltaErrorSum +  deltaError ) / constant ; 
  double errorConst = 5.0 ; 
  deltaErrorSum = ( deltaErrorSum / constant ) + ( deltaError / errorConst ) * deltaTemp ; 
  if(deltaErrorSum <0) {
      deltaErrorSum = 0 ; 
  }

  if(counter < numPoints  ){
      currentTemp = (*tempSchedule)[counter] + ( deltaErrorSum  ) ; 
  }
  else{
      // Don't reduce the temperature the first time through.
      if (counter != 0) {
          currentTemp = (currentTemp / constant) + deltaErrorSum ;
      }
  }

  // increment counter
  ++counter ; 
  // calculate temp change
  deltaTemp = currentTemp - prevTemp ; 
  prevTemp = currentTemp ; 
  
  return currentTemp ; 

}


void Momentum2PowerTempSchedule::toXML(ostream *s) const  {

  *s << "\t<tempschedule type=\"momentum2powertempschedule\">" << endl ;
  *s << "\t\t<numpoints value=\"" << numPoints << "\" />" << endl ;
  *s << "\t\t<hightemp value=\"" << highTemp << "\" />" << endl ;
  *s << "\t\t<lowtemp value=\"" << lowTemp << "\" />" << endl ;
  *s << "\t\t<power value=\"" << power << "\" />" << endl ;
  *s << "\t\t<constant value=\"" << constant << "\" />" << endl ;
  *s << "\t</tempschedule>" << endl ;
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

