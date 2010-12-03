#ifndef POWERTEMPSCHEDULE_HPP_
#  define POWERTEMPSCHEDULE_HPP_

#include "TempSchedule.hpp" 



class PowerTempSchedule : public TempSchedule{

public:
    PowerTempSchedule(int numPoints, double power,double start, double stop); 
    PowerTempSchedule():power(2.0) {} ; 
    virtual void initTemps() ; 
    virtual double getNextTemp(double deltaError=0.0,vector<double>* variables=NULL) ; 
    virtual void setPower(double newPower){ power = newPower ; }  ; 
    virtual double getPower(){ return power ; }  ; 
    virtual void toXML(ostream *s) ;

protected:
    double power ; 

} ;

#endif /* ifndef POWERTEMPSCHEDULE_H */
// -*- C++ -*-

