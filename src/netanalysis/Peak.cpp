
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::pair ; 

#include "Peak.hpp"

Peak::Peak() : pair<int,double>()
{

}

Peak::Peak(int timePoint,double pointValue) : pair<int,double>(timePoint,pointValue)
{

}

int Peak::getPeakTime() 
{
    return first ; 
}

double Peak::getPeakValue() 
{
    return second ; 
}

void Peak::setTimePoint(int newPeakTime) 
{
    first = newPeakTime ;
}

void Peak::setPointValue(double newPeakValue) 
{
    second = newPeakValue ;
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


