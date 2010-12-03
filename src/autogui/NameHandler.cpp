// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>

#include "NameHandler.hpp"


string NameHandler::getInterfaceFromPair(string pairString) 
{
    int index ; 
    index = pairString.find(TYPE_DELIMITER) ; 
    if(index>=0){
		return  pairString.substr(0,index) ; 
    }
    else{
        return pairString ; 
    }
}


string NameHandler::getTypeFromPair(string pairString) 
{
    int index ; 
    index = pairString.find(TYPE_DELIMITER) ; 
    if(index>=0){
		return  pairString.substr(index+1,pairString.size()-1) ; 
    }
    else{
        return pairString ; 
    }
}


string NameHandler::getLastInterfacePair(string fullPath) 
{
    int index = fullPath.find(INTERFACE_DELIMITER) ;
    if(index!=string::npos) 
    {
            return getLastInterfacePair(fullPath.substr(index+1,fullPath.size()-1)) ; 
    }
    else
    {
        return fullPath ; 
    }
}

string NameHandler::getAllButLastInterfacePair(string fullPath)  
{
    int index = fullPath.find(INTERFACE_DELIMITER) ;
    if(index!=string::npos) 
    {
            return fullPath.substr(0,index) ; 
    }
    else
    {
        return "" ; 
    }
}

string NameHandler::getFirstInterface(string pathToType)  
{
    string returnString = getFirstInterfacePair(pathToType) ; 
    returnString = getInterfaceFromPair(returnString) ; 
    return returnString ; 
}


bool NameHandler::lastPairHasType(string pathToType)  
{
    return pairHasType(getLastInterfacePair(pathToType)) ; 
}

bool NameHandler::firstPairHasType(string pathToType)  
{
    return pairHasType(getFirstInterfacePair(pathToType)) ; 
}

bool NameHandler::pairHasType(string pairName){
    int typeIndex =  pairName.find(NameHandler::TYPE_DELIMITER) ;
    // not found
    if(typeIndex==string::npos){
        return false ; 
    }
    // found
    else{
        return true ; 
    }
}

bool NameHandler::hasSubInterface(string pathToType){
    int typeIndex =  pathToType.find(NameHandler::INTERFACE_DELIMITER) ;
    // not found so remaining interface
    if(typeIndex==string::npos){
        return false ; 
    }
    else{
        return true ; 
    }
}

string NameHandler::getFirstType(string pathToType)  
{
    return getTypeFromPair(getFirstInterfacePair(pathToType)); 
}

string NameHandler::getAllButFirstInterfacePair(string pathToType)  
{
    string returnString ; 
	int interfaceIndex =  pathToType.find(NameHandler::INTERFACE_DELIMITER) ;

    // found
    if(interfaceIndex!=string::npos){
        return pathToType.substr(interfaceIndex+1,pathToType.size()-1) ; 
    }
    else{
        // must pluck it off
        return "" ; 
    }
}


string NameHandler::getFirstInterfacePair(string pathToType)  
{
	int interfaceIndex =  pathToType.find(NameHandler::INTERFACE_DELIMITER) ;

    // found
    if(interfaceIndex!=string::npos){
        return pathToType.substr(0,interfaceIndex) ; 
    }
    else{
        // must pluck it off
        return pathToType ; 
    }
}

string NameHandler::getLastInterface(string pathName)  
{
   return   getInterfaceFromPair(getLastInterfacePair(pathName)) ; 
}

string NameHandler::getNameFromPath(string pathToType)  
{
    int index = pathToType.find(NAME_DELIMITER) ; 
    if(index!=string::npos) // found 
    {
        return pathToType.substr(index+1,pathToType.size()-1) ; 
    }
    else{
        return "" ; 
    }
}

string NameHandler::getAllButNameFromPath(string pathToType)  
{
    int index = pathToType.find(NAME_DELIMITER) ; 
    if(index!=string::npos) // found 
    {
        return pathToType.substr(0,index) ; 
    }
    else{
        return pathToType ; 
    }
}


const string NameHandler::INTERFACE_DELIMITER = "."  ; 
const string NameHandler::TYPE_DELIMITER= "/"  ; 
const string NameHandler::NAME_DELIMITER  = ":" ; 


