#ifndef _dottynetapp_HPP_
#  define _dottynetapp_HPP_

#include <string>
using std::string ; 



#include <BaseFlatDriver.hpp>



class AppInterface ; 

/** An annealing class which has a gui.
 */

class dottynetapp : public BaseFlatDriver{

public:
    dottynetapp(AppInterface* newApp)  ; 

protected:

} ; 

#endif /* ifndef _dottynetapp_H */
// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: dottynetapp.hpp,v 1.4.2.1 2004/02/03 03:51:59 ndunn Exp $

