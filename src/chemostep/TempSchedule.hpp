#ifndef TEMPSCHEDULE_HPP_
#  define TEMPSCHEDULE_HPP_


#include <iostream>
using std::ostream ; 

#include <vector>
using std::vector ; 

#include <math.h>

#include "XmlRenderable.hpp"

/** 
 * Creates and initializes a temperature schedule for NetAnnealer. 
 */


class TempSchedule : public XmlRenderable {

public:
    TempSchedule():hasInitTemps(false) {}; 
    TempSchedule(int numPoints,double newHighTemp,double newLowTemp) ; 
    virtual double getNextTemp(double deltaError,double doubleVar) ; 
    virtual double getNextTemp(double deltaError=0.0,vector<double>* variables=NULL)=0 ; 
    virtual int numTemps() {return numPoints ; } 
    virtual bool hasMoreTemps() ; 
    virtual int getNumPoints() ; 
    virtual void setNumPoints(int newPoints) ; 
    virtual double getHighTemp() ; 
    virtual void setHighTemp(double newHighTemp) ; 
    virtual double getLowTemp() ; 
    virtual void setLowTemp(double newLowTemp) ; 
    virtual void initTemps()=0 ; 
    virtual void toXML(ostream *s) ;


protected:
    int numPoints ; 
    double highTemp ; 
    double lowTemp ; 
    int counter ; 
    vector<double> *tempSchedule ; 
    bool hasInitTemps ; 
    double currentTemp  ; 
    vector<double>* lazyVector ; 
} ;

#endif /* ifndef TEMPSCHEDULE_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

