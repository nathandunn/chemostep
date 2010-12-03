#include <iostream>
using std::cout ; 
using std::endl ; 

#include <sstream>
using std::ostringstream ; 

#include "ZeroOrderImpulseFilter.hpp"
#include "blitzdefs.hpp"
#include "Label.hpp"


#include "ZeroOrderLabel.hpp"

ZeroOrderLabel::ZeroOrderLabel(int newLabelCount) : Label(newLabelCount) 
{
}

ZeroOrderLabel::ZeroOrderLabel(int newLabelCount,DataFilter* newDataFilter) : Label(newLabelCount) 
{
}



string ZeroOrderLabel::print() 
{
//    ostringstream* outputString = new ostringstream() ; 
    ostringstream outputString  ; 
    outputString << "ZeroOrderLabel: " ; 
    outputString << "error[" << mError  << "] " ; 
    outputString << "avgerror[" << mError / (getErrorPoints()) << "] " ; 
    outputString << "points[" << (getErrorPoints())<< "] " ; 
    outputString << endl ; 
        
    return outputString.str()   ; 
}





/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


