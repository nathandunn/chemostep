#ifndef _GUIALOPEXER_HPP_
#  define _GUIALOPEXER_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  guialopexer was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class guialopexer : public BaseFlatDriver{

public:
    guialopexer(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef guialopexer_H */
// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--jsmerge--1.4--base-0/src/alopexapp/guialopexer.hpp"
// LAST MODIFICATION: "Tue, 17 Aug 2004 11:49:31 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: guialopexer.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

