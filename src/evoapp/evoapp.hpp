#ifndef _EVOAPP_HPP_
#  define _eVOAPP_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  evoapp was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class evoapp : public BaseFlatDriver{

public:
    evoapp(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef evoapp_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.4--patch-1/src/evoapp/evoapp.hpp"
// LAST MODIFICATION: "Mon, 14 Jun 2004 14:06:47 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: evoapp.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

