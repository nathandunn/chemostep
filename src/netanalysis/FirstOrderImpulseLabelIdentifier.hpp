#ifndef FIRSTORDERIMPULSELABELIDENTIFIER_HPP_
#  define FIRSTORDERIMPULSELABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 


#include "FirstOrderLabelIdentifier.hpp"

#include <vector>
using std::vector ; 

#include "LabelSet.hpp"

class Label ; 
class DataFilter ; 

class FirstOrderImpulseLabelIdentifier : public FirstOrderLabelIdentifier {

public:
    FirstOrderImpulseLabelIdentifier() { } 
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter) ; 
    virtual double calculateError(Label* newLabel,DataFilter* newDataFilter) ; 
    virtual int calculateErrorPoints(Label* newLabel,DataFilter* newDataFilter) ; 


protected:
    double mTau ; 
    double mAmpl ; 

} ;

#endif /* ifndef FIRSTORDERIMPULSELABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


