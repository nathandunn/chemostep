// -*- C++ -*-
// FILE: "/Users/ndunn/TEMP/testclasses/source/AnnealerObject.hpp"
// LAST MODIFICATION: "Sun, 28 Sep 2003 12:22:31 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AnnealerObject.hpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $

#ifndef ANNEALER_OBJ_HPP_
#define ANNEALER_OBJ_HPP_

#include <AppInterface.hpp>

class AnnealerObject : public AppInterface{

public:
    AnnealerObject(string newInterfaceName ,string newTypeName, AppInterface* newParent=NULL ): AppInterface(newInterfaceName,newTypeName,newParent){ theTemperature= 0.0 ;   } 
    virtual bool perturb(double temperature) = 0 ; 

protected:
    double theTemperature ; 
} ; 

#endif

