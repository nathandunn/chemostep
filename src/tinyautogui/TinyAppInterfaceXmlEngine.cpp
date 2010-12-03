// -*- C++ -*-

#include "TinyAppInterfaceXmlEngine.hpp" 
#include "AppInterface.hpp"  
#include "Option.hpp"  
#include "Command.hpp"  
#include "Interface.hpp"  
#include "NameHandler.hpp"  

#include <tinyxml.h>

#include <map>
using std::map ; 
using std::pair ; 

#include <string>
using std::string ; 


TinyAppInterfaceXmlEngine::TinyAppInterfaceXmlEngine(AppInterface* appInterface)  
{
    if(appInterface!=NULL){
        app = appInterface ; 
        options = app->getOptionMap() ; 
        commands = app->getCommandMap() ; 
        interfaces = app->getInterfaceMap() ; 
    }
}


string TinyAppInterfaceXmlEngine::toXml(AppInterface* appInterface)  
{

    string xmlString = "" ; 
    if(appInterface!=NULL){
        app = appInterface; 
        options = app->getOptionMap() ; 
        commands = app->getCommandMap() ; 
        interfaces = app->getInterfaceMap() ; 
    }
    if(app==NULL){
        return "APP NOT SET" ; 
    }

    /* the root should be type 
     */
    xmlString += "<type name=\"" ;
    xmlString += app->getTypeName() ;
    xmlString += "\" " ;
    xmlString += " set=\"" ;
    xmlString += InterfaceTypes::OPT_BOOL_TRUE ;
    xmlString += "\" " ;
    xmlString += ">" ;
   xmlString += "\n" ; 
    
   /*
   * Do "description"
   */
   xmlString += "<description>" ; 
   xmlString += "\n" ; 
   xmlString += app->getDescription() ; 
   xmlString += "\n" ; 
   xmlString += "</description>" ; 
   xmlString += "\n" ; 

    /*
     * Do "options"
     */
   xmlString += "<options>" ; 
   xmlString += "\n" ; 
   xmlString += getOptionsAsXml() ; 
   xmlString += "</options>" ; 
   xmlString += "\n" ; 


   /*
   * Do "commands"
   */
   xmlString += "<commands>" ; 
   xmlString += "\n" ; 
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

   /*
    * Finish with the enclosing type 
    */
   xmlString += "</type>" ; 
   xmlString += "\n" ; 

   return xmlString ; 
}


string TinyAppInterfaceXmlEngine::optionToXml(Option* newOption){
   string xmlOptionString = "" ; 

   xmlOptionString += "<option name=\"" + newOption->getName()+ "\" " ; 

   xmlOptionString += "type=\"" + newOption->getType() + "\" " ; 
   xmlOptionString += "value=\"" + newOption->getValue() + "\" " ; 
   xmlOptionString += "label=\"" + newOption->getLabel() + "\" />" ; 
   return xmlOptionString ; 
}

string TinyAppInterfaceXmlEngine::getOptionsAsXml()  
{
   string optionString = "" ; 
   map<string,Option*>::iterator iter  ; 
   Option* option = NULL ; 
   if(options!=NULL){
       for(iter = options->begin() ; iter!=options->end() ; iter++){
			optionString += optionToXml(iter->second) ; 
       }
   }
   return optionString ; 
}

string TinyAppInterfaceXmlEngine::getCommandsAsXml()  
{
    string commandString = "" ; 
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
      
            commandString += "<command" ; 
            commandString += " name=\"" + currentCommand->getName()+"\"" ; 
            commandString += " type=\"" + currentCommand->getType()+"\"" ; 
            commandString += ">" ; 
       
            commandArgumentFields = currentCommand->getArguments() ; 


            if(commandArgumentFields!=NULL && commandArgumentFields->size()>0){
                  for(argumentIterator = commandArgumentFields->begin() ;  argumentIterator!= commandArgumentFields->end()  ; argumentIterator++ ){
                    currentCommandArgumentField= argumentIterator->second ; 
                    if(currentCommandArgumentField!=NULL){
                        commandString += "<argument" ; 
                        commandString += " name=\"" + currentCommandArgumentField->getName()+"\""; 
                        commandString += " type=\"" + currentCommandArgumentField->getType()+"\""; 
                        commandString += " value=\"" + currentCommandArgumentField->getValue()+"\""; 
                        commandString += " set=\"" + currentCommandArgumentField->getIsSet()+"\""; 
                        commandString += " valuefromoption=\"" + currentCommandArgumentField->getValueFromOption()+"\""; 
                        commandString += "/>" ; 
                    }
//                    ++argumentIterator; 
                }
            }
            commandString += "</command>" ; 
            commandString += "\n"  ; 
        }
   }

   return commandString ; 
}




