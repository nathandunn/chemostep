#ifndef guianneal_H
#  define guianneal_H

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  guianneal was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class guianneal : public BaseFlatDriver{

public:
    guianneal(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef guianneal_H */
// -*- C++ -*-
// FILE: "/Users/ndunn/tla/auto3--dev--1.3.3--base-0/src/guiapps/guianneal.hpp"
// LAST MODIFICATION: "Thu, 18 Mar 2004 12:34:22 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: guianneal.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

