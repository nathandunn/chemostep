#include <iostream>
using std::cout ; 
using std::endl ; 

#include "RNG.hpp"

clock_t currentClock  ; 
clock_t nextClock ; 

int supertest(int iters){
    cout << "rand()/RAND_MAX---------" << endl ; 
    currentClock = clock() ; 
    for(int i = 0 ; i < iters ; i++){
//        cout << rand() / (float) RAND_MAX << endl ;
        rand() / (float) RAND_MAX  ; 
    }
    nextClock = clock() ; 
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 



    cout << "drand48()---------" << endl ; 
    currentClock = clock() ; 
    for(int i = 0 ; i < iters ; i++){
//        cout << drand48()  << endl ;
        drand48()  ; 
    }
    nextClock = clock() ; 
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 


    float randDivisor = 1.0 / (float) RAND_MAX ; 
    cout << "rand() * invsRAND_MAX ---------" << endl ; 
    currentClock = clock() ; 
    for(int i = 0 ; i < iters ; i++){
//        cout << erand48()  << endl ;
//        cout << rand() * randDivisor  << endl ;
        rand() * randDivisor  ;
    }
    nextClock = clock() ; 
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
  
  
    cout << "RNG::uniform()---------" << endl ; 
    currentClock = clock() ; 
    for(int i = 0 ; i < iters ; i++){
//        cout << RNG::uniform()  << endl ;
        RNG::uniform()  ; 
    }
    nextClock = clock() ; 
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 
    cout << "RNG::normal()---------" << endl ; 
    currentClock = clock() ; 
    for(int i = 0 ; i < iters ; i++){
//        cout << RNG::normal()  << endl ;
          RNG::normal() ; 
    }
    nextClock = clock() ; 
    cout <<  "time: " << (nextClock-currentClock)/ (double) CLOCKS_PER_SEC << endl ; 


}



/* Function int main(int argc, char **argv) {{{ */
int main(int argc, char **argv)
{

    if(argc>1){
        supertest( atoi(argv[1]) ) ; 
    }
    else{
        supertest( 100 ) ; 
    }

    return 0;
} /* }}} */



// -*- C++ -*-

// (C) 2005 by Nathan Dunn, <ndunn@mac.com>


