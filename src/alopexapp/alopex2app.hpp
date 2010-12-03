#ifndef _ALOPEX2APP_HPP_
#  define _ALOPEX2APP_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 *
 * Note:  alopex2app was having trouble with MPI when .bashrc was set to .bash_profile (whether or not LD_LIBRARY_PATH was set).  .bash_profile is what's initially picked up by rsh and was set in order to support distcc.  It still seems to work.  
 * \todo Make annealing standalone, using fork to start, and socket to stop.
 * 
 */

class alopex2app : public BaseFlatDriver{

public:
    alopex2app(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef alopex2app_H */
// -*- C++ -*-
// FILE: "/home/ndunn/svn/chemostep-alopex/src/alopexapp/alopex2app.hpp"
// LAST MODIFICATION: "Mon, 22 Nov 2004 10:02:13 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: alopex2app.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

