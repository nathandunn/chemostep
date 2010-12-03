#ifndef _evoannealcheckapp_HPP_
#  define _evoannealcheckapp_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  evoannealapp was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class evoannealcheckapp : public BaseFlatDriver{

public:
    evoannealcheckapp(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef evoannealcheckapp_H */
// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--nathanevo--1.4.1--base-0/src/evoannealcheckapp/evoannealcheckapp.hpp"
// LAST MODIFICATION: "Wed, 23 Jun 2004 14:59:47 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: evoannealcheckapp.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

