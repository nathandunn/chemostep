#ifndef FASTSIGLOOKUP_HPP_
#  define FASTSIGLOOKUP_HPP_

#include "blitzdefs.hpp"

class FastSigLookup {

public:
    FastSigLookup() ; 
    FastSigLookup(int newTableLength,double newAbsoluteLimit) ; 
    bool sigLookupInit() const ; 
    double sigLookup(double input) const ; 
    Vector* sigLookup(Vector *input) const ; 

protected:
    static Vector mDiffVector ; 
    static Vector mValueVector ; 
    static double mFFactor , mInvsFFactor , mHalfTableLength; 
    static int F_TABLE_LENGTH ; 
    static double F_LIMIT ; 
    const static int defaultTableLength ; 
    const static double defaultLimit ; 
	


} ;

#endif /* ifndef FASTSIGLOOKUP_H */
// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


