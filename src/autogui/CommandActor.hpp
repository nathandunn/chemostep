// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/renderer/CommandActor.hpp"
// LAST MODIFICATION: "Mon, 22 Sep 2003 14:43:43 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: CommandActor.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#ifndef _COMMANDACTOR_HPP_
#define _COMMANDACTOR_HPP_

#include <string>
using std::string ; 

class CommandActor{
public:
    virtual string getCommandName() = 0 ; 
    virtual string getPathName() = 0 ; 
    virtual string getType() = 0 ; 

} ; 


#endif



