/*
 * $Id: MomentumTempSchedule.hpp,v 1.1.4.3 2004/02/06 02:44:39 joel Exp $
 */
#ifndef MOMENTUMTEMPSCHEDULE_HPP_
#  define MOMENTUMTEMPSCHEDULE_HPP_

#include "TempSchedule.hpp" 

#include <iostream>
using std::ostream ;
using std::cout ; 
using std::endl ; 

#include <fstream>
using std::ofstream;


class MomentumTempSchedule : public TempSchedule{

public:
  MomentumTempSchedule(double constant, double start, double stop); 
  MomentumTempSchedule() {} ; 
  virtual void initTemps() ; 
  virtual double getNextTemp(double deltaError=0.0,vector<double>* variables=NULL) ; 
  virtual bool hasMoreTemps() ; 
  virtual void setConstant(double newConstant) { constant = newConstant ; } ;
  virtual void toXML(ostream *s) ;

protected:
  double constant ;
} ;

#endif /* ifndef MOMENTUMTEMPSCHEDULE_H */

// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/chemostep/MomentumTempSchedule.hpp"
// LAST MODIFICATION: "Wed, 12 Jan 2005 09:50:33 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: MomentumTempSchedule.hpp,v 1.1.4.3 2004/02/06 02:44:39 joel Exp $

