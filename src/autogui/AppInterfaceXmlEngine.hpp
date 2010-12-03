// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/AUTOGUI_2/source/AppInterfaceXmlEngine.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 14:10:37 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AppInterfaceXmlEngine.hpp,v 1.1.1.1 2003/10/24 19:59:21 ndunn Exp $

#ifndef APPINTERFACEXMLENGINE_HPP_
#define APPINTERFACEXMLENGINE_HPP_

#include <string>
using std::string ; 

#include <map>
using std::map ; 
using std::pair ; 

class Option ; 
class Command ; 
class Interface ; 
class AppInterface ; 

#include "InterfaceXmlString.hpp" 

class AppInterfaceXmlEngine : public InterfaceXmlString {

public:
    virtual string toXml(AppInterface* appInterface=NULL) = 0 ;  /// generates a string map representation
    virtual string doXmlCommand(string xmlString,AppInterface* appInterface=NULL) = 0 ;    /// applies an xml static string to its API

protected:
    virtual string getOptionsAsXml() =0  ;  /// generates a string map representation
    virtual string getCommandsAsXml() =0 ;  /// generates a string map representation
    virtual string getInterfacesAsXml() =0 ;  /// generates a string map representation
    AppInterface *app ; 
    map<string,Option*> *options ; 
    map<string,Command*> *commands;  /// the return type is specified 
//    map<string,Component*> *components ;  // <interface/type.interface/type>
    map<string,Interface*> *interfaces;  /// <interface/type.interface/type>


} ;



#endif



