// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/appinterface/InterfaceXmlString.hpp"
// LAST MODIFICATION: "Tue, 16 Sep 2003 11:52:33 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: InterfaceXmlString.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#ifndef _INTERFACEXMLSTRING_HPP_
#define _INTERFACEXMLSTRING_HPP_


#include <string>
using std::string ; 

class InterfaceXmlString{

public:
    static const string COMMAND; 
    static const string COMMAND_BATCH ; 
    static const string COMMAND_DOCOMMAND ; 
    static const string COMMAND_SETOPTION; 
    static const string COMMAND_GETOPTION; 
    static const string COMMAND_SETTYPE; 
    static const string COMMAND_GETTYPE; 
    static const string COMMAND_CREATEMAPS; 
    static const string COMMAND_DISPOSEMAPS; 
    static const string COMMANDRETURN ; 
    static const string COMMANDRETURN_SUCCESS ; 
    static const string COMMANDRETURN_FAILURE ; 
    static const string COMMAND_ID ; 
    static const string COMMAND_NAME ; 
    static const string COMMAND_VALUE; 
    static const string COMMAND_PATH; 
    static const string COMMAND_ARGUMENT  ; 
    static const string COMMANDSTATUS  ; 
    static const string COMMAND_SUCCESS ; 
    static const string COMMAND_FAILURE  ; 
    static const string COMMAND_TYPE ; 
    static const string STATUS ; 
    static const string COMMANDSTATUS_SUCCESS  ; 
    static const string COMMANDSTATUS_FAILURE  ; 
    static const string OPTION ; 

} ; 


#endif

