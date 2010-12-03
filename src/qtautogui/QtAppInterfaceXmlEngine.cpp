// -*- C++ -*-
// FILE: "/Users/nathandunn/svn/chemotrunk/src/qtautogui/QtAppInterfaceXmlEngine.cpp"
// LAST MODIFICATION: "Wed, 01 Dec 2004 18:55:34 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtAppInterfaceXmlEngine.cpp,v 1.1.1.1 2003/10/24 19:59:33 ndunn Exp $

#include "QtAppInterfaceXmlEngine.hpp" 
#include "AppInterface.hpp"  
#include "Option.hpp" ; 
#include "Command.hpp" ; 
#include "Interface.hpp" ; 
#include "NameHandler.hpp" ; 

#include <map>
using std::map ; 
using std::pair ; 

#include <string>
using std::string ; 

#include <qdom.h>


QtAppInterfaceXmlEngine::QtAppInterfaceXmlEngine(AppInterface* appInterface)  
{
    if(appInterface!=NULL){
        app = newAppInterface ; 
        options = app->getOptionMap() ; 
        commands = app->getCommandMap() ; 
        interfaces = app->getInterfaceMap() ; 
    }
}


string QtAppInterfaceXmlEngine::toXml(AppInterface* newAppInterface)  
{
    if(appInterface!=NULL){
        app = newAppInterface ; 
        options = app->getOptionMap() ; 
        commands = app->getCommandMap() ; 
        interfaces = app->getInterfaceMap() ; 
    }
    if(app==NULL){
        return "APP NOT SET" ; 
    }

    string xmlString = "" ; 

   /*
   * Do "description"
   */
   xmlString += "<description>" ; 
   xmlString += app->getDescription() ; 
   xmlString += "</description>" ; 
   xmlString += "\n" ; 

    /*
     * Do "options"
     */
   xmlString += "<options>" ; 
   xmlString += getOptionsAsXml() ; 
   xmlString += "</options>" ; 
   xmlString += "\n" ; 




   /*
   * Do "commands"
   */
   xmlString += "<commands>" ; 
   xmlString += getCommandsAsXml() ; 
   xmlString += "</commands>" ; 
   xmlString += "\n" ; 

   /*
   * Do "components"
   */
   xmlString += "<interfaces>" ; 
   xmlString += getInterfacesAsXml() ; 
   xmlString += "</interfaces>" ; 
   xmlString += "\n" ; 

   return xmlString ; 
}


string QtAppInterfaceXmlEngine::getOptionsAsXml()  
{
   string xmlString ; 
   map<string,Option*>::iterator iter  ; 
   Option* option = NULL ; 
   if(options!=NULL){
       for(iter = options->begin() ; iter!=options->end() ; iter++){
           option = iter->second ; 
           xmlString += "<option name=\"" + iter->first + "\" " ; 

           xmlString += "type=\"" + option->getType() + "\" " ; 
           if( (option->getValueVector())->size()==1){
               xmlString += "value=\"" + option->getValue() + "\" />" ; 
           }
           else{
               vector<string>* valueVector = option->getValueVector() ; 
               int vectorSize = valueVector->size() ; 
               cout << ">" << endl ;  // close open option
               for(int i = 0 ; i < vectorSize ; i++){
                   xmlString += "<vector value=\"" + (*valueVector)[i] + "\" />" ; 
               }
               xmlString += "</option>" ; 
           }
       }
   }
   return xmlString ; 
}

string QtAppInterfaceXmlEngine::getCommandsAsXml()  
{
   string xmlString ; 
   map<string,Command*>::iterator commandIterator; 
   map<string,CommandArgumentField*>::iterator argumentIterator; 
   Command *currentCommand = NULL ; 
   CommandArgumentField *currentCommandArgumentField = NULL ; 
   map<string,CommandArgumentField*> *commandArgumentFields = NULL ; 
   string argumentName = "" ; 
   string argumentType = "" ; 

   if(commands!=NULL){
       
		for(commandIterator = commands->begin() ; commandIterator != commands->end() ; commandIterator++ ){
            currentCommand = commandIterator->second ; 
      
            xmlString += "<command" ; 
            xmlString += " name=\"" + currentCommand->getName()+"\"" ; 
            xmlString += " type=\"" + currentCommand->getType()+"\"" ; 
            xmlString += ">" ; 
       
            commandArgumentFields = currentCommand->getArguments() ; 


            if(commandArgumentFields!=NULL && commandArgumentFields->size()>0){
                  for(argumentIterator = commandArgumentFields->begin() ;  argumentIterator!= commandArgumentFields->end()  ; argumentIterator++ ){
                    currentCommandArgumentField= argumentIterator->second ; 
                    if(currentCommandArgumentField!=NULL){
                        xmlString += "<argument" ; 
                        xmlString += " name=\"" + currentCommandArgumentField->getName()+"\""; 
                        xmlString += " type=\"" + currentCommandArgumentField->getType()+"\""; 
                        xmlString += " value=\"" + currentCommandArgumentField->getValue()+"\""; 
                        xmlString += " set=\"" + currentCommandArgumentField->getIsSet()+"\""; 
                        xmlString += " valuefromoption=\"" + currentCommandArgumentField->getValueFromOption()+"\""; 
                        xmlString += "/>" ; 
                    }
//                    ++argumentIterator; 
                }
            }
            xmlString += "</command>" ; 
        }
   }

   return xmlString ; 
}

