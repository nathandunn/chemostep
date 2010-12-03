#ifndef MOMENTUM2POWERTEMPSCHEDULE_HPP_
#  define MOMENTUM2POWERTEMPSCHEDULE_HPP_

#include "MomentumPowerTempSchedule.hpp" 

#include <iostream>
using std::ostream ;
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include <fstream>
using std::ofstream;


/// This method uses the power schedule, but has a error summary term which decreases over time.  The greater the constant, the quicker it decreases.  When it runs out of space, it decreases geometrically using the constant.  
class Momentum2PowerTempSchedule : public MomentumPowerTempSchedule{

public:
  Momentum2PowerTempSchedule(int numPoints, double power, double constant, double start, double stop); 
  virtual double getNextTemp(double deltaError=0.0,vector<double>* variables=NULL) ; 
  virtual void toXML(ostream *s) const;

protected:
  double prevTemp ; 
  double deltaTemp ; 
} ;

#endif /* ifndef MOMENTUM2POWERTEMPSCHEDULE_H */

// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

