#include <iostream>
using std::cout ; 
using std::endl ; 

#include <float.h>
#include <time.h>

#include "FastSigLookup.hpp"
#include "SigLookupInterface.hpp"
#include "SigLookup.hpp"
#include "SigLookupBz.hpp"

int testSize  ; 
double* realOutputArray  ; 
double* inputArray ; 
double* test2OutputArray ; 
SigLookupInterface *sigLookupInterface  ; 
SigLookup* sigLookup ; 
SigLookupBz* sigLookupBz ; 
Vector* inputVector  ; 
Vector* test3OutputVector ; 
FastSigLookup* fastSigLookup ; 
int numIterations ; 
double mTableLimit ; 

clock_t currentClock  ; 
clock_t nextClock ; 


int initArray(double startValue,double increment,int newNumIterations,int tableSize,double tableLimit){
    cout << "startValue[" << startValue << "] increment[" << increment << "] " << endl ; 
    numIterations = newNumIterations ; 
    mTableLimit = tableLimit ; 
    sigLookupInterface = new SigLookupInterface() ; 
    sigLookupBz = new SigLookupBz() ; 
    fastSigLookup = new FastSigLookup(tableSize,tableLimit) ; 
    testSize = abs( (int)   (startValue * 2.0 / increment) ) ; 
    cout << "testSize[" << testSize << "] " << endl ; 
    inputArray = new double[testSize] ; 
    inputVector = new Vector(testSize) ;
    realOutputArray = new double[testSize] ; 
    test2OutputArray = new double[testSize] ; 
    test3OutputVector = new Vector(testSize) ; 
    double currentValue = -fabs(startValue) ; 

    for(int i = 0 ; i < testSize ; i++){
        inputArray[i] = currentValue ; 
        (*inputVector)(i) = currentValue ; 
        currentValue += increment ; 
    }
    cout << "finish initArray" << endl ; 


    return 0 ; 
}

// tests sigmoid using exp
int test1(){
    cout << "START ***** test1 *****" << endl ;
    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        for(int i = 0 ; i < testSize ; i++){
            realOutputArray[i] = 1.0 / (1.0 + exp(-inputArray[i]) ) ; 
    //        cout << i << ":" << inputArray[i] << "->" << realOutputArray[i] << endl ; 
        }
    }
    nextClock = clock() ; 
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << 0 << endl ; 

    cout << "FINISH ***** test1 *****" << endl ;
}


// tests scalar sigLookup
int test2(){
    cout << "START ***** test2 *****" << endl ;
    double error = 0.0 ; 
    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        for(int i = 0 ; i < testSize ; i++){
            test2OutputArray[i] = sigLookupInterface->sigLookup( inputArray[i])  ; 
//            cout << i << ":" << inputArray[i] << "->" << realOutputArray[i] << " vs " << test2OutputArray[i] << endl ; 
        }
    }
    nextClock = clock() ; 

    for(int i = 0 ; i < testSize ; i++){
        error += pow ( test2OutputArray[i] - realOutputArray[i] ,2.0) ; 
        
    }
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << error/ (double) testSize  << endl ; 

    cout << "FINISH ***** test2 *****" << endl ;
}


int test3(){
    cout << "START ***** test3 *****" << endl ;
    double error = 0.0 ; 

    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        *test3OutputVector = *inputVector ; 
        sigLookupInterface->sigLookup( test3OutputVector ,mTableLimit)  ; 
    }
    nextClock = clock() ; 

    for(int i = 0 ; i < testSize ; i++){
        error += pow ( (*test3OutputVector)(i) - realOutputArray[i] ,2.0) ; 
        
    }
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << error/ (double) testSize  << endl ; 
    
//    for(int i = 0 ; i < testSize ; i++){
//            cout << i << ":" << (*inputVector)(i) << "->" << realOutputArray[i] << " vs " << (*test3OutputVector)(i) << endl ; 
//    }

    cout << "FINISH ***** test3 *****" << endl ;
}


int test4(){
    cout << "START ***** test4 *****" << endl ;
    double error = 0.0 ; 

    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        for(int i = 0 ; i < testSize ; i++){
            test2OutputArray[i] = SigLookup::sigLookup( inputArray[i])  ; 
    //        cout << i << ":" << inputArray[i] << "->" << realOutputArray[i] << " vs " << test2OutputArray[i] << endl ; 
        }
    }
    nextClock = clock() ; 

    for(int i = 0 ; i < testSize ; i++){
        error += pow ( test2OutputArray[i] - realOutputArray[i] ,2.0) ; 
        
    }
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << error/ (double) testSize  << endl ; 

    cout << "FINISH ***** test4 *****" << endl ;
}


int test5(){
    cout << "START ***** test5 *****" << endl ;
    double error = 0.0 ; 

    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        for(int i = 0 ; i < testSize ; i++){
            test2OutputArray[i] = sigLookupBz->sigLookup( inputArray[i])  ; 
    //        cout << i << ":" << inputArray[i] << "->" << realOutputArray[i] << " vs " << test2OutputArray[i] << endl ; 
        }
    }
    nextClock = clock() ; 

    for(int i = 0 ; i < testSize ; i++){
        error += pow ( test2OutputArray[i] - realOutputArray[i] ,2.0) ; 
        
    }
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << error/ (double) testSize  << endl ; 

    cout << "FINISH ***** test5 *****" << endl ;
}



int test6(){
    cout << "START ***** test6 *****" << endl ;
    double error = 0.0 ; 

    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        for(int i = 0 ; i < testSize ; i++){
            test2OutputArray[i] = fastSigLookup->sigLookup( inputArray[i])  ; 
//            cout << i << " : " << inputArray[i] << "->" << realOutputArray[i] << " vs " << test2OutputArray[i] << endl ; 
        }
    }
    nextClock = clock() ; 

    for(int i = 0 ; i < testSize ; i++){
        error += pow ( test2OutputArray[i] - realOutputArray[i] ,2.0) ; 
        
    }
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << error/ (double) testSize  << endl ; 

    cout << "FINISH ***** test6 *****" << endl ;
}


int test7(){
    cout << "START ***** test7 *****" << endl ;
    double error = 0.0 ; 

    currentClock = clock() ; 
    for(int j = 0 ; j < numIterations ; j++){
        *test3OutputVector = *inputVector ; 
        fastSigLookup->sigLookup( test3OutputVector )  ; 
    }
    nextClock = clock() ; 

    for(int i = 0 ; i < testSize ; i++){
        error += pow ( (*test3OutputVector)(i) - realOutputArray[i] ,2.0) ; 
        
    }
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout <<  "error: " << error/ (double) testSize  << endl ; 

    cout << "FINISH ***** test7 *****" << endl ;
}





/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{
    cout << "numArgs: " << argc << endl ; 
    if(argc==6){
        initArray(atof(argv[1]),atof( argv[2] ),atoi(argv[3]),atoi(argv[4]),atof(argv[5]) ) ; 
    }
    else{
        cout << "no args -10, by 1 times 10 iterations" << endl ; 
        initArray(-10.0,1,10 ,1000,6.0) ; 
    }

    test1( ) ; // test the baseline with exp
    test2( ) ; // test SigLookupInterface, scalar
    test3( ) ; // test SigLookupInterface, vector 
//    test4( ) ; // test SigLookup, scalar
    test5( ) ; // test SigLookupBz, scalar  // can't run these two together, but this is marginally better
    test6( ) ; // test FastSigLookup, scalar
    test7( ) ; // test FastSigLookup, vector 


    return 0;
} /* }}} */



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


