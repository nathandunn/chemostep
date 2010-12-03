

#ifndef APP_INTERFACE_HPP_
#define APP_INTERFACE_HPP_



#include <string>
using std::string ; 

#include<iostream>
using std::cout ; 
using std::cerr ; 
using std::endl ; 

#include <list>
using std::list ; 

#include <vector>
using std::vector ; 

#include <map>
using std::map ; 
using std::pair ; 


#include "Type.hpp"
#include "InterfaceXmlString.hpp"


class CommandArgumentField ; 
class Command ; 
class Option ; 
class InterfaceTypes ; 
class Interface ; 


/**
\brief  Base GUI class.  
The abstract base class which classes that whish to make observeable to the user (via a GUI) must extend.  AppInterface's are set Types.  Local methods still need to be provided in order to connect the Options to normal class fields (text, double, int, etc), the Interfaces to custom class field names (which also extend AppInterface), and Commands to class functions.  
*/

class AppInterface :  public Type  {

public:
    AppInterface(string interfaceName,string typeName,AppInterface* parent=0)  ;  /// creates the map here instead of constructure
//    AppInterface()  ;  // creates the map here instead of constructure
    ~AppInterface()  ;  /// destroys the maps asdf
    AppInterface* operator=(AppInterface* rhs)  ;  // creates the map here instead of constructure
    // mapper interface options
    // *********************************
    //   Create/dispose local maps
    // *********************************
    virtual bool createMaps(string pathToType)  ;  /// creates the map here instead of constructure
    virtual bool createLocalMaps() = 0 ;  /// creates the map here instead of constructure
    virtual bool disposeMaps(string pathToType)  ;  /// creates the map here instead of constructure
    virtual bool disposeLocalInterfaces() = 0 ;  /// deletes the map here instead of constructure
    virtual bool disposeLocalMaps()  ;  /// deletes the map here instead of constructure
    virtual bool makeMappable(string interface,vector<string> *typeList)  ;

    // *********************************
    //   Set/Get options
    // *********************************
    virtual bool setOption(string pathToType, string name,string value)  ; /// sets name and value of option, supporting embedded groups
    virtual bool setLocalOption(string typeName,string value) = 0 ; /// sets name and value of option
    virtual bool setLocalOptionMap(string typeName,string value)  ; /// sets name and value of option
    virtual string getOption(string pathToType,string name)  ;    /// returns name and type of option
    virtual string getLocalOption(string typeName) = 0 ;    /// returns name and type of option
    virtual Option* getOptionFromMap(string pathToType,string name)  ;    /// returns name and type of option
//    virtual bool addOptionToMap(string optionKey,Option *newOption) = 0 


    // *********************************
    //   Set/Get commands
    // *********************************
    virtual string doCommand(string pathToType,string commandName)  ;    /// processes a command not in the optionInterface API
    virtual string doCommand(string pathToType,Command* theCommand)  ;    /// processes a command not in the optionInterface API
    virtual string doLocalCommand(Command* theCommand) = 0 ;    /// processes a command not in the optionInterface API
    virtual string doLocalCommand(string commandName)  ;    /// processes a command not in the optionInterface API
    virtual bool addCommand(string pathToType,string commandKey,Command *newCommand=NULL)  ;    /// gets available commands 
    virtual list<string>* getCommandNames(string pathToType)  ;    /// gets available commands 
    virtual list<string>* getLocalCommandNames()  ;    /// gets available commands 
   

    // *********************************
    //   Set/Get interface/types
    // *********************************
    virtual bool setLocalTypeMap(Interface* newInterface,Type* newType)  ; /// sets the map flags?  *DELETE?*
    virtual bool setType(string pathToType)  ; /// sets type for the interface, iterating to the path and setting the named interface for the named type
    virtual AppInterface* setLocalType(string theInterfaceName,string theTypeName)=0  ; /// sets name and value of option
    virtual AppInterface* getLocalTypeForInterface(string theInterfaceName) = 0  ; /// accepts int.int.int (where it grabs the approriate link) or int/type.int/type
//    virtual AppInterface* getLocalNameForInterface(string interfaceName) = 0  ; // accepts int.int.int (where it grabs the approriate link) or int/type.int/type
    virtual AppInterface* getLocalTypeFromInterfaceMap(string interfaceName)   ; /// accepts int.int.int (where it grabs the approriate link) or int/type.int/type
    virtual bool isInterfaceSet(string pathToType)   ; /// checks to see if its set
    virtual AppInterface* getTypeForInterface(string pathToType)  ;
    virtual list<string>* getInterfaceNames() ; 
    virtual Interface* getLocalInterface(string theInterfaceName) ; 
    virtual Interface* getThisInterface() ; 
    virtual bool addInterfaceToMap(Interface* newInterface) ; 
    virtual bool addInterfaceToMap(string newInterfaceName) ; 
    virtual bool addTypeToInterfaceMap(string newInterfaceName,string newTypeName) ;
    virtual bool addTypeToInterfaceMap(string newInterfaceName,Type* newType,bool setType=false) ;



    // *********************************
    //   Group Accessor methods
    // *********************************
    virtual list<string>* getTypeNamesForInterface(string interfaceName)  ; 
    virtual bool setInterfaceName(string newInterfaceName ){ interfaceName = newInterfaceName ; }
    virtual string getInterfaceName()  ;  
    virtual AppInterface* getParent()  ;
    virtual bool isBaseApp(){ return (parent==NULL) ;  }
   
} ; 

#endif
