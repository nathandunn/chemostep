#ifndef SECONDORDERLABEL_HPP_
#  define SECONDORDERLABEL_HPP_

#include "Label.hpp"
#include "blitzdefs.hpp"

#include <vector>
using std::vector ; 


class SecondOrderImpulseFilter ; 

/**  This represents a first-order transfer function.  H(s) = M*(1/(tau s + 1) ).  This 
 *
 */
class SecondOrderLabel : public Label{

public:
    SecondOrderLabel(int newLabelCount) ;
    SecondOrderLabel(int newLabelCount,double newDecay,double newAmpl,double newPeriod,double newPhaseShift,DataFilter* newDataFilter) ;
    virtual string print() ; 
    virtual void setDecay(double newDecay) ; 
    virtual void setAmplitude(double newAmpl) ; 
    virtual void setPeriod(double newPeriod) ; 
    virtual void setPhaseShift(double newPhaseShift) ; 
    virtual double getDecay() ; 
    virtual double getAmplitude() ; 
    virtual double getPeriod() ; 
    virtual double getPhaseShift() ; 

    
protected:
  double mDecay, mAmpl, mPeriod, mPhaseShift ; 

    
} ;

#endif /* ifndef SECONDORDERLABEL_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


