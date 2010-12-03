#include <iostream>
using std::cout ; 
using std::endl ; 


#include "blitzdefs.hpp"
#include "ZeroOrderFilter.hpp"
#include "DataFilter.hpp"

ZeroOrderFilter::ZeroOrderFilter() : DataFilter() 
,mZeroOrderBaseline(NULL)
{
    
}


double ZeroOrderFilter::getBaseline(int signalNumber) 
{
    return (*mZeroOrderBaseline)(signalNumber) ; 
}






/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


