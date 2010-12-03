#include <iostream>
using std::cout ; 
using std::endl ; 


#include "blitzdefs.hpp"
#include "FirstOrderFilter.hpp"

FirstOrderFilter::FirstOrderFilter() : DataFilter() 
,mFirstOrderAmplitude(NULL)
,mFirstOrderTau(NULL)
{
    
}


double FirstOrderFilter::getAmplitude(int signalNumber) 
{
    return (*mFirstOrderAmplitude)(signalNumber) ; 
}


double FirstOrderFilter::getTau(int signalNumber) 
{
    return (*mFirstOrderTau)(signalNumber) ; 
}




/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


