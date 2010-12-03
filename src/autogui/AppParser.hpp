// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/AUTOGUI_2/source/AppParser.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 14:10:48 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: AppParser.hpp,v 1.1.1.1 2003/10/24 19:59:21 ndunn Exp $

#ifndef _APPPARSER_HPP_
#define _APPPARSER_HPP_

#include "InterfaceXmlString.hpp" 
#include <string>
using std::string ;

class Renderer ; 

class AppParser : public InterfaceXmlString {

public:
    virtual string parse(Renderer* newRenderer,string xmlString)=0 ; /// this should simply be a series of calls to AddGuiType

protected:
    Renderer* thisRenderer ; 
    string  thisXml ; 

} ; 


#endif


