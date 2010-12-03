
#include <iostream>
using std::ostream ; 

#include "XmlRenderable.hpp"



ostream& XmlRenderable::operator<<(ostream &s) 
{
    toXML(&s) ; 
    return s ; 
}

void XmlRenderable::decrementTabCount() 
{
    --mNumTabs ; 
}


void XmlRenderable::addSpacer(ostream *s,int postCounterAdjust) 
{
    for(int i = 0 ; i < mNumTabs ; i++){
        *s << mSpacerValue ; 
    }
    mNumTabs = mNumTabs + postCounterAdjust ; 
}


void XmlRenderable::setNumTabs(int newNumTabs) 
{
    mNumTabs = newNumTabs ; 
}

int XmlRenderable::getNumTabs() 
{
    return mNumTabs ; 
}




int XmlRenderable::mNumTabs = 0 ; 
string XmlRenderable::mSpacerValue = "\t" ; 

/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */


