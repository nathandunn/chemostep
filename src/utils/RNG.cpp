/*
 * $Id: RNG.cpp,v 1.1.1.1 2003/10/24 19:59:28 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 


#include <string>
using std::string;

#include <float.h>


#include "RNG.hpp"


int RNG::initSeed() 
{
  first = true;			// flag for normal() method

  struct timeval t;
  gettimeofday(&t,0);
  srand48(t.tv_sec);
	return t.tv_sec;
}


void RNG::setSeed(int seed)
{
    first = true;
    srand48(seed);
}


// normal_pair() -- generate a pair of normally-distributed random
// numbers (Box-Muller method, from Advanced Algorithms for Neural
// Networks, by T. Masters)

void normal_pair(double &x1, double &x2)
{
double u1, u2;

while (true) {		// iterate until we get a good uniform deviate
 
u1 = drand48() ; 
 
 
if (u1 == 0.0)		// can't use 0 -- try again
  continue;
 
u1 = sqrt(-2.0 * log(u1));
 
u2 = 2.0 * M_PI * drand48();
 
x1 = u1 * sin(u2);
x2 = u1 * cos(u2);

 
return;
}
}

// Return the next uniform random deviate.  

double RNG::uniform()
{
		return drand48();
}

bool RNG::coinToss()
{
    return (uniform()> 0.5) ; 
}


// Return the next Gaussian random deviate.  Uses normal_pair to
// get two deviates at a time, then returns alternating members of
// the pair.

bool RNG::first = true;

double RNG::normal()
{
static double x, y;

if (first) {
normal_pair(x,y);
first = false;
return x;
}
else {
first = true;
return y;
}
}

//void main(){
	 //
    //RNG::initSeed() ; 
	//cout <<  "uniform: " << RNG::uniform()	 << endl ; 
	//cout <<  "uniform: " << RNG::uniform()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
	//cout <<  "normal: " << RNG::normal()	 << endl ; 
//
//}



// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/utils/RNG.cpp"
// LAST MODIFICATION: "Fri, 04 Aug 2006 22:03:07 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: RNG.cpp,v 1.1.1.1 2003/10/24 19:59:28 ndunn Exp $

