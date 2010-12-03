// -*- C++ -*-

#ifndef TINYAPPINTERFACEXMLENGINE_HPP_
#define TINYAPPINTERFACEXMLENGINE_HPP_

#include "AppInterfaceXmlEngine.hpp"  

class TiXmlNode ; 

class TinyAppInterfaceXmlEngine : public AppInterfaceXmlEngine{

public:
    TinyAppInterfaceXmlEngine(AppInterface* appInterface=NULL)  ;  // generates a string map representation
    virtual string toXml(AppInterface* appInterface=NULL)  ;  // generates a string map representation
    virtual string doXmlCommand(string xmlString,AppInterface* appInterface=NULL)  ;    // applies an xml string to its API

protected:
    virtual string getOptionsAsXml()  ;  // generates a string map representation
    virtual string getCommandsAsXml()  ;  // generates a string map representation
    virtual string getInterfacesAsXml()  ;  // generates a string map representation
    virtual string optionToXml(Option* newOption)  ;  // generates a string map representation

    // to the xml commands
    virtual string doCommand(TiXmlNode* executionNode)  ;  // generates a string map representation
    virtual string getOption(TiXmlNode* executionNode)  ;  // generates a string map representation
    virtual string setOption(TiXmlNode* executionNode)  ;  // generates a string map representation
    virtual string setType(TiXmlNode* executionNode)  ;  // generates a string map representation
    virtual string createMaps(TiXmlNode* executionNode)  ;  // generates a string map representation
    virtual string disposeMaps(TiXmlNode* executionNode)  ;  // generates a string map representation
    virtual string displayMessage(TiXmlNode* executionNode)  ;  // generates a string map representation




} ;



#endif



