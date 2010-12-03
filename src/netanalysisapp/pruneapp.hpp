#ifndef _PRUNEAPP_HPP_
#  define _PRUNEAPP_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  pruneapp was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class pruneapp : public BaseFlatDriver{

public:
    pruneapp(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef _PRUNEAPP_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: pruneapp.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $
