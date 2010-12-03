// -*- C++ -*-
//
// FILE: "/Users/nathandunn/cvs/auto2/testclasses/source/TestNN.cpp"
// LAST MODIFICATION: "Tue, 30 Sep 2003 16:35:44 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TestNN.cpp,v 1.1.1.1 2003/10/24 19:59:35 ndunn Exp $


#include "TestNN.hpp"

#include <InterfaceXmlString.hpp>

TestNN::TestNN(string newInterfaceName,string newTypeName,AppInterface* newParent) : AnnealerObject(newInterfaceName,newTypeName,newParent) {
    theFile = "" ; 
    theTempterature = 0.0  ;
    stimFeeder = NULL ; 
    targetFeeder = NULL ; 
    description = "A test neural network" ; 
}


bool TestNN::createLocalMaps()   
{
    // add components
    addInterfaceToMap(STIM_FEEDER) ; 
    addInterfaceToMap(TARGET_FEEDER) ; 

    addTypeToInterfaceMap(STIM_FEEDER,FILE_FEEDER) ; 
    addTypeToInterfaceMap(STIM_FEEDER,RANDOM_FEEDER) ; 
    addTypeToInterfaceMap(TARGET_FEEDER,FILE_FEEDER) ; 
    addTypeToInterfaceMap(TARGET_FEEDER,RANDOM_FEEDER) ; 

    // add commands
    addCommandToMap(PERTURB_NET) ; 

    // add options
    addOptionToMap(NETWORK_DATA,OPT_STRING) ; 
    addOptionToMap(TEMPERATURE_DATA,OPT_DOUBLE) ; 

    return true ; 
}


bool TestNN::disposeLocalInterfaces()   
{
   stimFeeder = NULL ; 
   targetFeeder = NULL ; 
//   *theFile = NULL ; 
   return true ; 
}



AppInterface* TestNN::setLocalType(string theInterfaceName,string theTypeName)  
{
//    cout << "TestNN setting object theInterfaceName: " << theInterfaceName << " theTypeName: " << theTypeName << endl ;
    if(theInterfaceName==STIM_FEEDER){
        stimFeeder = NULL ; 
        if(theTypeName==FILE_FEEDER){
            stimFeeder = new TestFileFeeder(STIM_FEEDER,FILE_FEEDER) ; 
        }
        else
        if(theTypeName==RANDOM_FEEDER){
            stimFeeder = new TestRandomFeeder(STIM_FEEDER,RANDOM_FEEDER) ; 
        }
        return stimFeeder ; 
    }
    else
    if(theInterfaceName==TARGET_FEEDER){
        targetFeeder = NULL ; 
        if(theTypeName==FILE_FEEDER){
            targetFeeder = new TestFileFeeder(TARGET_FEEDER,FILE_FEEDER) ; 
        }
        else
        if(theTypeName==RANDOM_FEEDER){
            targetFeeder = new TestRandomFeeder(TARGET_FEEDER,RANDOM_FEEDER) ; 
        }
        return targetFeeder ; 
    }
    return NULL ; 
}

string TestNN::getLocalOption(string name)  
{
    if(name==NETWORK_DATA){
        return theFile ; 
    }
    else
    if(name==TEMPERATURE_DATA){
        char buffer[20]  ; 
        sprintf(buffer,"%d",theTempterature) ; 
        return buffer ; 
    }

    return NULL ; 

}


bool TestNN::setLocalOption(string name,string value)
{
    if(name==NETWORK_DATA){
		theFile = value ; 
        return true ; 
    }
    else
    if(name==TEMPERATURE_DATA){
        theTempterature = atof(value.c_str()) ; 
        return true ; 
    }

    return false ; 
}

//AppInterface* TestNN::getLocalInterfaceForName(string localGroup)   
AppInterface* TestNN::getLocalTypeForInterface(string theInterfaceName)   
{
    cout << "TestNN getting localType: " <<theInterfaceName << endl ; 
    if(theInterfaceName==STIM_FEEDER){
        cout << "TestNN returning stimFeeder: "<< stimFeeder << endl ; 
      return  stimFeeder ; 
    }else
    if(theInterfaceName==TARGET_FEEDER){
      return  targetFeeder  ; 
    }else{
        return  NULL ; 
    }
    
}

bool TestNN::perturb(double temperature)  
{
    cout << "perturbin using temp: " << temperature << endl ;
    return true ;
}

string TestNN::doLocalCommand(Command* theCommand)  
{
    cout << "command in TestNN " << endl ; 
    cout << "doing local command: " << theCommand->getName() << endl ; 
    string theName= theCommand->getName() ; 
    string returnString = "" ; 
    if(theName ==PERTURB_NET){
        returnString = "<command "+InterfaceXmlString::COMMAND_ID+"=\"" + theCommand->getId() +"\">"+"</command>" ; 
        if(perturb(theTempterature)) { 
            returnString += InterfaceXmlString::COMMANDSTATUS_SUCCESS ; 
        }
        else{
            returnString += InterfaceXmlString::COMMANDSTATUS_FAILURE ; 
        }
        returnString = "</command>" ; 
    }
    return returnString ; 
}



const string TestNN::STIM_FEEDER = "STIM_FEEDER" ; 
const string TestNN::TARGET_FEEDER = "TARGET_FEEDER" ; 
const string TestNN::RANDOM_FEEDER = "RANDOM_FEEDER" ; 
const string TestNN::FILE_FEEDER = "FILE_FEEDER" ; 
const string TestNN::NETWORK_DATA= "NETWORK_DATA" ; 
const string TestNN::PERTURB_NET= "PERTURB_NET" ; 
const string TestNN::TEMPERATURE_DATA= "TEMPERATURE_DATA" ; 



