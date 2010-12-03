
#ifndef SZUACCEPTMODEL_HPP_
#  define SZUACCEPTMODEL_HPP_

#include <iostream>
using std::ostream ; 


#include "MetropolisAcceptModel.hpp"

/**  Model of acceptance, if needed used by optimization algorithms. To be used with a faster temperature schedule.
 *
 */
class SzuAcceptModel : public MetropolisAcceptModel{

public:
    SzuAcceptModel(double newConst=-1) ; 
    virtual bool accept(double* variables) ;
    virtual void toXML(ostream *s) ; 

protected:
    
} ;

#endif /* ifndef ACCEPTMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

