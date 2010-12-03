// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/blitzchemostep/source/BlitzCSVNetRenderer.hpp"
// LAST MODIFICATION: "Thu, 02 Oct 2003 15:35:50 -0700 (nathandunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: BlitzCSVNetRenderer.hpp,v 1.1.1.1 2003/10/24 19:59:24 ndunn Exp $


#ifndef _BlitzCSVNetRenderer_
#define _BlitzCSVNetRenderer_

#include <string>
using std::string ; 

#include "BlitzNetRenderer.hpp"

class BlitzNet ; 

class BlitzCSVNetRenderer : public BlitzNetRenderer {

public:
   BlitzCSVNetRenderer(string aDelimiter = " ")  ; 
   virtual void setDelimiter(string newDelimiter){ delimiter = newDelimiter ; } 
   virtual string getDelimiter(){ return delimiter ; } 
    virtual string render(BlitzNet* net) ; 

protected:
   string delimiter  ; 

} ;

#endif


