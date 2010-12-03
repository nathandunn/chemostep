#ifndef _ANALYSISAPP_HPP_
#  define _ANALYSISAPP_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  analysisapp was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class analysisapp : public BaseFlatDriver{

public:
    analysisapp(AppInterface* newApp)  ; 

protected:

} ; 

#endif 
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: analysisapp.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

