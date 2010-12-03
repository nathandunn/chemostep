
#ifndef GEOMETRICTEMPSCHEDULE_HPP_
#  define GEOMETRICTEMPSCHEDULE_HPP_ 


#include <iostream>
using std::ostream ; 

#include <vector>
using std::vector ; 

/** 
 * Creates and initializes a temperature schedule for NetAnnealer. 
 */

#include "TempSchedule.hpp"

class GeometricTempSchedule : public TempSchedule {

public:
    GeometricTempSchedule() ; 
    GeometricTempSchedule(int numPoints,double newHighTemp,double newLowTemp) ; 
    virtual double getNextTemp(double deltaError=0.0,vector<double>* variables=NULL) ; 
    virtual void initTemps() ; 
    virtual void toXML(ostream *s) ;


protected:


} ;

#endif /* ifndef GEOMETRICTEMPSCHEDULE_HPP_ */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