string QtAppInterfaceXmlEngine::getInterfacesAsXml()  
{
   string xmlString ; 
   list<string>* interfaceNames = app->getInterfaceNames() ; 
   list<string>* typeNames ; 
   list<string>::iterator interfaceNameIterator ; 
   list<string>::iterator typeNameIterator ;  // iterates through the names in the group
   if(interfaceNames!=NULL){
       for(interfaceNameIterator = interfaceNames->begin() ; interfaceNameIterator != interfaceNames->end() ; interfaceNameIterator++){
           xmlString += "<interface name=\""+ (*interfaceNameIterator) + "\">" ; 
               // give interface
               AppInterface* tempType = app->getLocalTypeForInterface(*interfaceNameIterator) ; 
//               typeNames = getNamesForGroup(*interfaceNameIterator) ; 
               typeNames = app->getTypeNamesForInterface(*interfaceNameIterator) ; 
               if(tempType != NULL ){
                   xmlString += "<type name=\""+ tempType->getTypeName() + "\" set=\""+InterfaceTypes::OPT_BOOL_TRUE+"\" >" ; 
//                   xmlString  += tempType->getMap() ; 
                   xmlString  += (new QtAppInterfaceXmlEngine())->toXml(tempType) ; 
                   xmlString += "</type>" ; 
                   for(typeNameIterator = typeNames->begin() ; typeNameIterator != typeNames->end() ; typeNameIterator++){
                       if((*typeNameIterator)!=tempType->getTypeName()){
                       xmlString += "<type name=\""+ (*typeNameIterator) + "\" set=\""+InterfaceTypes::OPT_BOOL_FALSE+"\" />" ; 
                       }
                   }
               }
               else{
//                   xmlString += "<type name=\"NOT_SET\">" ; 
                   for(typeNameIterator = typeNames->begin() ; typeNameIterator != typeNames->end() ; typeNameIterator++){
                       xmlString += "<type name=\""+ (*typeNameIterator) + "\" set=\""+InterfaceTypes::OPT_BOOL_FALSE+"\" />" ; 
                   }
               }
           xmlString += "</interface>" ; 
       }
   }
   return xmlString ; 
}



