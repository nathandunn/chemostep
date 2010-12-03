/*
 * $Id: NetPerturber.cpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include "NetPerturber.hpp"
#include "RNG.hpp"

NetPerturber::NetPerturber() {
    RNG::initSeed() ; 
}

NeuralNetwork* NetPerturber::perturb(double temp,NeuralNetwork* newNet) 
{
    NeuralNetwork* returnNet = newNet ; 
//    cout << "perturbing at: " << temp << endl ; 

    // no perturbing takes place here, pointer just handed straight back
    return returnNet ; 
}

void NetPerturber::toXML(ostream *s) 
{
  // open the XML
  addSpacer(s) ; 
  *s << "<perturber type=\"netperturber\">" << endl ;
  // close the XML
  addSpacer(s) ; 
  *s << "</perturber>" << endl ;
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
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: NetPerturber.cpp,v 1.1.1.1 2003/10/24 19:59:27 ndunn Exp $

