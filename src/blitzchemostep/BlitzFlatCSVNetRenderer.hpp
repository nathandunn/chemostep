// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/blitzchemostep/source/BlitzFlatCSVNetRenderer.hpp"
// LAST MODIFICATION: "Wed, 01 Oct 2003 20:00:45 -0700 (nathandunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: BlitzFlatCSVNetRenderer.hpp,v 1.1.1.1 2003/10/24 19:59:25 ndunn Exp $


#ifndef _BlitzFlatCSVNetRenderer_
#define _BlitzFlatCSVNetRenderer_

#include <string>
using std::string ; 

#include "BlitzCSVNetRenderer.hpp"

class BlitzFlatCSVNetRenderer : public BlitzCSVNetRenderer {

public:
   BlitzFlatCSVNetRenderer(double newNormal = -1.0, string aDelimiter = " ") : BlitzCSVNetRenderer(aDelimiter) {
      normal = newNormal ;  
   }  
    virtual string render(BlitzNet* net) ; 

protected:
   double normal ; 

} ;

#endif


