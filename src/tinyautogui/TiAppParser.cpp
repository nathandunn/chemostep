// -*- C++ -*-

#include "TiAppParser.hpp"

#include "Renderer.hpp" 
#include "Type.hpp"
#include "Option.hpp"
#include "Interface.hpp"
#include "Command.hpp"
#include "NameHandler.hpp"
#include "InterfaceTypes.hpp"
#include <tinyxml.h>

#include <vector>
using std::vector ; 

#include <stdio.h>

#include <iostream>
using std::cout ; 
using std::endl ; 


TiAppParser::TiAppParser(Renderer* newRenderer){
    if(newRenderer!=NULL){
      thisRenderer = newRenderer ; 
    }
}

string TiAppParser::parse(Renderer* newRenderer,string xmlString) 
{
    thisRenderer = newRenderer ; 
    thisXml = xmlString ; 

    cout << "trying to parse: " << thisXml << endl ;

    // generate types and then call addGuiType for each one

    TiXmlDocument *doc = new TiXmlDocument() ;
    doc->Parse( thisXml.c_str()  ) ; 
    if ( doc->Error() )
    {
        printf( "Error in %s: %s\n", doc->Value(), doc->ErrorDesc() );
        throw "PARSE ERROR IN COMMAND" ; 
    }
    TiXmlElement* rootElement = doc->RootElement() ; 
    if(parseElement(rootElement,NULL,"APP")){
        cout << "parsed successfully" << endl ; 
    }else{
        cout << "a bug dude" << endl ; 
    }

    return "" ; 
}



bool TiAppParser::parseElement(TiXmlElement* theElement,Type* parentType,string interfacePath) 
{
    // assume a root type, 
    // 1. create a type at this level
    // 2.   find the interfaces
    // 3.   call parseElement for each element whose name is type (for each interface)
   
    TiXmlNode* node = (TiXmlNode*) theElement ; 
    TiXmlNode* childNode = NULL ; 
    TiXmlNode* childChildNode = NULL ; 

//    cout << "U nodeValue: " << (node->ToElement())->Value() << endl ; 

    // do a depth-first sweep, but only breadth and this level ?!?
    if ( node->Type()== TiXmlNode::ELEMENT && (node->ToElement())->Value() == COMMAND_TYPE ) {
        string nodeName = (node->ToElement())->Attribute("name") ; 
        Type* newType = NULL ; 
        newType = new Type(nodeName,parentType,NameHandler::getLastInterface(interfacePath)) ; 

        childNode = node->FirstChild("description") ; 
        childChildNode = childNode->FirstChild() ; 
        if(childChildNode->Type()==TiXmlNode::TEXT){
            newType->setDescription(childChildNode->Value()) ; 
        }

//        // addOptionToMap   // for all options
        childNode = node->FirstChild("options") ; 
        childChildNode = childNode->FirstChild() ; 
        while(childChildNode!=NULL && childChildNode->Type()==TiXmlNode::ELEMENT ){
            newType->addOptionToMap(new Option((childChildNode->ToElement())->Attribute("name"),(childChildNode->ToElement())->Attribute("type"),NULL,interfacePath+"/"+newType->getTypeName(),  (childChildNode->ToElement())->Attribute("label"),(childChildNode->ToElement())->Attribute("value"),true  )   ) ;
            childChildNode = childChildNode->NextSibling() ; 
        }

//
//        // addCommandToMap // for all commands
        childNode = node->FirstChild("commands") ; 
        childChildNode = childNode->FirstChild() ; 
        while(childChildNode!=NULL && childChildNode->Type()==TiXmlNode::ELEMENT){
            newType->addCommandToMap(new Command((childChildNode->ToElement())->Attribute("name"),NULL,(childChildNode->ToElement())->Attribute("type") )   ) ;
            childChildNode = childChildNode->NextSibling() ; 
        }
        thisRenderer->addGuiType(interfacePath+"/"+newType->getTypeName(),newType) ; 

//        // get the interfaces
        childNode = node->FirstChild("interfaces") ; 
        childChildNode = childNode->FirstChild() ; 
//        // if node hasChildren, process each interface

        while(childChildNode!=NULL && childChildNode->Type()==TiXmlNode::ELEMENT ){
            // for each interface, if interface is set get set type
                string interfaceName =  (childChildNode->ToElement())->Attribute("name") ;
            if((childChildNode->ToElement())->Attribute("set")==InterfaceTypes::OPT_BOOL_TRUE) {
                string setType =  (childChildNode->ToElement())->Attribute("settype")  ; 
                TiXmlNode* typeNode = childChildNode->FirstChild() ; 
                // process each type for the set type
                while(typeNode!=NULL){
                    if( (typeNode->ToElement())->Attribute("name")==setType){
                        parseElement(typeNode->ToElement(),newType,interfacePath+"."+interfaceName) ; 
                        typeNode = NULL ; 
                    }
                    else{
                        typeNode = typeNode->NextSibling() ; 
                    }
                }
            }
            childChildNode = childChildNode->NextSibling() ; 
        }
    }


    return true ; 
}





