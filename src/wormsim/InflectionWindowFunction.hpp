#ifndef INFLECTIONWINDOWFUNCTION_HPP_
#  define INFLECTIONWINDOWFUNCTION_HPP_

#include "PowerWindowFunction.hpp" 

/// This class gives positive scores prior to the inflection point, which is the mHighInput, and negative scores after the inflection points. The point behind this class is that negative solutions need to be penalized, in addition to positive solutions being rewarded.  Currently negative solutions are ignored.    
class InflectionWindowFunction : public PowerWindowFunction {

public:
    InflectionWindowFunction( double newLowInput,double newHighInput, double newPower=1.0,double newLowOutput=1.0,double  newHighOutput=1.0,double newRatio=1.0) ; 

    // over-ride these functions
    virtual double getValue( double inputValue) ; 
    virtual void toXML(ostream* s) ; 

protected:
    double mRatio ;  /// This is the ratio of pre-inflection maximum to post-inflection maximum
} ;

#endif /* ifndef INFLECTIONWINDOWFUNCTION_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

