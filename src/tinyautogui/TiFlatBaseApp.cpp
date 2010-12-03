/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 

#include <Command.hpp>
#include <Renderer.hpp>

#include "TiFlatBaseApp.hpp"
#include "TinyAppInterfaceXmlEngine.hpp"

TiFlatBaseApp::TiFlatBaseApp(string interfaceName,string typeName,AppInterface* parent)  : TiAppInterface(interfaceName,typeName,parent)
    ,mBaseAppName("APP/BASEAPP")
    
{
    description = "This is a basic Flat Application, without embedded interface/types." ; 
}

bool TiFlatBaseApp::createLocalMaps()  
{
    addOptionToMap("LATEST",OPT_BOOL,&mTestBool,mBaseAppName,"Really quit?") ; 
    addOptionToMap("TESTSTRING",OPT_STRING,&mTestString,mBaseAppName,"Test string!!!!") ; 
    addCommandToMap("quit") ; 
    return true ; 
}

AppInterface* TiFlatBaseApp::setLocalType(string theInterfaceName,string theTypeName) 
{
    return NULL ; 
}

AppInterface* TiFlatBaseApp::getLocalTypeForInterface(string theInterfaceName)
{
    return this ; 
}/// accepts int.int.int (where it grabs the approriate link) or int/type.int/type



bool TiFlatBaseApp::disposeLocalInterfaces()  
{
    return true ; 
}

string TiFlatBaseApp::doLocalCommand(Command* theCommand)  
{
    cout << "doing command: " << theCommand->getName() << endl ; 
    mRenderer->savePreferences() ; 

    cout << "my string: " << mTestString << endl ; 

    // eventually this should be start and stop annealer
    string theName  = theCommand->getName() ; 
    string returnString = "" ; 
    if(theName=="quit"){
        if(mTestBool==true){
            cout << "mTestBool is true: " << mTestBool << endl ; 
            returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS; 
            exit(0) ; 
        }
        else{
            cout << "mTestBool is false : " << mTestBool << endl ; 
            returnString += InterfaceXmlString::COMMANDSTATUS_FAILURE ; 
        }
    }
    cout << "the return string" << returnString << endl ; 
    return returnString ; 
    
}

void TiFlatBaseApp::setXmlRenderer(TinyAppInterfaceXmlEngine* newXmlRenderer ) 
{
    mXmlRenderer = newXmlRenderer ; 
}


void TiFlatBaseApp::setRenderer(Renderer* newRenderer) 
{
    mRenderer = newRenderer ; 
}





/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/tinyautogui/TiFlatBaseApp.cpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 17:59:48 -0800 (nathandunn)"
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

