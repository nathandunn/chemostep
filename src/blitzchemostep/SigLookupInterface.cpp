
#include <iostream>
using std::cout ; 
using std::endl ; 
#include <float.h>


#include "blitzdefs.hpp"

#include "SigLookupInterface.hpp"

SigLookupInterface::SigLookupInterface() 
{
    sigLookupInit() ; 
}


bool SigLookupInterface::sigLookupInit() const 
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

/// return (1.0 / (1.0 + exp (-x))); // original sigmoid
double SigLookupInterface::sigLookup(double x) const 
{
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
    }

}

/// We assume that limit is positive.  May assume later that limit is implicit. 
Vector* SigLookupInterface::sigLookup(Vector *v,double limit) const 
{
    int vSize = v->size() ; 
    for(int i = 0 ; i < vSize ; i++){
        if((*v)(i)> limit){
            (*v)(i) = 1 ; 
        }
        else
        if((*v)(i)< -limit){
            (*v)(i) = 0 ; 
        }
        else{
            (*v)(i) = sigLookup( (*v)(i) ) ; 
        }
    }

    return v ; 

}

Vector SigLookupInterface::f_dV(defaultTableLength)  ; 
Vector SigLookupInterface::f_fV(defaultTableLength)  ; 

double SigLookupInterface::f_factor = 0 ; 
const int SigLookupInterface::defaultTableLength = 1000 ; 
const int SigLookupInterface::defaultTableMax = 8 ; 
int SigLookupInterface::F_TABLE_LENGTH = defaultTableLength ; 
int SigLookupInterface::F_TABLE_MAX= defaultTableMax ; 

/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */



