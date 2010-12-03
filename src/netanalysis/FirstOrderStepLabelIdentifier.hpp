#ifndef FIRSTORDERSTEPLABELIDENTIFIER_HPP_
#  define FIRSTORDERSTEPLABELIDENTIFIER_HPP_

#include <vector>
using std::vector ; 


class Label ; 
class DataFilter ; 

#include "FirstOrderLabelIdentifier.hpp"

class FirstOrderStepLabelIdentifier : public FirstOrderLabelIdentifier {

public:
    FirstOrderStepLabelIdentifier() { } 
    virtual vector<Label*>* identifyLabel(DataFilter* newDataFilter) ; 


} ;

#endif /* ifndef FIRSTORDERSTEPLABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


