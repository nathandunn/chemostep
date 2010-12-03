#ifndef SIGLOOKUPBZ_HPP_
#  define SIGLOOKUPBZ_HPP_

#include "SigLookup.hpp"

/**  Sigmoid lookup function, which is hopefuly more efficient, storing data using blitz.
 *
 */
class SigLookupBz : public SigLookup {

public:
    bool sigLookupInit() const ; 
    double sigLookup(double input) const ; 

protected:
    static Vector f_dV ; 
    static Vector f_fV; 

} ;

#endif /* ifndef SIGLOOKUPBZ_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>

