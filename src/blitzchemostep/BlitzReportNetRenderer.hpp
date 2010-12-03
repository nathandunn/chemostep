// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/blitzchemostep/source/BlitzReportNetRenderer.hpp"
// LAST MODIFICATION: "Thu, 02 Oct 2003 16:11:21 -0700 (nathandunn)"
// (C) 2002 by Nathan Dunn, <ndunn@idiom.com>
// $Id: BlitzReportNetRenderer.hpp,v 1.1.1.1 2003/10/24 19:59:26 ndunn Exp $


#ifndef _BLITZREPORTNETRENDERER_HPP_
#define _BLITZREPORTNETRENDERER_HPP_

#include "BlitzNetRenderer.hpp"

#include <string>
using std::string ; 

class BlitzNet ; 

class BlitzReportNetRenderer: public BlitzNetRenderer{

public:
   BlitzReportNetRenderer() : BlitzNetRenderer() { }; 
   virtual string render(BlitzNet *net) ; 
} ;

#endif


