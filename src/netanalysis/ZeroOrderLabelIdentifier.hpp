#ifndef ZEROORDERLABELIDENTIFIER_HPP_
#  define ZEROORDERLABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 

#include "LabelIdentifier.hpp"

class Label ; 
class DataFilter ; 
class LabelSet ; 

class ZeroOrderLabelIdentifier : public LabelIdentifier {

public:
    ZeroOrderLabelIdentifier() : LabelIdentifier() { }; 
    virtual LabelSet* identifyLabel(DataFilter* newDataFilter) ; 


} ;

#endif /* ifndef ZEROORDERLABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


