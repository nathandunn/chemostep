// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestFileFeeder.cpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:33:12 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestFileFeeder.cpp,v 1.1.1.1 2003/10/24 19:59:34 ndunn Exp $

#include "TestFileFeeder.hpp"

#include <Command.hpp>
#include <InterfaceXmlString.hpp>

#include <stdio.h>

TestFileFeeder::TestFileFeeder(string newInterfaceName,string newTypeName,AppInterface* newParent) : TestFeeder(newInterfaceName,newTypeName,newParent) 
{
    theFileName = "/tmp/tempFile" ; 
    pointAt= 0 ; 
    description = "Iterates over a loaded file." ; 
}


double TestFileFeeder::getPoint(double time) 
{
    cout << "getting point, fileName set to: " << theFileName << endl ; 
    return 2 ;
}

double TestFileFeeder::getNextPoint()  
{
    cout << "getting next point, fileName set to: " << theFileName << endl ; 
    return 3 ; 
}

void TestFileFeeder::setFile(string fileName)  
{
   theFileName = fileName ; 
}

string TestFileFeeder::getFileName()  
{
    return theFileName  ; 
}

bool TestFileFeeder::setLocalOption(string name,string value) 
{
    if(name==FILE_FILENAME){
        theFileName = value ; 
        return true ; 
    }
    return false ; 
}

AppInterface* TestFileFeeder::getLocalInterfaceForName(string localName) 
{
    return NULL ; 
}

string TestFileFeeder::getLocalOption(string name) 
{
    if(name==FILE_FILENAME){
        return theFileName ; 
    }
    else
    if(name==POINT_AT){
        char buffer[20] ; 
        sprintf(buffer,"%d",pointAt) ; 
        return  buffer ; 
    }
    return NULL ; 
}

bool TestFileFeeder::createLocalMaps() 
{
    // add options
    addOptionToMap(FILE_FILENAME,OPT_STRING) ; 
    addOptionToMap(POINT_AT,OPT_INT) ; 
    

    // add commands
    addCommandToMap(GET_NEXT_POINT) ; 
    Command *theCommand = new Command(GET_POINT_AT,OPT_DOUBLE) ; 
    theCommand->addCommandArgument(TIME_POINT,OPT_DOUBLE) ; 
    addCommandToMap(GET_POINT_AT,theCommand) ; 
    return true ; 
}


bool TestFileFeeder::disposeLocalInterfaces()     
{
    theFileName = "/tmp/tempFile" ; 
    return true ; 
}



string TestFileFeeder::doLocalCommand(Command* theCommand)  
{
    string name = theCommand->getName() ; 
    string returnString = "" ; 
    // note:  we should actually be calling the calls in question
    if(name==GET_NEXT_POINT){
        getNextPoint() ; 
        returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS ; 
    }
    else
    if(name==GET_POINT_AT){
        getPoint(2) ; 
        returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS ; 
    }
    return returnString ; 
}


const string TestFileFeeder::FILE_FILENAME= "FILE_FILENAME" ; 
const string TestFileFeeder::POINT_AT= "POINT_AT" ; 