// will probably go back in option interface, and will dole out commands, 
// interfaces, and option getting/setting from there
string QtAppInterfaceXmlEngine::doXmlCommand(string xmlString,AppInterface* appInterface) 
{
    string returnString = "" ; 
//    domTree.setContent( (QString) xmlString) ; 
    QDomDocument domTree ; 
    domTree.setContent(  xmlString) ; 
    QDomElement root = domTree.documentElement() ; 
    QDomNode node ,executionNode, argumentNode ; 
    QDomElement theCommand ; 
//    node = root.firstChild();
    node = root ; 
    string argName = "" ; 
    string argValue = "" ; 
    string argType = "" ; 
//    cout << "theString : " << xmlString <<  endl ;

    int count = 0 ; 

    // if multiple commands, must be sent in a batch, so that 
    // the siblings may be iterated over
    if(node.nodeName()==COMMAND_BATCH) {
        node = node.firstChild() ; 
    }

    while ( !node.isNull() ) {
        if ( node.isElement() && node.nodeName() == COMMAND) {
            returnString += "<"+COMMANDRETURN +" "; 
            if(node.toElement().hasAttribute( (QString) COMMAND_ID)){
                returnString += COMMAND_ID+"=\""+ ( node.toElement().attribute(COMMAND_ID).ascii())+"\""; 
            }
            returnString += ">"; 

            // set and return id from command, if it exists in returncommand
            executionNode = node.firstChild() ; 

            if(executionNode.isElement()){
                theCommand = executionNode.toElement();
            }
                
//    cout << "doing xml command: " << executionNode.nodeName() <<  endl ;

            // handle all of the command options
            if (  executionNode.nodeName() == COMMAND_DOCOMMAND ) {
                Command* theCommand = new Command(executionNode.toElement().attribute(COMMAND_NAME),executionNode.toElement().attribute(COMMAND_TYPE)) ; 
                if(executionNode.hasChildNodes() ){
                    argumentNode = executionNode.firstChild() ; 
                    while ( !argumentNode.isNull() && argumentNode.nodeName() == COMMAND_ARGUMENT  ) {
                        // handle the arguments
                        theCommand->addCommandArgument(argumentNode.toElement().attribute(COMMAND_NAME),argumentNode.toElement().attribute(COMMAND_TYPE),argumentNode.toElement().attribute(COMMAND_VALUE)) ; 
                        argumentNode = argumentNode.nextSibling() ; 
                    }
                }
                if(executionNode.toElement().hasAttribute(COMMAND_PATH)){
                    returnString += app->doCommand(executionNode.toElement().attribute(COMMAND_PATH),theCommand) ; 
                }
                else{
                    returnString += app->doLocalCommand(theCommand) ; 
                }
            }
            // handle all of the get option commands
            else
            if ( executionNode.nodeName() == COMMAND_GETOPTION) {
                if(theCommand.hasAttribute(COMMAND_PATH)){
                    returnString += app->getOption(theCommand.attribute(COMMAND_PATH),theCommand.attribute(COMMAND_NAME)) ; 
                }
                else{
                    returnString += app->getLocalOption(theCommand.attribute(COMMAND_NAME)) ; 
                }
            }
            // handle all of the set option commands
            else
            if ( executionNode.nodeName() == COMMAND_SETOPTION) {
                if(theCommand.hasAttribute(COMMAND_PATH)){
                    if(app->setOption(theCommand.attribute(COMMAND_PATH),theCommand.attribute(COMMAND_NAME),theCommand.attribute(COMMAND_VALUE))){
                        returnString += COMMANDSTATUS_SUCCESS ; 
                    }
                    else{
                        returnString += COMMANDSTATUS_FAILURE; 
                    }
                }
                else{
                   if(app->setLocalOption(theCommand.attribute(COMMAND_NAME),theCommand.attribute(COMMAND_VALUE))){
                        returnString += COMMANDSTATUS_SUCCESS ; 
                    }
                    else{
                        returnString += COMMANDSTATUS_FAILURE; 
                    }
                }
            }
            // handle all of the set type commands
            else
            if ( executionNode.nodeName() == COMMAND_SETTYPE) {
                if(theCommand.hasAttribute(COMMAND_PATH)){
                    if(app->setType(theCommand.attribute(COMMAND_PATH)+NameHandler::TYPE_DELIMITER+theCommand.attribute(COMMAND_NAME) ) ){ returnString += COMMANDSTATUS_SUCCESS ; } else {returnString += COMMANDSTATUS_FAILURE ; } 
                }
                else{
                    returnString += COMMANDSTATUS_FAILURE ;
                }
            }
            // handle all of the get components commands
            else
            if ( executionNode.nodeName() == COMMAND_CREATEMAPS ) {
                if(theCommand.hasAttribute(COMMAND_PATH)){
                    if(app->createMaps(theCommand.attribute(COMMAND_PATH))){
                        returnString += COMMANDSTATUS_SUCCESS ; 
                    }
                    else{
                        returnString += COMMANDSTATUS_FAILURE; 
                    }
                }
                else{
                   if(app->createLocalMaps()){
                        returnString += COMMANDSTATUS_SUCCESS ; 
                    }
                    else{
                        returnString += COMMANDSTATUS_FAILURE; 
                    }
                }
            }
            else
            if ( executionNode.nodeName() == COMMAND_DISPOSEMAPS ) {
                if(theCommand.hasAttribute(COMMAND_PATH)){

                    if(app->disposeMaps(theCommand.attribute(COMMAND_PATH))){
                        returnString += COMMANDSTATUS_SUCCESS ; 
                    }
                    else{
                        returnString += COMMANDSTATUS_FAILURE; 
                    }
                }
                else{
                   if(app->disposeLocalMaps()){
                        returnString += COMMANDSTATUS_SUCCESS ; 
                    }
                    else{
                        returnString += COMMANDSTATUS_FAILURE; 
                    }
                }
            }
            else{
                cerr << "unrecognized command: " << executionNode.nodeName() << " in : " << endl << xmlString << endl ; 
                returnString += "<COMMAND_NOT_KNOWN />"; 
            }
        }
        returnString += "</"+COMMANDRETURN +">"; 
        node = node.nextSibling();
    }

   return returnString ; 
}


