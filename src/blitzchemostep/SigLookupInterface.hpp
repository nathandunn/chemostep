#ifndef SIGLOOKUPINTERFACE_HPP_
#  define SIGLOOKUPINTERFACE_HPP_

#include "blitzdefs.hpp"

/** Description:  Class SigLookupInterface takes blitz vectors and double values and returns a sigmoid using a lookup table and hard limits.  May potentially be inlined, as well, but is meant to be inherited.
 *
 */
class SigLookupInterface {

public:
    SigLookupInterface() ; 
    bool sigLookupInit() const ; 
    double sigLookup(double input) const ; 
    Vector* sigLookup(Vector *input,double limit) const ; // 


protected:
    static Vector f_dV ; 
    static Vector f_fV; 
    static double f_factor ; 
    static int F_TABLE_LENGTH ; 
    static int F_TABLE_MAX ; 
    const static int defaultTableLength ; 
    const static int defaultTableMax ; 

} ;

#endif /* ifndef SIGLOOKUPINTERFACE_H */

