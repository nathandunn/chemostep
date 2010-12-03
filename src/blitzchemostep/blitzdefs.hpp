/**
 * 
Array operations -- vector updates, inner products, etc -- are implemented 
* using the Blitz++ package [www.oonumerics.org/blitz].  A declaration of
* the form
*
*    Array<double,N> A;
*
* defines A to be an N-dimensional array of doubles.  Parameters following
* an array name define the size of each dimension, e.g.
*
*    Array<double,2> A(4,10);
*
* declares A to be a 2-dimensional array with 4 rows and 10 columns.
*
*/


#ifndef _blitzdefs_
#define _blitzdefs_

/// To clean up the synatax a bit, define Vector to be a 1-dimensional
/// array of doubles and Matrix to be a 2-dimensional array of doubles
/// \todo Set blitzdefs to be a long double, since this is the base calculation class, and blitz explicitly supports long doubles.

#include "blitz/memblock.h"
using blitz::deleteDataWhenDone;

#include "blitz/array.h"
using blitz::Array;
using blitz::Range;
using blitz::assertFailMode;

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <vector>
using std::vector ; 

#include <math.h>

typedef Array<double,1> Vector;
typedef Array<double,2> Matrix;

const static int MEM_POLICY = deleteDataWhenDone ; 


double getMax(const Matrix v,int position[2] = 0) ;  ///double getMax(const Vector v) ; 
double getMin(const Matrix v,int position[2] = 0) ; /// number at the first input

const Matrix shift(const Matrix theMatrix, int numToShift);  /// +N is shift rows down
												   /// replacing the input with 
                                                   /// number at the first input
const Matrix shift(const Matrix theMatrix, int numToShift,const Vector replace);  /// +N is shift rows down
												   /// replacing the input with 
                                                   /// number at the first input


double getMin(const Vector v) ; 
double getMax(const Vector v) ; 

vector<double>* getSTLVector(const Vector v) ; 
vector<vector<double>*>* getSTLMatrix(const Matrix v) ; 

//double getMin(const Vector v) ; 
//int    getMaxPosition(const Vector v) ; 
//int    getMinPosition(const Vector v) ; 

//inline void fastMult(const Matrix & m,const Vector & v,Vector & resultV,int vSize ); /// Overload the * operator for matrix-vector products

Vector& operator *(const Vector v, const Matrix m); /// Overload the * operator for matrix-vector products

bool operator ==(const Vector v,const Vector w); /// Run a loop to compare all of the values.
bool operator ==(const Matrix v,const Matrix w); /// Run a loop to compare all of the values.  



inline void fastMult(const Matrix *m,const Vector *v,Vector *resultV,int vSize )
{
  double somme  = 0.0 ; 
  for (int i = 0; i < vSize ; i++){
    somme = 0.0 ; 
    for (int j = 0; j < vSize ; j++){
        somme += (*m)(j,i)*(*v)(j);
    }
    (*resultV)(i) = somme ; 
  }
}




#endif

