
#include <iostream>
using std::cout ; 
using std::endl ; 

#include "Annealer.hpp"


Annealer::Annealer() :  
    mBackStep(0) 
    ,mSetBack(0)  
    ,iterPerTemp(0)  
{
}

void Annealer::setBackStep(double newBackStep) 
{
    mBackStep = newBackStep ; 
}

void Annealer::setSetBack(int newSetBack) 
{
    mSetBack = newSetBack ; 
}

int Annealer::getSetBack() 
{
    return mSetBack  ; 
}

double Annealer::getBackStep() 
{
    return mBackStep ; 
}

void Annealer::setTempSchedule(TempSchedule* newTempSchedule) 
{
    tempSchedule = newTempSchedule ; 
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

