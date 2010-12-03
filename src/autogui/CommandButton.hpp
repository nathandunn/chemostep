// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/renderer/CommandButton.hpp"
// LAST MODIFICATION: "Mon, 22 Sep 2003 14:44:44 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: CommandButton.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $


#ifndef COMMANDBUTTON_HPP_
#define COMMANDBUTTON_HPP_

#include "CommandActor.hpp" 

class Renderer ; 

class CommandButton : public CommandActor {

public:
    CommandButton(string newCommandName,string newPathToType,string newType,Renderer* newParent) {
        thisParent = newParent ; 
        pathToType = newPathToType ; 
        commandName = newCommandName ; 
        theType = newType ; 
    } 
    virtual string getCommandName() { return commandName ; } ; 
    virtual string getPathName()  { return pathToType ; }  ; 
    virtual string getType()  { return theType ; }  ; 
    virtual Renderer *getParent()  { return thisParent ; }  ; 

protected:
    Renderer* thisParent ; 
    string pathToType ; 
    string commandName ; 
    string theType ; 

} ;


#endif




