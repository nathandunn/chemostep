#ifndef SECONDORDERIMPULSELABELIDENTIFIER_HPP_
#  define SECONDORDERIMPULSELABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 


#include "SecondOrderLabelIdentifier.hpp"

#include <vector>
using std::vector ; 

#include "LabelSet.hpp"

class Label ; 
class DataFilter ; 

class SecondOrderImpulseLabelIdentifier : public SecondOrderLabelIdentifier {

public:
    SecondOrderImpulseLabelIdentifier() { } 
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter) ; 
    virtual double calculateError(Label* newLabel,DataFilter* newDataFilter) ; 
    virtual int calculateErrorPoints(Label* newLabel,DataFilter* newDataFilter) ; 


protected:
    double mTau ; 
    double mAmpl ; 

} ;

#endif /* ifndef SECONDORDERIMPULSELABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