string TinyAppInterfaceXmlEngine::getInterfacesAsXml()  
{
       string interfaceString = "" ; 
       list<string>* interfaceNames = app->getInterfaceNames() ; 
       list<string>* typeNames ; 
       list<string>::iterator interfaceNameIterator   ; 
        AppInterface* theSetType = NULL ; 
       if(interfaceNames!=NULL){
//           cout << "in number of interfaces: " << interfaceNames->size() << endl ; 
           for( interfaceNameIterator  = interfaceNames->begin() ; interfaceNameIterator != interfaceNames->end() ; interfaceNameIterator++){
                Interface* tempInterface = app->getLocalInterface( (*interfaceNameIterator)) ; 
//    cout << "the tempInterface: " << tempInterface->getTypeName() << endl ; 
    
    
           // header for interface
           interfaceString += "<interface " ; 
           interfaceString += "name=\"" ; 
           interfaceString += tempInterface->getInterfaceName() ;
           interfaceString += "\"  " ; 
           if(tempInterface->isSet()){
               interfaceString += "set=\"" ; 
               interfaceString+= InterfaceTypes::OPT_BOOL_TRUE ;
               interfaceString += "\"  " ; 
               interfaceString += "settype=\"" ; 
               interfaceString+= tempInterface->getTypeName() ;
               interfaceString += "\" " ; 
           }
           else{
               interfaceString += "set=\"" ; 
               interfaceString+= InterfaceTypes::OPT_BOOL_FALSE ;
               interfaceString += "\"  " ; 
           }
           interfaceString += ">" ; 
    
            // add unpopulated types
           list<string>* unsetTypeNames = tempInterface->getUnsetTypeNames() ; 
           list<string>::iterator unsetTypeNameIterator = unsetTypeNames->begin() ; 
           for(unsetTypeNameIterator = unsetTypeNames->begin() ; unsetTypeNameIterator != unsetTypeNames->end() ; unsetTypeNameIterator++){
               interfaceString += "<type name=\""+ (*unsetTypeNameIterator) + "\" set=\""+InterfaceTypes::OPT_BOOL_FALSE+"\" />" ; 
               interfaceString += "\n" ; 
           }
            
            // add populated type
            if(tempInterface->isSet()){
                theSetType = (AppInterface*) tempInterface->getType() ; 
//                cout << "theSetType: " << theSetType->getTypeName() << endl ; 
                // this is here because you can NOT be doing that iterating that shit
                // throught the same memory space
                interfaceString += (new TinyAppInterfaceXmlEngine())->toXml( theSetType) ; 
            }
                

           // end interface
           interfaceString += "</interface>" ; 
           interfaceString += "\n" ; 
               
       }
   }
       return interfaceString ; 
}

string TinyAppInterfaceXmlEngine::displayMessage(TiXmlNode* executionNode)  
{

    cout << "displaying the message box" << endl ; 

//    QMessageBox::message(this,

}



string TinyAppInterfaceXmlEngine::setOption(TiXmlNode* executionNode)  
{
    string theOptionString = "" ; 
    TiXmlElement* theCommand = executionNode->ToElement() ; 
    if(theCommand->Attribute(COMMAND_PATH.c_str())!=NULL){
        if(app->setOption(theCommand->Attribute(COMMAND_PATH.c_str()),theCommand->Attribute(COMMAND_NAME.c_str()),theCommand->Attribute(COMMAND_VALUE.c_str()))){
            theOptionString += COMMANDSTATUS_SUCCESS ; 
        }
        else{
            theOptionString += COMMANDSTATUS_FAILURE; 
        }
    }
    else{
       if(app->setOption("",theCommand->Attribute(COMMAND_NAME.c_str()),theCommand->Attribute(COMMAND_VALUE.c_str()))){
            theOptionString += COMMANDSTATUS_SUCCESS ; 
        }
        else{
            theOptionString += COMMANDSTATUS_FAILURE; 
        }
    }
    return theOptionString ; 
}



