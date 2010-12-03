#ifndef FIRSTORDERLABELIDENTIFIER_HPP_
#  define FIRSTORDERLABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 

#include "LabelIdentifier.hpp"

class Label ; 
class DataFilter ; 
class LabelSet ; 

class FirstOrderLabelIdentifier : public LabelIdentifier {

public:
    FirstOrderLabelIdentifier() : LabelIdentifier() { }; 
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter) ; 


} ;

#endif /* ifndef FIRSTORDERLABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


