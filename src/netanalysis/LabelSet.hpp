
#ifndef LABELSET_HPP_
#  define LABELSET_HPP_

#include <vector>
using std::vector ; 

#include "Label.hpp"


class LabelSet : public vector<Label*> {

public:
    LabelSet() ; 
    LabelSet(int size) ; 
    LabelSet(const LabelSet & newLabelSet) ; 
    vector<vector<double>*>* getErrorTraceAsSeries()  ; 
    vector<vector<double>*>* getModelTraceAsSeries()  ; 

protected:
    int mMaxTime ; 

} ;

#endif /* ifndef LABELSET_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