string TinyAppInterfaceXmlEngine::getOption(TiXmlNode* executionNode)  
{
    TiXmlElement* executionElement = executionNode->ToElement() ; 
    string getOptionReturnString = "" ; 
    if(executionElement->Attribute(COMMAND_PATH.c_str())!=NULL){
        getOptionReturnString += optionToXml(app->getOptionFromMap(executionElement->Attribute(COMMAND_PATH.c_str()),executionElement->Attribute(COMMAND_NAME.c_str()))) ; 
    }
    else{
        getOptionReturnString += optionToXml(app->getOptionFromMap("",executionElement->Attribute(COMMAND_NAME.c_str()))) ; 
    }
    
    return getOptionReturnString ; 

}



string TinyAppInterfaceXmlEngine::doCommand(TiXmlNode* executionNode)  
{
    string doCommandReturnString = "" ; 
    TiXmlNode* argumentNode = NULL ; 

    string commandName = "" ; 
    string commandType = "" ; 
    string commandId = "" ; 
    if(executionNode->ToElement()->Attribute(COMMAND_NAME.c_str())){
        commandName = executionNode->ToElement()->Attribute(COMMAND_NAME.c_str()) ; 
    }
    if(executionNode->ToElement()->Attribute(COMMAND_TYPE.c_str())){
        commandType = executionNode->ToElement()->Attribute(COMMAND_TYPE.c_str()) ;
    }
    if(executionNode->ToElement()->Attribute(COMMAND_ID.c_str())){
        commandId = executionNode->ToElement()->Attribute(COMMAND_ID.c_str());
    }

    Command* theCommand = new Command(commandName,NULL,commandType,commandId) ; 
    if(!executionNode->NoChildren() ){
        argumentNode = executionNode->FirstChild() ; 
        while ( argumentNode!=NULL && argumentNode->Value() == COMMAND_ARGUMENT  ) {
            // handle the arguments
            theCommand->addCommandArgument(argumentNode->ToElement()->Attribute(COMMAND_NAME.c_str()),argumentNode->ToElement()->Attribute(COMMAND_TYPE.c_str()),argumentNode->ToElement()->Attribute(COMMAND_VALUE.c_str())) ; 
            argumentNode = argumentNode->NextSibling() ; 
        }
    }
    if(executionNode->ToElement()->Attribute(COMMAND_PATH.c_str())!=NULL){
        doCommandReturnString += app->doCommand(executionNode->ToElement()->Attribute(COMMAND_PATH.c_str()),theCommand) ; 
    }
    else{
        doCommandReturnString += app->doLocalCommand(theCommand) ; 
    }
    return doCommandReturnString ; 

}



