// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/WORKSPACE/mapper/Component.cpp"
// LAST MODIFICATION: "Tue, 12 Aug 2003 12:59:08 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: Component.cpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#include "Component.hpp"

string Component::getKey()  
{
    return makeKey(group,name) ; 
}

const string Component::makeKey(string newGroup,string newName) 
{
    return newGroup+KEY_DELIMITER+newName ; 
}


const string Component::KEY_DELIMITER = "/" ; 

