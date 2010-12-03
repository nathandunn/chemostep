#ifndef WINDOWFUNCTION_HPP_
#  define WINDOWFUNCTION_HPP_

#include <iostream>
using std::ostream ; 
using std::endl ; 

#include <XmlRenderable.hpp>

class WindowFunction : public XmlRenderable{

public:
    WindowFunction( ){ }  ; 
    WindowFunction(double newMaxInputWindow ,double maxOutput=1.0 ) ; 
    virtual double getValue( double inputValue) ; 
    virtual void toXML(ostream* s) ; 

protected:
    double mHighOutput; 
    double mLowOutput ; 
    double mLowInput ;
    double mHighInput ; 

} ;

#endif /* ifndef WINDOWFUNCTION_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

