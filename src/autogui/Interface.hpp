// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/auto2/AUTOGUI_2/source/Interface.hpp"
// LAST MODIFICATION: "Tue, 21 Oct 2003 14:16:53 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: Interface.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#ifndef INTERFACE_HPP_
#define INTERFACE_HPP_

#include <string>
using std::string ; 

#include<iostream>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include <list>
using std::list ; 

#include <map>
using std::map ; 
using std::pair ; 

class Type; 

class Interface{

public:
    Interface(const Interface&) ; 
    Interface(string interfaceName,Type* parentType=NULL,Type* setType=NULL) ; 
    Interface operator=(const Interface& rhs) ; 
    bool isSet() ; 
    map<string,Type*>* getTypes() ;  /// return NULL if not set
    list<string>* getTypeNames() ;  /// returns key strings for types
    list<string>* getUnsetTypeNames() ;  /// returns key strings for types
    Type* getType() ;  /// returns the set type, or NULL if none are set
    Type* getParentType() ;  /// returns the set type, or NULL if none are set
    bool setParentType(Type* newParentType) ;  /// returns the set type, or NULL if none are set
    string getTypeName() ;  /// returns the set type name, or "" if none are set
    bool setType(Type* thisType) ;  /// returns the set type, or NULL if none are set
    string getInterfaceName() ;  /// returns the interfaceName
    Type* addType(Type* newType,bool setThisType=false) ; 
    Type* addType(string newTypeKey,Type* parentType=NULL) ; 
    bool clearTypes() ; 
    bool unsetTypes() ; 
    


protected:
    string interfaceName ; 
    Type* parentType ; 
    Type* theSetType ; 
    map<string,Type*> *typeList ;  /// return NULL if not set


} ; 



#endif


