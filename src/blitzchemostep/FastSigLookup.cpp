#include <iostream>
using std::cout ; 
using std::endl ; 

#include "FastSigLookup.hpp"



FastSigLookup::FastSigLookup() 
{
    sigLookupInit() ; 
}



FastSigLookup::FastSigLookup(int newTableLength,double newAbsoluteLimit) 
{
    F_TABLE_LENGTH = newTableLength ; 
    F_LIMIT = fabs( newAbsoluteLimit ) ; 
    sigLookupInit() ; 
}



bool FastSigLookup::sigLookupInit() const 
{
    if(mDiffVector.size()!=F_TABLE_LENGTH){
        mDiffVector.resize(F_TABLE_LENGTH) ; 
    }
    if(mValueVector.size()!=F_TABLE_LENGTH){
        mValueVector.resize(F_TABLE_LENGTH) ; 
    }
//    mFFactor = (double) (F_TABLE_LENGTH - 1) / ( F_LIMIT * 2.0) ;
    mFFactor =  ( F_LIMIT * 2.0) / (double) (F_TABLE_LENGTH ) ;
    mInvsFFactor = 1.0 / mFFactor ; 
    mHalfTableLength =  ((double) F_TABLE_LENGTH / 2.0) ; 
    double input = -F_LIMIT ;
    for (int i = 0; i < F_TABLE_LENGTH; i++, input += mFFactor ) {//for
        (mValueVector)(i) = 1.0 / (1.0 + exp (-((double) input ) ));
//        cout << i << ": " << (input) << "[" << input << "]->" << (mValueVector)(i) << endl ;  
        if(i>0){
            (mDiffVector)(i-1) = (mValueVector)(i) - (mValueVector)(i-1);
        }
    }//for
    return true ; 
}



double FastSigLookup::sigLookup(double input) const 
{
//    if(input <= -F_LIMIT){
//        return 0.0 ; 
//    }
//    else
//    if(input >= F_LIMIT){
//        return 1.0 ; 
//    }
//    else{
        double lookupValue = (input * mInvsFFactor )  + mHalfTableLength  ; 
        int intLookupValue = (int) lookupValue ; 
        return (mValueVector)(intLookupValue) + ( (mDiffVector)(intLookupValue) * (lookupValue - intLookupValue) )  ; 
//    }
}



Vector* FastSigLookup::sigLookup(Vector *input) const 
{
    int size = input->size() ; 
    double lookupValue ;
    int intLookupValue ; 
    for(int i = 0 ; i < size ; i++){
            lookupValue = ( (*input)(i) * mInvsFFactor )  + mHalfTableLength  ; 
            intLookupValue = (int) lookupValue  ; 
            (*input)(i) = (mValueVector)(intLookupValue) + ( (mDiffVector)(intLookupValue) * (lookupValue - intLookupValue) )  ; 
    }
    return input ; 

}


double FastSigLookup::mFFactor = 0 ; 
const int FastSigLookup::defaultTableLength = 1000 ; 
const double FastSigLookup::defaultLimit = 8 ; 
int FastSigLookup::F_TABLE_LENGTH = defaultTableLength ; 
double FastSigLookup::F_LIMIT = defaultLimit ; 
Vector FastSigLookup::mDiffVector(defaultTableLength) ; 
Vector FastSigLookup::mValueVector(defaultTableLength) ; 
double FastSigLookup::mInvsFFactor = 1.0 / mFFactor ; 
double FastSigLookup::mHalfTableLength = ((double) F_TABLE_LENGTH) / 2.0 ; 


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


