#ifndef SIGLOOKUP_HPP_
#  define SIGLOOKUP_HPP_

/**  Sigmoid lookup function, which is hopefuly more efficient.
 *
 */
class SigLookup {

public:
    const static bool sigLookupInit() ; 
    const static bool sigLookupInit(int length,int max) ; 
    const static double sigLookup(double input) ; 

protected:
    static double f_factor ; 
    static int F_TABLE_LENGTH ; 
    static int F_TABLE_MAX ; 
    const static int defaultTableLength ; 
    const static int defaultTableMax ; 

private:
    static double* f_d ; 
    static double* f_f ; 
//    static bool test() ; 

} ;

#endif /* ifndef SIGLOOKUP_H */
// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>

