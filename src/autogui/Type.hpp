// -*- C++ -*-

/**
 *  \brief  An instantiated instance of an Interface. 
 *
 *  All AppInterface classes are fully instantiated Type's.  However,
 *  in the Renderer class, a naming schema is needed to hold Type data.
 *
 *
 */

#ifndef TYPE_HPP_
#define TYPE_HPP_

class Option ; 
class Command ; 
class Interface ; 

#include <map>
using std::map ; 
using std::pair ; 

#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include<iostream>
using std::cout ; 
using std::cerr ; 
using std::endl ; 



class Type  {

public:
    Type(string newName,Type* parentType=NULL,string newInterfaceName="") ; 
    virtual string getTypeName() ; 
    virtual bool isRootType() ; 
    virtual Type* getParent() ; 
    virtual Type* setParent(Type* newParentType) ; 
    virtual map<string,Option*> *getOptionMap()  ;    /// returns name and type of option
    virtual map<string,Command*>* getCommandMap()  ;    /// gets available commands 
    virtual map<string,Interface*>* getInterfaceMap() ; 
    virtual bool addOptionToMap(Option *newOption)  ; /// adds NULLtype as key
    virtual bool addOptionToMap(string optionName,string optionType,void* reference=NULL,string newPath="",string optionLabel="",string optionValue="",bool isSet=false)  ; 
    virtual bool addCommandToMap(string commandKey,void* setRef=NULL,Command *newCommand=NULL)  ;    /// gets available commands 
    virtual bool addCommandToMap(Command *newCommand)  ;    /// gets available commands 
    virtual string getDescription()  ;
    virtual void setDescription(string newDescription)  ;
    virtual string getInterfaceName() ; 

protected:
    string typeName ; 
    Type* parent ; 
    map<string,Option*> *optionMap ; 
    map<string,Command*> *commandMap ;  /// the return type is specified 
    map<string,Interface*> *interfaceMap ;  /// <interface/type.interface/type>
    string description ; 
    string interfaceName ; 

} ; 

#endif
