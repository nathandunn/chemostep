#ifndef FIRSTORDERLABEL_HPP_
#  define FIRSTORDERLABEL_HPP_

#include "Label.hpp"
#include "blitzdefs.hpp"

#include <vector>
using std::vector ; 


class FirstOrderImpulseFilter ; 

/**  This represents a first-order transfer function.  H(s) = M*(1/(tau s + 1) ).  This 
 *
 */
class FirstOrderLabel : public Label{

public:
    FirstOrderLabel(int newLabelCount) ;
    FirstOrderLabel(int newLabelCount,double newTau,double newAmpl,DataFilter* newDataFilter) ;
    virtual string print() ; 
    virtual void setTau(double newTau) ; 
    virtual void setAmplitude(double newAmpl) ; 
    virtual double getAmplitude() ; 
    virtual double getTau() ; 

    
protected:
  double mTau , mAmpl ; 

    
} ;

#endif /* ifndef FIRSTORDERLABEL_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


