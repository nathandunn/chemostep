// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestRandomFeeder.hpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:31:31 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestRandomFeeder.hpp,v 1.1.1.1 2003/10/24 19:59:35 ndunn Exp $

#ifndef TESTRANDOM_FEEDER_HPP_
#define TESTRANDOM_FEEDER_HPP_

#include <Command.hpp>
#include <InterfaceXmlString.hpp>

#include <stdlib.h>

#include "TestFeeder.hpp"

class TestRandomFeeder: public TestFeeder  {

public:
    TestRandomFeeder(string newInterfaceName ,string newTypeName, AppInterface* newParent=NULL ) ;
    virtual string doLocalCommand(Command* theCommand)  ;    
    virtual double getPoint(double time)  ; 
    virtual bool disposeLocalInterfaces()     ;  
    virtual double getNextPoint()  ; 
    virtual AppInterface* setLocalType(string theInterfaceName,string theTypeName) { return NULL ; } ; // sets name and value of option
    virtual bool setLocalOption(string name,string value) ; 
    virtual string getLocalOption(string name) ; 
    virtual bool createLocalMaps()  ;  // creates the map here instead of constructure
    static const string RANDOM_CENTER ; 
    static const string RANDOM_WIDTH; 

private:
    double center  ;  
    double width  ; 

} ; 

#endif

