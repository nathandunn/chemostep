#ifndef POWERWINDOWFUNCTION_HPP_
#  define POWERWINDOWFUNCTION_HPP_

#include "WindowFunction.hpp" 

/// This plots a power function from the lowInput (typically 0), which is lowOutput, to highInput (typically the mWindow value), which is highOutput.  A power less than 1 gives a function that decreases slowly from the lowInput.  A power greater than 1 gives a functio nthat decreases quickly from the lowInput.  
class PowerWindowFunction: public WindowFunction {

public:
    PowerWindowFunction( double newLowInput,double newHighInput, double newPower=1.0,double newLowOutput=1.0,double  newHighOutput=1.0) ; 
    virtual void setLowValue(double newLowValue) ; 
    virtual void setHighValue(double newHighValue) ; 
    virtual void setLowInput(double newLowInput) ; 
    virtual void setHighInput(double newHighInput) ; 
    virtual double getHighInput() ; 

    // over-ride these functions
    virtual double getValue( double inputValue) ; 
    virtual void toXML(ostream* s) ; 

protected:
    double mPower ; 

} ;

#endif /* ifndef POWERWINDOWFUNCTION_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

