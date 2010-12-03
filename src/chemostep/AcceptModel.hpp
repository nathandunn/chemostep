
#ifndef ACCEPTMODEL_HPP_
#  define ACCEPTMODEL_HPP_

#include <iostream>
using std::ostream ; 

#include <math.h>

#include "XmlRenderable.hpp"

/**  Model of acceptance, if needed used by optimization algorithms.
 *
 */
class AcceptModel : public XmlRenderable {

public:
    AcceptModel() ; 
//    bool accept( double compare1 , double compare2 ) ;
    virtual bool accept(double* variables) ;
    virtual int getNumVariables() ; 
    virtual void toXML(ostream *s) ; 

} ;

#endif /* ifndef ACCEPTMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

