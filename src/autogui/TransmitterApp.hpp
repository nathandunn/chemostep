// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/renderer/TransmitterApp.hpp"
// LAST MODIFICATION: "Fri, 19 Sep 2003 12:56:13 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TransmitterApp.hpp,v 1.1.1.1 2003/10/24 19:59:23 ndunn Exp $

#ifndef TRANSMITTERAPP_HPP_
#define TRANSMITTERAPP_HPP_

#include <string>
using std::string ; 


class TransmitterApp{

public:
    virtual string transmitXml(string xmlString)  =0 ; 

} ; 

#endif