// will probably go back in option interface, and will dole out commands, 
// interfaces, and option getting/setting from there
string TinyAppInterfaceXmlEngine::doXmlCommand(string inputString,AppInterface* appInterface) 
{
//    cout << "TinyAppInterfaceXmlEngine-> doing xml-command: " << inputString << endl ; 


    if(appInterface!=NULL){
//        cout << "appInterface NOT NULL" << endl ; 
        app = appInterface ; 
           
        options = app->getOptionMap() ; 
        commands = app->getCommandMap() ; 
        interfaces = app->getInterfaceMap() ; 
    }

    if(app==NULL){
        cout << "appInterface IS NULL, going to crhas" << endl ; 
        return "APP NOT SET" ; 
    }

    string commandReturnString = "" ; 
    TiXmlDocument *doc = new TiXmlDocument() ;
    doc->Parse( inputString.c_str() ) ; 
    if ( doc->Error() )
    {
        printf( "Error in %s: %s\n", doc->Value(), doc->ErrorDesc() );
        return "PARSE ERROR IN COMMAND" ; 
    }
    TiXmlElement *rootElement = doc->RootElement() ; 
    TiXmlNode* node = NULL ; 
    TiXmlNode* executionNode = NULL ; 
    TiXmlElement* theCommand = NULL ; 
    node = doc->FirstChild() ;  
    string argName = "" ; 
    string argValue = "" ; 
    string argType = "" ; 

    int count = 0 ; 

    // if multiple commands, must be sent in a batch, so that 
    // the siblings may be iterated over
    if(node->Value()==COMMAND_BATCH) {
        node = node->FirstChild() ; 
    }


    while ( node!=NULL ) {
        if ( node->Type()== TiXmlNode::ELEMENT && (node->ToElement())->Value() == COMMAND) {
            commandReturnString += "<"+COMMANDRETURN +" "; 
            if(node->ToElement()->Attribute(  COMMAND_ID.c_str())!=NULL){
                commandReturnString += " "+ COMMAND_ID+"=\""+ ( (node->ToElement())->Attribute(COMMAND_ID.c_str()))+"\""; 
            }
            commandReturnString += ">"; 

            // set and return id from command, if it exists in returncommand
            executionNode = node->FirstChild() ; 

            if(executionNode->Type() == TiXmlNode::ELEMENT){
                theCommand = executionNode->ToElement();
            }
                

            // handle all of the command options
            
            // in the doCommand
            if (  executionNode->Value() == COMMAND_DOCOMMAND ) {
                commandReturnString += doCommand(executionNode) ; 
 
            }
            else
            // handle all of the get option commands
            if ( executionNode->Value() == COMMAND_GETOPTION) {
                commandReturnString += getOption(executionNode) ; 
            }
            else
            // handle all of the set option commands
            if ( executionNode->Value() == COMMAND_SETOPTION) {
                commandReturnString += setOption(executionNode) ; 
            }
            else
            // handle all of the set type commands
            if ( executionNode->Value() == COMMAND_SETTYPE) {
                commandReturnString += setType(executionNode) ; 
            }
            else
            // handle all of the create map commands
            if ( executionNode->Value() == COMMAND_CREATEMAPS ) {
                commandReturnString += createMaps(executionNode) ; 
            }
            else
            // handle all of tghe disposeMaps commands
            if ( executionNode->Value() == COMMAND_DISPOSEMAPS ) {
                commandReturnString += disposeMaps(executionNode) ; 
            }
            else
            if (  executionNode->Value() == "doMessage") {
                commandReturnString += displayMessage(executionNode) ; 
 
            }
            // no recognized command
            else{
                cerr << "unrecognized command: " << executionNode->Value() << " in : " << endl << commandReturnString << endl ; 
                commandReturnString += "<COMMAND_NOT_KNOWN />"; 
            }
        }
        commandReturnString += "</"+COMMANDRETURN +">"; 
        node = node->NextSibling();
    }

   return commandReturnString ; 
}


string TinyAppInterfaceXmlEngine::setType(TiXmlNode* executionNode)  
{
    string typeString = "" ; 
    TiXmlElement* theCommand = executionNode->ToElement() ; 
    if(theCommand->Attribute(COMMAND_PATH.c_str())!=NULL){
        if(app->setType(theCommand->Attribute(COMMAND_PATH.c_str()) ) ){
            typeString += COMMANDSTATUS_SUCCESS ; 
        } 
        else 
        {
            typeString += COMMANDSTATUS_FAILURE ; 
        } 
    }
    else{
        typeString += COMMANDSTATUS_FAILURE ;
    }
    return typeString ; 
}

string TinyAppInterfaceXmlEngine::createMaps(TiXmlNode* executionNode)  
{
    string createMapsString = "" ; 
    TiXmlElement* theCommand = executionNode->ToElement() ; 
    if(theCommand->Attribute(COMMAND_PATH.c_str())!=NULL){
        if(app->createMaps(theCommand->Attribute(COMMAND_PATH.c_str()))){
            createMapsString += COMMANDSTATUS_SUCCESS ; 
        }
        else{
            createMapsString += COMMANDSTATUS_FAILURE; 
        }
    }
    else{
       if(app->createLocalMaps()){
            createMapsString += COMMANDSTATUS_SUCCESS ; 
        }
        else{
            createMapsString += COMMANDSTATUS_FAILURE; 
        }
    }
    return createMapsString ; 
}


string TinyAppInterfaceXmlEngine::disposeMaps(TiXmlNode* executionNode)  
{
    string disposeMapsString = "" ; 
    TiXmlElement* theCommand = executionNode->ToElement() ; 
    if(theCommand->Attribute(COMMAND_PATH.c_str())!=NULL){
        if(app->disposeMaps(theCommand->Attribute(COMMAND_PATH.c_str()))){
            disposeMapsString += COMMANDSTATUS_SUCCESS ; 
        }
        else{
            disposeMapsString += COMMANDSTATUS_FAILURE; 
        }
    }
    else{
       if(app->disposeLocalMaps()){
            disposeMapsString += COMMANDSTATUS_SUCCESS ; 
        }
        else{
            disposeMapsString += COMMANDSTATUS_FAILURE; 
        }
    }
    return disposeMapsString ; 
}





