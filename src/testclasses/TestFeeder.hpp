// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestFeeder.hpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:30:16 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestFeeder.hpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $

#ifndef TESTFEEDER_HPP_
#define TESTFEEDER_HPP_


#include <AppInterface.hpp>
#include <InterfaceTypes.hpp>

class TestFeeder : public AppInterface, public InterfaceTypes{

    public:
        TestFeeder(string newInterfaceName ,string newTypeName, AppInterface* newParent=NULL ) ;
        virtual double getPoint(double time) = 0 ; 
        virtual double getNextPoint() = 0 ; 
        virtual AppInterface* setLocalType(string theInterfaceName,string theTypeName) { return NULL ; } ; // sets name and value of option
        virtual AppInterface* getLocalTypeForInterface(string theInterfaceName) { return NULL ; } ; // sets name and value of option
        static const string GET_POINT_AT ; 
        static const string GET_NEXT_POINT; 
        static const string TIME_POINT ; 

} ; 

#endif

