#include <iostream>
using std::cout ; 
using std::endl ; 

#include "LabelFactory.hpp"

LabelFactory::LabelFactory( DataFilter* newDataFilter,LabelIdentifier* newLabelIdentifier) 
:mDataFilter(newDataFilter)  
,mLabelIdentifier(newLabelIdentifier) 
{
}


LabelSet* LabelFactory::extractLabelSet(RawSignal* newRawSignal) 
{
   return   mLabelIdentifier->identifyLabel( mDataFilter->extractData(newRawSignal) )  ; 
}


DataFilter* LabelFactory::getDataFilter() 
{
    return mDataFilter ; 
}

LabelIdentifier* LabelFactory::getLabelIdentifier() 
{
    return mLabelIdentifier ; 
}



/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */



// -*- C++ -*-

// (C) 2004 by Nathan Dunn, <ndunn@mac.com>


