// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

#include "Renderer.hpp" 
#include "CommandActor.hpp" 
#include "Option.hpp"
#include "TransmitterApp.hpp" 
#include "InterfaceTypes.hpp" 


#include <iostream>
using std::cout ; 
using std::endl ; 


Renderer::Renderer(TransmitterApp *newTransmitterApp/*NULL*/) 
{
    transmitterApp = newTransmitterApp ; 
    theCommandId = 1 ; 
    xmlMap = "" ; 
    optionList = new vector<Option*>() ; 
}


string Renderer::loadAppToMap(string newXmlString) 
{
    xmlMap  = newXmlString ; 
	 return newXmlString ; 
}


string Renderer::doCommandButton(CommandActor *commandActor) 
{
//    cout << "doing command button form: " << commandActor->getCommandName() << endl ; 
    string commandString = "" ; 

    // the commandbatch
    commandString += "<commandbatch>" ; 

    // the command
    commandString += "<command " ; 
    char buffer[50]  ;
    sprintf(buffer," id=\"%i\"",getCommandId()) ; 
    commandString += buffer ;
    commandString += ">" ; 

    // the doCommand
    commandString += "<doCommand" ; 
    commandString += " path=\"" ; 
    commandString += commandActor->getPathName() ;
    commandString += "\"" ; 
    commandString += " name=\"" ; 
    commandString += commandActor->getCommandName() ;
    commandString += "\"" ; 
    commandString += "/>" ; 
    commandString += "</command>" ; 

    commandString += "</commandbatch>" ; 
   
//    cout << "doCommandButton->about to transmit commandString: " << commandString << endl ;
    return transmitXmlCommand(commandString)  ; 
}

string Renderer::optionSetInGui(Option* optionSet,string pathToType) 
{
    return "" ; 
}

/// Puts options from preferences and sets them in the gui.
bool Renderer::loadPreferences() 
{
    return false ; 
}

/**
 *  It saves each option in the gui based on type.  
 */
bool Renderer::savePreferences() 
{
//    cout << "saving preferences" << endl ; 
    // for each option in renderer
    saveOptionPref("/sample/myname","nathan",InterfaceTypes::OPT_STRING) ; 
//    cout << "done saving preferences" << endl ; 
    return false ; 
}

void Renderer::setPreferenceURL(string newURL) 
{
    mPrefURL = newURL ; 
}

string Renderer::getPreferenceURL() 
{
    return mPrefURL ; 
}



void Renderer::setPreferenceRoot(string newRoot) 
{
    mPreferenceRoot = newRoot ; 
}

string Renderer::getPreferenceRoot() 
{
    return mPreferenceRoot ; 
}





string Renderer::setMapOption(string pathToType,Option* optionValue) 
{
    return "" ; 
}

string Renderer::addMapOption(string pathToType,Option* optionValue) 
{
	 return "" ; 
}

string Renderer::setMapCommand(string pathToType,Command* optionValue) 
{
	 return "" ; 
}

string Renderer::addMapCommand(string pathToType,Command* optionValue) 
{
	 return "" ; 
}


Option* Renderer::getMapOption(string pathToType,string optionName) 
{
	 return NULL  ; 
}

string Renderer::transmitXmlCommand(string xmlCommands) 
{
    if(transmitterApp==NULL){
        cout << "the command: " << xmlCommands << endl ; 
    }
    else{
        return transmitterApp->transmitXml(xmlCommands) ; 
    }
	 return "" ; 
}

string Renderer::transmitXmlOptions(string xmlCommands) 
{
	 return "" ; 
}

string Renderer::transmitXml(string xmlCommands,TransmitterApp *transmitterApp) 
{
	 return "" ; 
}

unsigned int Renderer::getCommandId() 
{
    return theCommandId++ ; 
}

string Renderer::setOptionFromGui(CommandActor* commandActor,string theValue) 
{

    string commandString = "" ; 

    // the commandbatch
    commandString += "<commandbatch>" ; 

    // the command
    commandString += "<command " ; 
    char buffer[50]  ;
    sprintf(buffer," id=\"%i\"",getCommandId()) ; 
    commandString += buffer ;
    commandString += ">" ; 

    // the doCommand
    commandString += "<setOption " ; 
    commandString += " path=\"" ; 
    commandString += commandActor->getPathName() ;
    commandString += "\"" ; 
    commandString += " name=\"" ; 
    commandString += commandActor->getCommandName() ;
    commandString += "\"" ; 
    commandString += " value=\"" ; 
    commandString += theValue ;
    commandString += "\"" ; 
    commandString += "/>" ; 

    commandString += "</command>" ; 

    commandString += "</commandbatch>" ; 
   
//    cout << "setOptionFromGui->about to transmit commandString: " << commandString << endl ;
    return transmitXmlCommand(commandString)  ; 

}


