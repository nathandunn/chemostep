/*
 * $Id: MomentumPowerTempSchedule.hpp,v 1.1.4.3 2004/02/06 02:44:39 joel Exp $
 */
#ifndef MOMENTUMPOWERTEMPSCHEDULE_HPP_
#  define MOMENTUMPOWERTEMPSCHEDULE_HPP_

#include "PowerTempSchedule.hpp" 

#include <iostream>
using std::ostream ;
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include <fstream>
using std::ofstream;


/// This method uses the power schedule, but has a error summary term which decreases over time.  The greater the constant, the quicker it decreases.  When it runs out of space, it decreases geometrically using the constant.  
class MomentumPowerTempSchedule : public PowerTempSchedule{

public:
  MomentumPowerTempSchedule(int numPoints, double power, double constant, double start, double stop); 
  MomentumPowerTempSchedule():power(2.0) {} ; 
  virtual double getNextTemp(double deltaError=0.0,vector<double>* variables=NULL) ; 
  virtual bool hasMoreTemps() ; 
  virtual void setConstant(double newConstant) { constant = newConstant ; } ;
  virtual void toXML(ostream *s) ;

protected:
  double power ; 
  double constant ;
  double deltaErrorSum ; 
} ;

#endif /* ifndef MOMENTUMPOWERTEMPSCHEDULE_H */

// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/MomentumPowerTempSchedule.hpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 09:44:34 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: MomentumPowerTempSchedule.hpp,v 1.1.4.3 2004/02/06 02:44:39 joel Exp $

