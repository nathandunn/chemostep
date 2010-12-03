// -*- C++ -*-
// FILE: "/Users/ndunn/cvs/AUTOGUI_1/source/appinterface/Interface.cpp"
// LAST MODIFICATION: "Thu, 18 Sep 2003 13:03:42 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: Interface.cpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#include "Interface.hpp" 

#include "Type.hpp" 


Interface::Interface(const Interface& oldInterface) : 
parentType(((Interface) oldInterface).getParentType()),
theSetType(((Interface)oldInterface).getType()),
interfaceName(((Interface)oldInterface).getInterfaceName()),
typeList(((Interface)oldInterface).getTypes())
{ }


Interface::Interface(string newInterface,Type* newParentType,Type* newSetType) :
interfaceName(newInterface) , 
parentType(newParentType) , 
theSetType(newSetType) ,
typeList(new map<string,Type*>())
{
}

Interface Interface::operator=(const Interface& rhs) 
{
    parentType = ((Interface) rhs).getParentType() ; 
    theSetType = ((Interface) rhs).getType() ; 
    interfaceName = ((Interface) rhs).getInterfaceName() ; 
    typeList = ((Interface) rhs).getTypes() ; 
    return *this ; 
}


bool Interface::isSet() 
{
    return (theSetType!=NULL) ; 
}


map<string,Type*>* Interface::getTypes() 
{
    return typeList ; 
}

string Interface::getTypeName() 
{
    if(theSetType==NULL) { 
        return "" ; 
    }
    else{
        return (theSetType)->getTypeName() ; 
    }
}

list<string>* Interface::getUnsetTypeNames() 
{
    list<string>* unsetTypeNames = new list<string>() ;
   map<string,Type*>::iterator iter  ; 
   for(iter = typeList->begin() ; iter!=typeList->end() ; iter++){
       if(iter->first!=getTypeName()){
           unsetTypeNames->push_back(iter->first) ; 
       }
   }
   unsetTypeNames->unique() ; 
    return unsetTypeNames ;


}


list<string>* Interface::getTypeNames() 
{
    list<string> *typeNames = new list<string>() ; 
   map<string,Type*>::iterator iter  ; 
   for(iter = typeList->begin() ; iter!=typeList->end() ; iter++){
       typeNames->push_back(iter->first) ; 
   }
   typeNames->unique() ; 
    return typeNames ;
}

Type* Interface::getType() 
{
    return theSetType; 
}  // returns the set type, or NULL if none are set

bool Interface::setType(Type* thisType) 
{
    theSetType = thisType ; 
    return true ;
}// returns the set type, or NULL if none are set

Type* Interface::getParentType() 
{
    return parentType ; 
}// returns the set type, or NULL if none are set

bool Interface::setParentType(Type* newParentType) 
{
    parentType = newParentType ; 
    return true ; 
}// returns the set type, or NULL if none are set


string Interface::getInterfaceName() 
{
    return interfaceName ; 
}

Type* Interface::addType(Type* newType,bool setThisType) 
{
    if(newType==NULL) return NULL ; 

    typeList->insert(pair<string,Type*>(newType->getTypeName(),newType)) ; 
    if(setThisType==true){
        theSetType = newType ; 
    }
    return newType ; 
}

Type* Interface::addType(string newTypeKey,Type* parentType) 
{
   addType(new Type(newTypeKey,parentType)) ; 
}

bool Interface::clearTypes() 
{
    unsetTypes() ; 
    typeList->clear() ; 
    return typeList->empty() ; 
}

bool Interface::unsetTypes(){
    theSetType = NULL ; 
    return true ; 
}



