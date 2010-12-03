// -*- C++ -*-
#include "Type.hpp" 

#include "Command.hpp"
#include "Option.hpp"

Type::Type(string newTypeName,Type* parentType,string newInterfaceName) 
{
    typeName = newTypeName; 
    parent = parentType ; 
    interfaceName = newInterfaceName ; 
    description = "" ; 
    optionMap = NULL ; 
    interfaceMap = NULL ; 
    commandMap = NULL ; 
}



string Type::getInterfaceName() 
{
    return interfaceName ; 
}


Type* Type::setParent(Type* newParentType) 
{
    parent = newParentType ; 
    return parent ; 
}


string Type::getTypeName() 
{
    return typeName ; 
}

bool Type::isRootType() 
{
    return (parent==NULL)  ; 
}

Type* Type::getParent() 
{
    return parent ; 
}


map<string,Option*>* Type::getOptionMap()  
{
    return optionMap ; 
}


map<string,Command*>* Type::getCommandMap()  
{
    return commandMap ;
}




map<string,Interface*>* Type::getInterfaceMap() 
{
    return interfaceMap ; 
}



bool Type::addOptionToMap(Option *theOption) {
    if(optionMap == NULL){
		optionMap = new map<string,Option*>() ; 
    }

//    cout << "theOption->getName(): " << theOption->getName() << endl ; 
//    cout << "theOption: " << theOption << endl ; 
//    cout << "theOption->getRef(): " << theOption->getRef() << endl ; 

    optionMap->insert(pair<string,Option*>(theOption->getName(),theOption)) ; 
    return true ; 
}


bool Type::addOptionToMap(string newName,string newType,void* newRef,string newPath,string newLabel,string newValue,bool set) {
   return addOptionToMap(new Option(newName,newType,newRef,newPath,newLabel,newValue,set)) ;  
}




bool Type::addCommandToMap(Command* newCommand)   
{
    return addCommandToMap(newCommand->getName(),newCommand) ; 
}

bool Type::addCommandToMap(string key,void* newRef,Command* newCommand)   
{
    if(commandMap == NULL){
		commandMap = new map<string, Command* >() ; 
    }
    if(newCommand==NULL){
        newCommand = new Command() ; 
        newCommand->setName(key) ; 
        newCommand->setRef(newRef) ; 
    }
    commandMap->insert(pair<string, Command* >(key,newCommand)) ; 
    return true ; 
}


string Type::getDescription()  
{
    return description ; 
}

void Type::setDescription(string newDescription)  
{
    description = newDescription ; 
}



