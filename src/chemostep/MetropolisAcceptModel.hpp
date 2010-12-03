
#ifndef METROPOLISACCEPTMODEL_HPP_
#  define METROPOLISACCEPTMODEL_HPP_

#include <iostream>
using std::ostream ; 

#include "AcceptModel.hpp"

/**  Model of acceptance, if needed used by optimization algorithms.  To be used with a more gradual, geometric schedule.
 *
 */
class MetropolisAcceptModel : public AcceptModel {

public:
    MetropolisAcceptModel(double newConst=1.0) ; 
//    bool accept( double compare1 , double compare2 ) ;
    virtual bool accept(double* variables) ;
    virtual int getNumVariables() ; 
    virtual void setConstant(double newConst) ; 
    virtual void toXML(ostream *s) ; 

protected:
    virtual bool calcAccept(double uniformProb) ; 
    double mConst ; 
    #ifdef DOMPI
    double randomValue ; 
    #endif

} ;

#endif /* ifndef ACCEPTMODEL_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

