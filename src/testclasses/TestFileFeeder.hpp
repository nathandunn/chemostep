// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestFileFeeder.hpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:33:59 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestFileFeeder.hpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $

#ifndef TEST_FILE_FEEDER_HPP_
#define TEST_FILE_FEEDER_HPP_

#include <stdlib.h>
#include "TestFeeder.hpp"



class TestFileFeeder : public TestFeeder {

public:
    TestFileFeeder(string newInterfaceName ,string newTypeName, AppInterface* newParent=NULL ) ;
    virtual double getPoint(double time) ; 
    virtual string doLocalCommand(Command* theCommand)  ;    
    virtual double getNextPoint()  ; 
    virtual bool disposeLocalInterfaces()     ;  
    virtual void setFile(string fileName)  ; 
    virtual string getFileName()  ; 
    virtual bool setLocalOption(string name,string value) ; 
    virtual AppInterface* setLocalType(string theInterfaceName,string theTypeName) { return NULL ; } ; // sets name and value of option
    virtual string getLocalOption(string name) ; 
    virtual bool createLocalMaps() ; 
    virtual AppInterface* getLocalInterfaceForName(string localName) ;  
    static const string FILE_FILENAME ; 
    static const string POINT_AT; 


protected:
    string theFileName ; 
    int pointAt ; 


} ; 

#endif

