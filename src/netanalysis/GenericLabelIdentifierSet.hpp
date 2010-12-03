#ifndef GENERICLABELIDENTIFIERSET_HPP_
#  define GENERICLABELIDENTIFIERSET_HPP_

#include <vector>
using std::vector ; 

#include "LabelFactory.hpp"

class GenericLabelIdentifierSet   {

public:
    GenericLabelIdentifierSet()  ; 
    virtual void addLabelFactory( LabelFactory* newLabelFactory  ) ; 
    virtual LabelSet* extractLabelSet( RawSignal* newRawSignal ) ; 

protected:
    virtual LabelSet* findBestLabelSet( vector<LabelSet*>*  newLabelSetVector ) ; 
    vector<LabelFactory*>* mLabelModelVector ; 

} ;

#endif /* ifndef SETLABELIDENTIFIER_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


