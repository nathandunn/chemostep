
#include <iostream>
using std::cout ; 
using std::endl ; 
using std::ostream ; 

#include <RNG.hpp>


#include "SzuAcceptModel.hpp"

#include "AcceptModel.hpp"

SzuAcceptModel::SzuAcceptModel(double newConst)  : MetropolisAcceptModel(newConst) 
{
}

/**  Take model relative to SzuAcceptModel.  P_accept = 1 / ( 1.0+exp( (current-best )/ (mConst * temop) ) )
 *
 */
bool SzuAcceptModel::accept( double* variables) 
{
//    return ( variables[0] < variables[1] ) ; 

//    cout << "mConst: " << mConst << endl ; 
    
    double probAcceptNew = 1.0 / (1.0 + exp( ( variables[0]-variables[1] ) / ( mConst * variables[6] ) ) ) ;  

//    cout << "SzuAcceptModel: " << probAcceptNew << " current: " << variables[0] << " best: " << variables[1] << " temp: " << variables[6] << endl ; 

    
    return calcAccept( probAcceptNew) ; 
}


void SzuAcceptModel::toXML(ostream *s) 
{
    addSpacer(s,1) ; 
    *s << "<acceptmodel type=\"szuacceptmodel\">" << endl ; ;   
    addSpacer(s) ; 
    *s << "<numbervariables value=\"" << getNumVariables() << "\"/>" << endl ; ;   
    addSpacer(s,-1) ; 
    *s << "<constant value=\"" << mConst << "\"/>" << endl ; ;   
    addSpacer(s) ; 
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

