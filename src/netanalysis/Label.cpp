#include <iostream>
using std::cout ; 
using std::endl ; 


#include <float.h>

#include <numeric>
using std::accumulate ; 
using std::plus; 


#include "Label.hpp"

#include <vector>
using std::vector ; 

Label::Label(int newLabelCount) : mErrorVector(NULL)
,mModelTraceVector(NULL)
{
    mLabelCount = newLabelCount ; 
}

// This method sets the error vector and then calculates the respective error.
void Label::setErrorVector(vector<double>* newErrorVector) 
{
    if(mErrorVector==NULL){
        mErrorVector = new vector<double>(newErrorVector->size()) ; 
    }
    else{
        mErrorVector->resize(newErrorVector->size()) ; 
    }

    for(int i = 0 ; i < newErrorVector->size() ; i++){
        (*mErrorVector)[i] = (*newErrorVector)[i] ; 
    }

    mError = accumulate( mErrorVector->begin(),mErrorVector->end(), 0.0 ,plus<double>() ) ; 

    // test if NAN and make max error
    mError = testError(mError) ;


}

/// Tests to see if error is a NAN, returning DBL_MAX if it is.
double Label::testError(double error) 
{
    if(error != error ){
        // 
        return DBL_MAX ; 
    }
    else{
        return error  ; 
    }

}


vector<double>* Label::getModelTraceVector() 
{
    return mModelTraceVector ; 
}

void Label::setModelTraceVector(vector<double>* newModelTraceVector) 
{
    if(mModelTraceVector==NULL){
        mModelTraceVector = new vector<double>(newModelTraceVector->size()) ; 
    }
    else{
        mModelTraceVector->resize(newModelTraceVector->size()) ; 
    }

    for(int i = 0 ; i < newModelTraceVector->size() ; i++){
        (*mModelTraceVector)[i] = (*newModelTraceVector)[i] ; 
    }
}




string Label::print() 
{
    return "Base Label" ;
}

void Label::setError( double newError) 
{
    mError = newError ; 
}

int Label::getLabelCount() 
{
    return mLabelCount ; 
}

double Label::getError() 
{
    return mError ; 
}

double Label::getAverageError() 
{
    return mError / (double) getErrorPoints() ; 
}



int Label::getErrorPoints() 
{
    if(mErrorVector==NULL){
        return 0 ; 
    }
    else{
        return mErrorVector->size() ; 
    }
}

vector<double>* Label::getErrorVector() 
{
    return mErrorVector ; 
}


/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


