/*
 * $Id: EvalTrace.cpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string ; 

#include "EvalTrace.hpp"


/// this should be a memory call, since we want the same evaluator used int he network
void EvalTrace::setEvaluator(NetEvaluator *newEvaluator) 
{
    evaluator = newEvaluator ; 
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
// FILE: "/Users/nathandunn/cvs/auto2/chemostepAUTO/source/EvalTrace.cpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 15:03:53 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: EvalTrace.cpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $

