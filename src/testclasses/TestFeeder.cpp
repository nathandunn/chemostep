// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestFeeder.cpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:29:59 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestFeeder.cpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $


#include "TestFeeder.hpp"

TestFeeder::TestFeeder(string newInterfaceName,string newTypeName,AppInterface* newParent) : AppInterface(newInterfaceName,newTypeName,newParent) 
{
    description = "Generic input/output generator class." ; 
}

const string TestFeeder::GET_POINT_AT = "GET_POINT_AT"; 
const string TestFeeder::GET_NEXT_POINT = "GET_NEXT_POINT" ; 
const string TestFeeder::TIME_POINT = "TIME_POINT" ; 



