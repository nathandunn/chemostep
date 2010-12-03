// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/AUTOGUI_1/source/appinterface/QtAppInterfaceXmlEngine.hpp"
// LAST MODIFICATION: "Thu, 18 Sep 2003 12:07:38 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtAppInterfaceXmlEngine.hpp,v 1.1.1.1 2003/10/24 19:59:33 ndunn Exp $

#ifndef TINYAPPINTERFACEXMLENGINE_HPP_
#define TINYAPPINTERFACEXMLENGINE_HPP_

#include "AppInterfaceXmlEngine.hpp" ; 



class QtAppInterfaceXmlEngine : public AppInterfaceXmlEngine{

public:
    QtAppInterfaceXmlEngine(AppInterface* appInterface=NULL)  ;  // generates a string map representation
    virtual string toXml(AppInterface* appInterface=NULL)  ;  // generates a string map representation
    virtual string doXmlCommand(string xmlString,AppInterface* appInterface=NULL)  ;    // applies an xml string to its API

protected:
    virtual string getOptionsAsXml()  ;  // generates a string map representation
    virtual string getCommandsAsXml()  ;  // generates a string map representation
    virtual string getInterfacesAsXml()  ;  // generates a string map representation


} ;



#endif



