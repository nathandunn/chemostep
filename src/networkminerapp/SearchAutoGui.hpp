// -*- C++ -*-
// FILE: "/Users/ndunn/tla/auto3--updateminer--1.3.4--patch-3/src/networkminerapp/SearchAutoGui.hpp"
// LAST MODIFICATION: "Mon, 05 Apr 2004 20:50:35 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: SearchAutoGui.hpp,v 1.11 2003/07/16 00:37:12 ndunn Exp $

#ifndef _SEARCHAUTO_GUI_
#define _SEARCHAUTO_GUI_

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <string>
using std::string; 

#include <qapplication.h>

//#include "SearchDriver.hpp" 
#include <ConnectionPath.hpp> 
#include <BaseFlatDriver.hpp>


class SearchAutoGui: public BaseFlatDriver {

public:
    SearchAutoGui(AppInterface *newApp) ; 
    // this will include all of the options
//    virtual void logTheMessage(string message) ; 
//    virtual void logGUIMessage(string message) ; 
    

private:
    string messageText ; 

} ;

#endif

