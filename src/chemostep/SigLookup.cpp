
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <float.h>
#include <math.h>

#include "SigLookup.hpp"

const bool SigLookup::sigLookupInit() {
    f_factor = (double) (F_TABLE_LENGTH - 1) / (double) F_TABLE_MAX;
    f_d = new double[F_TABLE_LENGTH] ; 
    f_f = new double[F_TABLE_LENGTH] ; 
//    cout << "f_factor: " << f_factor << endl ; 
    for (int i = 0; i < F_TABLE_LENGTH; i++) {//for
        f_f[i] = 1.0 / (1.0 + exp (-((double) i) / f_factor));
        if(i>0){
            f_d[i-1] = f_f[i] - f_f[i-1];
        }
    }//for

//    test() ; 
}

//bool SigLookup::test() {
//    for(double i = -F_TABLE_MAX ; i < F_TABLE_MAX ; i+= 0.5){
//        cout << i  << " maps to: " << sigLookup(i) << endl ; 
//    }
//}

const double SigLookup::sigLookup(double x) 
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
            return f_f[F_TABLE_LENGTH - 1];
        }
        else{
            return f_f[i] + f_d[i] * (xd - i); 
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
            return 1.0 - f_f[F_TABLE_LENGTH - 1];
        }
        else{
            // take the base number, and make the difference
            return 1.0 - (f_f[i] + f_d[i] * (xd - i));
        }
    }//else
}


const bool SigLookup::sigLookupInit(int length,int max) 
{
    F_TABLE_LENGTH = length ; 
    F_TABLE_MAX = max ; 
    return sigLookupInit() ; 
}


double* SigLookup::f_d = 0 ; 
double* SigLookup::f_f = 0 ; 
double SigLookup::f_factor = 0 ; 
const int SigLookup::defaultTableLength = 1000 ; 
const int SigLookup::defaultTableMax = 8 ; 
int SigLookup::F_TABLE_LENGTH = defaultTableLength ; 
int SigLookup::F_TABLE_MAX= defaultTableMax ; 


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

