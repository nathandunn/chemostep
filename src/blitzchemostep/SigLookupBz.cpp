/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <float.h>

#include <blitzdefs.hpp>

#include "SigLookupBz.hpp"

bool SigLookupBz::sigLookupInit() const
{
    f_factor = (double) (F_TABLE_LENGTH - 1) / (double) F_TABLE_MAX;
    f_dV = (new Vector(F_TABLE_LENGTH))->copy() ; 
    f_fV = (new Vector(F_TABLE_LENGTH))->copy() ; 
//    cout << "f_factor: " << f_factor << endl ; 
    for (int i = 0; i < F_TABLE_LENGTH; i++) {//for
        (f_fV)(i) = 1.0 / (1.0 + exp (-((double) i) / f_factor));
        if(i>0){
            (f_dV)(i-1) = (f_fV)(i) - (f_fV)(i-1);
        }
    }//for
    return true ; 
}


double SigLookupBz::sigLookup(double x) const
{
    if(f_factor==0){
        sigLookupInit() ; 
    }
     //return (1.0 / (1.0 + exp (-x))); The obvious approach
    int i;
    double xd;

    if (x >= 0.0) {//if

        if (x > (DBL_MAX / f_factor)){
            x = DBL_MAX / f_factor;
        }

        xd = x * f_factor;

        if (xd > INT_MAX){
            xd = (double)INT_MAX;
        }
        i = (int) xd;
        if (i >= (F_TABLE_LENGTH - 1)){
            return (f_fV)(F_TABLE_LENGTH - 1);
        }
        else{
            return (f_fV)(i) + (f_dV)(i) * (xd - i); 
        }
    }//if
    else {//else  x < 0
        // as x approaches 0?
        if (-x < (DBL_MIN / f_factor)){
            x = DBL_MIN / f_factor;
        }
        xd = - x * f_factor;

        if (xd < INT_MIN){
            xd = (double)INT_MIN;
        }

        i = (int) xd;
        if (i >= (F_TABLE_LENGTH - 1)){
            return 1.0 - (f_fV)(F_TABLE_LENGTH - 1);
        }
        else{
            // take the base number, and make the difference
            return 1.0 - ((f_fV)(i) + (f_dV)(i) * (xd - i));
        }
    }//else
}



Vector SigLookupBz::f_dV(defaultTableLength)  ; 
Vector SigLookupBz::f_fV(defaultTableLength)  ; 

/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

