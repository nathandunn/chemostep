/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "NeuronNamer.hpp"

string NeuronNamer::getSymmetricalName(string unsymmetricalName) 
{
    // if the name ends in L or R, simply cut off end
	int size = unsymmetricalName.size() ; 
//        cout << unsymmetricalName.substr(size-1) << " from: " << unsymmetricalName << endl ; 
    if(
        unsymmetricalName.substr(size-1)=="L" || 
        unsymmetricalName.substr(size-1)=="R" 
        ){

        return unsymmetricalName.substr(0,size-1) ; 
    }
    else{
        return unsymmetricalName ; 
    }
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
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--base-0/src/netparserapp/NeuronNamer.cpp"
// LAST MODIFICATION: "Fri, 12 Mar 2004 15:59:57 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

