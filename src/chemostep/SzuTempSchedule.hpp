#ifndef SZUTEMPSCHEDULE_HPP_
#  define SZUTEMPSCHEDULE_HPP_


#include <iostream>
using std::ostream ; 

#include <vector>
using std::vector ; 

/** 
 * Creates and initializes a temperature schedule for NetAnnealer. 
 */

#include "GeometricTempSchedule.hpp"

class SzuTempSchedule : public GeometricTempSchedule {

public:
    SzuTempSchedule() ; 
    SzuTempSchedule(int numPoints,double newHighTemp,double newLowTemp) ; 
    virtual void initTemps() ; 
    virtual void toXML(ostream *s) ;


protected:

} ;

#endif /* ifndef SZUTEMPSCHEDULE_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

