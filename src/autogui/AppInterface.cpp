// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>


#include "AppInterface.hpp"
#include "Interface.hpp"
#include "CommandArgumentField.hpp"
#include "Command.hpp"
#include "Option.hpp"
#include "NameHandler.hpp" 

/// Note:  We change the callback order to Type.
AppInterface::AppInterface(string newInterfaceName,string newTypeName,AppInterface* newParent) : Type(newTypeName,newParent,newInterfaceName) 
{
}

AppInterface* AppInterface::operator=(AppInterface* rhs){
    typeName = rhs->getTypeName(); 
    interfaceName = rhs->getInterfaceName() ; 
    parent = rhs->getParent() ; 
    optionMap = rhs->getOptionMap() ; 
    interfaceMap = rhs->getInterfaceMap() ; 
    commandMap = rhs->getCommandMap() ; 
    return this ; 
}

//AppInterface::AppInterface(): Type{
//    typeName = "TYPE_NOT_SET" ; 
//    interfaceName = "INTERFACE_NOT_SET" ; 
//    description = "No description given" ; 
//
//    optionMap = NULL ; 
//    interfaceMap = NULL ; 
//    commandMap = NULL ; 
//}


Interface* AppInterface::getLocalInterface(string theInterfaceName) 
{
// cout << "getLocalInterface interfaceMap: " << interfaceMap << endl ; 
    map<string,Interface*>::iterator iter ;  
    iter = interfaceMap->find(theInterfaceName) ; 

    if(iter==interfaceMap->end()){
        return NULL ; 
    }

    return iter->second ; 
}




AppInterface::~AppInterface(){
//    disposeMaps() ; 
    delete interfaceMap ; 
    delete optionMap ; 
    delete commandMap ; 
}




bool AppInterface::setOption(string pathToType, string optionName,string optionValue)
{
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
//    cout << "the tempType: " << tempType << endl ; 
    if(tempType==NULL){
        return false ; 
    }
//    cout << "setting option for interface: " << tempType->getTypeName() << endl ; 
//    cout << "option name: " << optionName << " option value: " << optionValue << endl ; 

    if(tempType->setLocalOption(optionName,optionValue)){
        if(tempType->setLocalOptionMap(optionName,optionValue) ){
//            cout << "option set" << endl ; 
            return true ; 
        }else{
            cout << "option NOT set" << endl ; 
            return false ; 
        }
    }
    else{
        return false ; 
    }


}





/// If option found, replace, otherwise add it. 
bool AppInterface::setLocalOption(string name,string newValue)
{
    map<string,Option*>::iterator iter ;  
    iter = optionMap->find(name) ; 

    Option* oldOption = (iter->second) ; 

    oldOption->setValue(newValue) ; 
    optionMap->insert(pair<string,Option*> (name,oldOption)) ;
    return true ; 
}

/// Get the names of all the inteface maps.
bool AppInterface::makeMappable(string interface,vector<string> *typeList)  
{
    for(int i = 0 ; i < typeList->size() ; i++){
       addTypeToInterfaceMap(interface,(*typeList)[i]) ;
    }
    return true ; 
}



list<string>* AppInterface::getInterfaceNames() 
{
    if(interfaceMap==NULL){
        return NULL ; 
    }
   list<string>* interfaceNames = new list<string>() ;
   map<string,Interface*>::iterator iter  ; 
   for(iter = interfaceMap->begin() ; iter!=interfaceMap->end() ; iter++){
       interfaceNames->push_back(NameHandler::getInterfaceFromPair(iter->first)) ; 
   }
   interfaceNames->unique() ; 
   return interfaceNames; 
}

list<string>* AppInterface::getTypeNamesForInterface(string theInterfaceName) 
{
   list<string>* typeList = new list<string>();

   map<string,Interface*>::iterator iter  ; 
   for(iter = interfaceMap->begin() ; iter!=interfaceMap->end() ; iter++){
       // apply the filter
//       if(getGroupFromKey(iter->first)==group){
       if(NameHandler::getInterfaceFromPair(iter->first)==theInterfaceName){
           typeList->push_back(NameHandler::getTypeFromPair( ((Interface*) (iter->second))->getInterfaceName() )  ) ;
       }
   }
   typeList->unique() ; 
   return typeList ; 
}









bool AppInterface::disposeMaps(string pathToType)     
{
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
//    cout << "parent: " << tempType->getParent() << endl ; 
    if(tempType==NULL){
        return false ; 
    }
    
	Interface* tempInterface = tempType->getThisInterface() ; 
    tempInterface->unsetTypes() ; 
        return tempType->disposeLocalMaps() ; 
}

