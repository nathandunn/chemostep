// -*- C++ -*-
// FILE: "/home/ndunn/cvs/WORKSPACE/mapper/CommandArgumentField.cpp"
// LAST MODIFICATION: "Mon, 11 Aug 2003 15:20:05 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CommandArgumentField.cpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#include "CommandArgumentField.hpp"

CommandArgumentField::CommandArgumentField(string argName,string argType,string argValue,string argValueFromOption,bool set) 
{
    name = argName ; 
    type = argType ; 
    value = argValue ; 
    if(set==true){
        isSet = OPT_BOOL_TRUE ; 
    }else{
        isSet = OPT_BOOL_FALSE ; 
    }
    valueFromOption = argValueFromOption ;
}




