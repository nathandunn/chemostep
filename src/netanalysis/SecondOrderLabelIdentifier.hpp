#ifndef SECONDORDERLABELIDENTIFIER_HPP_
#  define SECONDORDERLABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 

#include "LabelIdentifier.hpp"

class Label ; 
class LabelSet ; 
class DataFilter ; 

class SecondOrderLabelIdentifier : public LabelIdentifier {

public:
    SecondOrderLabelIdentifier() : LabelIdentifier() { }; 
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter) ; 


} ;

#endif /* ifndef SECONDORDERLABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