Interface* AppInterface::getThisInterface() 
{
    if(isBaseApp()){
        return new Interface("APP",NULL,this) ; 
    }
    else{
        return getParent()->getLocalInterface(getInterfaceName()) ; 
    }
}



bool AppInterface::createMaps(string pathToType)     
{
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
    if(tempType==NULL){
        return false ; 
    }
//    cout << "creating a local map on: " << tempType->getTypeName() << endl ; 
    tempType->disposeLocalMaps() ; 
    return tempType->createLocalMaps() ; 
}


bool AppInterface::setLocalTypeMap(Interface* theInterface,Type *newType)  {

//    cout << "newType: " << newType << endl ; 
//    cout << "theInterface: " << theInterface << endl ; 

    if(interfaceMap==NULL || interfaceMap->size()<1){
        return false ; 
    }
    newType->setParent(this) ; 
    if(theInterface->setType(newType) && theInterface->setParentType(this)) {
        return true ; 
    }
}



bool AppInterface::setType(string pathToType)  
{
     string lastPair = NameHandler::getLastInterfacePair(pathToType) ; 
     string pathToParent = NameHandler::getAllButLastInterfacePair(pathToType) ; 
     string theInterfaceName = NameHandler::getInterfaceFromPair(lastPair) ; 
     string theTypeName = NameHandler::getTypeFromPair(lastPair) ; 

     AppInterface* tempType = NULL ; 

     if(pathToParent==""){
         tempType = this ; 
     }
     else{
         tempType = getTypeForInterface(pathToParent) ;
     }


    if(tempType->setLocalType(theInterfaceName,theTypeName)!=NULL){
//        cout << "local type set, now trying to set map" << endl ; 
        if(tempType->setLocalTypeMap(tempType->getLocalInterface(theInterfaceName),tempType->getTypeForInterface(theInterfaceName)) ){
//            cout << "local map set" << endl ;
        }else{
//            cout << "local map NOT set" << endl ;
        }
        return true ; 
    }else{
        cerr << "failed to set "  << theInterfaceName+"/"+theTypeName << endl ; 
        return false ; 
    }

}


bool AppInterface::setLocalOptionMap(string typeName,string value)  
{
    if(optionMap==NULL || optionMap->size()<1){
        return false ; 
    }

    map<string,Option*>::iterator  optionIterator = optionMap->find(typeName) ; 
    if(  (optionIterator->second)->setValue(value)  == true  ){
        return true ; 
    }else{
        return false ; 
    }
}




bool AppInterface::addTypeToInterfaceMap(string newInterfaceName,string newTypeName) {
    return addTypeToInterfaceMap(newInterfaceName,new Type(newTypeName,this),false) ; 
}

bool AppInterface::addTypeToInterfaceMap(string newInterfaceName,Type* newType,bool setType) 
{

    if(interfaceMap == NULL){
		interfaceMap = new map<string,Interface*>() ; 
    }

    // start with this baby
    // probably need to use "find" here
    map<string,Interface*>::iterator  typeIterator ; 
    typeIterator = interfaceMap->find(newInterfaceName) ; 
    Interface* currentInterface = typeIterator->second ; 

	// if the interface DOES NOT exist, then create a new one
    if(currentInterface==NULL){
        currentInterface = new Interface(newInterfaceName,this) ; 
    }
    
    // add the type to the interface
    currentInterface->addType(newType,setType)  ;  // should still be in the map, right?

    return true ; 
}

bool AppInterface::isInterfaceSet(string pathToType) {
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
    return (tempType!=NULL) ; 
}


AppInterface* AppInterface::getLocalTypeFromInterfaceMap(string newInterfaceName)   
{

    map<string,Interface*>::iterator iter =  interfaceMap->find(newInterfaceName) ; 

    if(iter==interfaceMap->end()){  // interface not found, return NULL
        cerr << "interface not found: " << newInterfaceName << endl ; 
        return NULL ; 
    }

    // returns the set type for the interface or null if not set
    return (AppInterface*) ((Interface*) iter->second)->getType() ; 
}// the name pair


string AppInterface::getOption(string pathToType,string optionName)  
{
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
    if(tempType==NULL){
        return NULL ; 
    }

    return tempType->getLocalOption(optionName) ; 
}

