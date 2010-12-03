#ifndef LABELFACTORY_HPP_
#  define LABELFACTORY_HPP_

#include "DataFilter.hpp"
#include "LabelIdentifier.hpp"

using std::pair ; 

class LabelSet ; 


class LabelFactory  {

public:
    LabelFactory( DataFilter* newDataFilter,LabelIdentifier* newLabelIdentifier)  ;
    LabelSet* extractLabelSet(RawSignal* newRawSignal) ; 
    DataFilter* getDataFilter() ; 
    LabelIdentifier* getLabelIdentifier() ; 

protected:
    DataFilter* mDataFilter ; 
    LabelIdentifier* mLabelIdentifier ; 

} ;

#endif /* ifndef LABELFACTORY_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


