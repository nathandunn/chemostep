// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/appinterface/InterfaceXmlString.cpp"
// LAST MODIFICATION: "Tue, 16 Sep 2003 11:52:38 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: InterfaceXmlString.cpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#include "InterfaceXmlString.hpp" 

const string InterfaceXmlString::COMMAND_DOCOMMAND = "doCommand" ; 
const string InterfaceXmlString::COMMAND= "command" ; 
const string InterfaceXmlString::COMMAND_BATCH= "commandbatch" ; 
const string InterfaceXmlString::COMMAND_TYPE ="type" ; 
const string InterfaceXmlString::COMMAND_ID= "id" ; 
const string InterfaceXmlString::COMMAND_NAME= "name" ; 
const string InterfaceXmlString::COMMAND_PATH = "path" ; 
const string InterfaceXmlString::COMMAND_VALUE = "value" ; 
const string InterfaceXmlString::COMMAND_SETOPTION = "setOption" ; 
const string InterfaceXmlString::COMMAND_GETOPTION = "getOption" ; 
const string InterfaceXmlString::COMMAND_SETTYPE = "setType" ; 
const string InterfaceXmlString::COMMAND_GETTYPE = "getType" ; 
const string InterfaceXmlString::COMMAND_CREATEMAPS = "createMaps" ; 
const string InterfaceXmlString::COMMAND_DISPOSEMAPS = "disposeMaps" ; 
const string InterfaceXmlString::COMMAND_ARGUMENT = "argument" ; 
const string InterfaceXmlString::COMMANDRETURN = "commandReturn" ; 
const string InterfaceXmlString::COMMANDSTATUS = "commandStatus" ; 
const string InterfaceXmlString::COMMAND_SUCCESS ="success"; 
const string InterfaceXmlString::COMMAND_FAILURE = "failure" ; 
const string InterfaceXmlString::STATUS = "status" ; 
const string InterfaceXmlString::COMMANDSTATUS_SUCCESS ="<"+COMMANDSTATUS+" "+ STATUS+"=\""+COMMAND_SUCCESS+"\" />" ; 
const string InterfaceXmlString::COMMANDSTATUS_FAILURE ="<"+COMMANDSTATUS+" "+ STATUS+"=\""+COMMAND_FAILURE+"\" />" ; 
const string InterfaceXmlString::OPTION = "option" ;