Option* AppInterface::getOptionFromMap(string pathToType,string name)  
{
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
    if(tempType==NULL || tempType->getOptionMap()==NULL ){
        return NULL ; 
    }

    map<string,Option*>::iterator iter =  (tempType->getOptionMap())->find(name) ; 
    if(iter!=tempType->getOptionMap()->end()){
        return iter->second ; 
    }
    else{
        return NULL ; 
    }
}



AppInterface* AppInterface::getTypeForInterface(string pathToType) 
{
//    cout << "typeForInterface: "<< pathToType << endl ; 
    if(pathToType==""){
        return this ; 
    }

    // if more groups exist then search iterate through to the next group

    if(NameHandler::hasSubInterface(pathToType)){
        // an additional interface found, so will need to iterate at least once
        cout << "interface iterator found" << endl ; 
        cout << "found hasParent: " << parent << endl ; 
        return (getLocalTypeForInterface(NameHandler::getFirstInterface(pathToType)))->getTypeForInterface(NameHandler::getAllButFirstInterfacePair(pathToType)) ; 
    }
    // if no more groups exist then just get the type
    else{
//        cout << "NO interface iterator found" << endl ; 
//        cout << "no interface hasParent: " << parent << endl ; 
        return getLocalTypeForInterface(NameHandler::getInterfaceFromPair(pathToType)) ; 
    }
}

bool AppInterface::addCommand(string pathToType, string commandName,Command* newCommand)
{
    AppInterface* theInterface = getTypeForInterface(pathToType) ; 
    if(theInterface==NULL){
        return false ; 
    }
    if(newCommand==NULL){
        newCommand = new Command() ; 
        newCommand->setName(commandName) ; 
    }
    theInterface = theInterface->getLocalTypeForInterface(NameHandler::getLastInterfacePair(pathToType)) ; 
    return theInterface->addCommandToMap(commandName,newCommand) ; 
}



list<string>* AppInterface::getLocalCommandNames()   
{
    list<string>* commandList = new list<string>() ; 
    map<string,Command* >::iterator commandIterator; 
   for(commandIterator = commandMap->begin() ; commandIterator!=commandMap->end() ; commandIterator++){
       commandList->push_back(commandIterator->first) ; 
   }

   return commandList ; 
}


list<string>* AppInterface::getCommandNames(string pathToType)   
{
    AppInterface* localType = getTypeForInterface(pathToType) ; 
    if(localType==NULL){
        return NULL ; 
    }
 
    localType = localType->getLocalTypeForInterface(NameHandler::getLastInterfacePair(pathToType)) ; 
    return localType->getLocalCommandNames() ; 
}



string AppInterface::doLocalCommand(string commandName){
  return doLocalCommand(new Command(commandName)) ; 
}


string AppInterface::doCommand(string pathToType,string theName){
    cout << "trying to do command: " << pathToType << " name: " << theName << endl ; 
    return doCommand(pathToType,new Command(theName)) ; 
}

string AppInterface::doCommand(string pathToType,Command* newCommand)   
{
    AppInterface* tempType = getTypeForInterface(pathToType) ; 
    if(tempType==NULL){
        return NULL ; 
    }
    return tempType->doLocalCommand(newCommand) ; 
}




bool AppInterface::disposeLocalMaps()  
{
    // must clear each interface, as well
    if(interfaceMap!=NULL){
        interfaceMap->clear() ; 
    }
    if(optionMap!=NULL){
        optionMap->clear() ; 
    }
    if(commandMap!=NULL){
        commandMap->clear() ; 
    }

    interfaceMap = NULL ; 
    optionMap = NULL ; 
    commandMap = NULL ; 

    // have the local app dispose itself
    return disposeLocalInterfaces() ; 
}


bool AppInterface::addInterfaceToMap(string newInterfaceName) {
    return addInterfaceToMap(new Interface(newInterfaceName,this)) ; 
}

bool AppInterface::addInterfaceToMap(Interface* newInterface) 
{
    if(interfaceMap == NULL){
		interfaceMap = new map<string,Interface*>() ; 
    }

    map<string,Interface*>::iterator iter =  interfaceMap->find(newInterface->getInterfaceName()) ; 
        
    if(iter!=interfaceMap->end()){  // not found, so insert
        interfaceMap->erase(iter) ; 
    }

    interfaceMap->insert(pair<string,Interface*>(newInterface->getInterfaceName(),newInterface)) ; 

    return true ; 
}

AppInterface* AppInterface::getParent()  
{
    return (AppInterface*) parent ; 
}

string AppInterface::getInterfaceName()  
{
    return interfaceName ; 
}





