/*
 * $Id: GradDescent.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "GradDescent.hpp"

#include "TrainingTarget.hpp"

GradDescent::GradDescent() 
{
}

TrainingTarget* GradDescent::train() 
{
    TrainingTarget* currentTrainee = trainee ; 

    bool finished = false ; 
    while(!finished){

        // for each point, iterate, setting value based on previous error
       
        finished = true ; 
    }

    
    return currentTrainee ; 
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
// FILE: "/Users/ndunn/cvs/auto3TWOINPUTSTEP/src/chemostep/GradDescent.cpp"
// LAST MODIFICATION: "Mon, 29 Dec 2003 19:45:53 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: GradDescent.cpp,v 1.2 2004/01/13 20:43:35 ndunn Exp $

