/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "DataFilter.hpp"

DataFilter::DataFilter() 
    : mRawSignal(NULL)
{
}

int DataFilter::getNumSignals() 
{
    if(mRawSignal==NULL){
        return 0 ; 
    }
    else{
        return mRawSignal->columns() ; 
    }
}

int DataFilter::getTotalTimePoints() 
{
    if(mRawSignal==NULL){
        return 0 ; 
    }
    else{
        return mRawSignal->rows() ; 
    }
}


string DataFilter::getType() 
{
    return "DataFilter" ; 
}

void DataFilter::setFilter(DataFilter* newDataFilter) 
{
    *mRawSignal = *(newDataFilter->getSignal())  ; 
}

Matrix* DataFilter::getSignal() 
{
    return mRawSignal ; 
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

