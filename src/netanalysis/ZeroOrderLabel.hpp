#ifndef ZEROORDERLABEL_HPP_
#  define ZEROORDERLABEL_HPP_

#include "Label.hpp"
#include "blitzdefs.hpp"

#include <vector>
using std::vector ; 


class ZeroOrderImpulseFilter ; 

/**  This represents a first-order transfer function.  H(s) = M*(1/(tau s + 1) ).  This 
 *
 */
class ZeroOrderLabel : public Label{

public:
    ZeroOrderLabel(int newLabelCount) ;
    ZeroOrderLabel(int newLabelCount,DataFilter* newDataFilter) ;
    virtual string print() ; 

    
protected:

    
} ;

#endif /* ifndef ZEROORDERLABEL_H */
// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


