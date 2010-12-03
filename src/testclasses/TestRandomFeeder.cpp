// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestRandomFeeder.cpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:34:30 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestRandomFeeder.cpp,v 1.1.1.1 2003/10/24 19:59:35 ndunn Exp $

#include "TestRandomFeeder.hpp" 
#include <InterfaceXmlString.hpp>
//#include "RNG.hpp" 

#include <float.h>
#include <iostream.h>
#include <stdlib.h>
#include <strstream>
using std::ostrstream;


TestRandomFeeder::TestRandomFeeder(string newInterfaceName,string newTypeName,AppInterface* newParent) : TestFeeder(newInterfaceName,newTypeName,newParent) 
{
//      RNG::initSeed() ; 
      srand(time(NULL)) ; 
      center = 0 ; 
      width = 1 ; 
      description = "randomly selects numbers" ; 
}


bool TestRandomFeeder::createLocalMaps()  
{
    // add options
    addOptionToMap(RANDOM_CENTER,OPT_DOUBLE) ; 
    addOptionToMap(RANDOM_WIDTH,OPT_DOUBLE) ; 

    // add commands
    addCommandToMap(GET_NEXT_POINT) ; 
    Command *theCommand = new Command(GET_POINT_AT) ; 
    theCommand->addCommandArgument(TIME_POINT,OPT_DOUBLE) ; 
    addCommandToMap(theCommand) ; 
    return true ; 
}


double TestRandomFeeder::getNextPoint()  
{
//    double nextPoint = RNG::normal() ; 
    double nextPoint = (double) rand()/RAND_MAX ; 
    cout << "next point:  " << nextPoint  << endl ; 
    return nextPoint ; 
}

double TestRandomFeeder::getPoint(double time)  
{
//    double pointAt = RNG::normal() ; 
    double pointAt = (double) rand() ; 
    cout << "getting point at: " << pointAt << endl ; 
    return pointAt ; 
}

bool TestRandomFeeder::setLocalOption(string name,string value) 
{
    cout << "setting local option with : " << name << " and " << value << endl ; 
    if(name==RANDOM_CENTER){
        center = atof(value.c_str()) ; 
        cout << "value set: " << center << endl ; 
        return true ; 
    }
    else
    if(name==RANDOM_WIDTH){
        width = atof(value.c_str()) ; 
        return true ; 
    }
    return false ; 
}



string TestRandomFeeder::getLocalOption(string name) 
{
    cout << "getting local option with: " << name << endl ; 
    if(name==RANDOM_CENTER){
        ostrstream returnString ; 
        returnString << center ; 
        return returnString.str() ; 
    }
    else
    if(name==RANDOM_WIDTH){
        ostrstream returnString ; 
        returnString << width ; 
        return returnString.str() ; 
    }
    return "" ; 
}

string TestRandomFeeder::doLocalCommand(Command* theCommand)  
{
    string name = theCommand->getName() ; 
    string returnString = "" ; 
    returnString = "<command "+InterfaceXmlString::COMMAND_ID+"=\"" + theCommand->getId() +"\">" ; 
    // note:  we should actually be calling the calls in question
    if(name==GET_NEXT_POINT){
        getNextPoint() ; 
        returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS ; 
    }
    else
    if(name==GET_POINT_AT){
        getPoint(2.2) ; 
        returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS ; 
    }
    return returnString+"</command>" ; 
}



bool TestRandomFeeder::disposeLocalInterfaces()     
{
    center  ;  
    width  ; 
    center = 0 ; 
    width = 1 ; 
}


const string TestRandomFeeder::RANDOM_CENTER = "CENTER" ; 
const string TestRandomFeeder::RANDOM_WIDTH = "WIDTH" ; 



