
#include <iostream>
using std::cout ; 
using std::ostream ; 
using std::cin ; 
using std::endl ; 

#include "BlitzXmlNetRenderer.hpp" 
#include "TempSchedule.hpp"
#include "BlitzNet.hpp"

#include "SeqCheckBlitzNetAnnealer.hpp"

#ifdef DOMPI
    #include "mpi.h"
#endif 


SeqCheckBlitzNetAnnealer::SeqCheckBlitzNetAnnealer() : SeqBlitzNetAnnealer()
{
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
// FILE: "/home/ndunn/tla/auto3--dev--1.4.3--patch-11-merge/src/blitzchemostep/SeqCheckBlitzNetAnnealer.cpp"
// LAST MODIFICATION: "Tue, 13 Jul 2004 16:52:59 -0700 (ndunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

