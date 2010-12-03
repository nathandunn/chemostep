// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testappsAUTO/source/rendertest.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 15:07:29 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: rendertest.hpp,v 1.1.1.1 2003/10/24 19:59:24 ndunn Exp $
//
//
// 

#ifndef RENDERTEST_HPP_
#define RENDERTEST_HPP_


#include <TransmitterApp.hpp>

class Renderer ; 
class AppInterface ; 
class Type ; 

/// Test app for the Renderer classes.
/// Just using AppInterface to generate xml
class rendertest : public TransmitterApp {


public:
    rendertest() ; 
    virtual string transmitXml(string xmlString)   ; 
    virtual void setRenderer(Renderer* newRenderer)   ; 
    virtual void setApp(AppInterface* newApp)   ; 
    virtual bool runTest(int argc,char **argv)   ; 
    virtual Type* generateType()   ; 


protected:
    AppInterface* app  ; 
    Renderer* renderer ; 
    Type* theType ; 

} ; 



#endif


