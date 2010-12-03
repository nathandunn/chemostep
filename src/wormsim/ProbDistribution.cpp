
#include <iostream>
using std::cout ; 
using std::endl ; 

#include <utility>
using std::pair ; 

#include <blitzdefs.hpp>

#ifdef DOMPI
  #include "mpi.h"
#endif


#include "ProbDistribution.hpp"

ProbDistribution::ProbDistribution(double newBinSize,double maxSize/*1*/,double minSize/*0*/)  :
    mBinVector(NULL)
{
    #ifdef DOMPI
    mTransferVector = NULL ; 
    probDenst = NULL ; 
    #endif
    if(newBinSize>0){
        mBinSize = newBinSize ; 
    }
    mMaxSize = maxSize ; 
    mMinSize = minSize ; 
}

double ProbDistribution::getValueForBin(int binNumber) 
{
    return (*mBinVector)(binNumber,2) ; 
}


void ProbDistribution::setDistribution( Vector* wormRadii) 
{
    // init the bin locations and sizes and set each count to 0
    initBins() ; 

	// calculate the distance from each radii
    int numRadii = wormRadii->size() ; 
	int divisor  ; 

    #ifdef DOMPI 
    	MPI_Comm_size(MPI_COMM_WORLD, &probDistProcSize)  ; 
        divisor = wormRadii->size() * probDistProcSize ; 
	#else
        divisor = wormRadii->size() ; 
    #endif


    for(int i = 0 ; i < numRadii ; i++){
        (*mBinVector)( getBinForValue(  (*wormRadii)(i) ),2)+= ( 1.0 / divisor)  ;  
    }


    #ifdef DOMPI
        if(probDenst == NULL){
            probDenst = new double[mBinVector->rows()] ; 
        }
        // need to sum it all from each vector
	    if(mTransferVector==NULL || mTransferVector->size() != mBinVector->rows()){
            mTransferVector = new Vector(mBinVector->rows()) ; 
        }
            
        (*mTransferVector) = ( (*mBinVector)(Range::all(),2)) ; 
    	MPI_Allreduce(  (mTransferVector->data()),probDenst,mBinVector->rows(),MPI_DOUBLE, MPI_SUM,MPI_COMM_WORLD) ; 
//        delete transferVector ; 

        for(int i = 0 ; i < mBinVector->rows() ; i++){
            (*mBinVector)(i,2)= probDenst[i] ; 
        }
    #endif

}

/// Starting from the first bin
int ProbDistribution::getBinForValue(double value) 
{
    return (int) floor ( value / mBinSize ) ; 
}


/// Init the number of bins and their limits.
void ProbDistribution::initBins() 
{
    if(mBinVector == NULL){
        mBinVector = new Matrix(getNumBins(),3) ; 
    }
    double binCounter = mMinSize ; 

    for(int i = 0 ; i < mBinVector->rows() ; i++){
        (*mBinVector)(i,0) = binCounter ; 
        binCounter += mBinSize ; 
        (*mBinVector)(i,1) = binCounter ; 
        (*mBinVector)(i,2) = 0 ; 
    }
}


vector<double>* ProbDistribution::getDoublePlot() 
{
   vector<double>* returnVector = new vector<double>() ; 
   for(int i = 0 ; i < mBinVector->rows() ; i++){
       returnVector->push_back( (*mBinVector)(i,2) ) ; 
   }
   return returnVector ; 
}



int ProbDistribution::getNumBins() 
{
    double probBins = (mMaxSize-mMinSize) / mBinSize ; 
    return (int) ceil (probBins)  ; 
}

double ProbDistribution::getBinMax(int binNumber) 
{
    return  (*mBinVector)(binNumber,1)  ;
}


Bin ProbDistribution::getBin(int binNumber) 
{
    return Bin( (*mBinVector)(binNumber,0)  , (*mBinVector)(binNumber,1)  ) ; 
}


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

