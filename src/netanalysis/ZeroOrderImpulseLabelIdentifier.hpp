#ifndef ZEROORDERIMPULSELABELIDENTIFIER_HPP_
#  define ZEROORDERIMPULSELABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 


#include "ZeroOrderLabelIdentifier.hpp"

#include <vector>
using std::vector ; 

#include "LabelSet.hpp"

class Label ; 
class DataFilter ; 

class ZeroOrderImpulseLabelIdentifier : public ZeroOrderLabelIdentifier {

public:
    ZeroOrderImpulseLabelIdentifier() { } 
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter) ; 
    virtual double calculateError(Label* newLabel,DataFilter* newDataFilter) ; 
    virtual int calculateErrorPoints(Label* newLabel,DataFilter* newDataFilter) ; 


protected:
    double mTau ; 
    double mAmpl ; 

} ;

#endif /* ifndef ZEROORDERIMPULSELABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


