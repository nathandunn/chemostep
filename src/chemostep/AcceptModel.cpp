
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include "AcceptModel.hpp"

AcceptModel::AcceptModel() 
{
}

///  If first point is lower than the second, return true.
//bool AcceptModel::accept( double compare1 , double compare2 ) 
bool AcceptModel::accept( double* variables) 
{
    // cout << " in AcceptModel accept" << endl;
    // cout << " variables[0] = " << variables[0] << ", variables[1] = " << variables[1] << endl;
//    return ( variables[0] < variables[1] ) ; 
    if(variables[0] >= variables[1]){
        return false ; 
    }
    else{
        return true ; 
    }
}

int AcceptModel::getNumVariables() 
{
    return 6 ; 
}


void AcceptModel::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<acceptmodel type=\"acceptmodel\">" << endl ; ;   
    addSpacer(s,-1) ; 
    *s << "<numbervariables value=\"" << getNumVariables() << "\"/>" << endl ; ;   
    addSpacer(s,1) ; 
    *s << "</acceptmodel>" << endl ; ;   
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

