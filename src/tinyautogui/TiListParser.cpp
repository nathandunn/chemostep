// -*- C++ -*-
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: TiListParser.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "TiListParser.hpp"

#include "Renderer.hpp" 
#include "Type.hpp"
#include "Option.hpp"
#include "Interface.hpp"
#include "Command.hpp"
#include "NameHandler.hpp"
#include "InterfaceTypes.hpp"
#include <tinyxml.h>


#include <string>
using std::string ; 

#include <vector>
using std::vector ; 

#include <stdio.h>

#include <iostream>
using std::cout ; 
using std::endl ; 


TiListParser::TiListParser(){
}


vector<string>* TiListParser::parseList(string xmlListString,int *selectedValue){

    vector<string>* listVector = new vector<string>() ; 

    TiXmlDocument *doc = new TiXmlDocument() ;
    doc->Parse( xmlListString.c_str()  ) ; 
    if ( doc->Error() )
    {
        printf( "Error in %s: %s\n", doc->Value(), doc->ErrorDesc() );
        throw "PARSE ERROR IN COMMAND" ; 
    }
    TiXmlElement* rootElement = doc->RootElement() ; 
    TiXmlNode* node = (TiXmlNode*) rootElement ; 


    int counter = 0 ; 
    if ( node->Type()== TiXmlNode::ELEMENT && (node->ToElement())->Value() == LIST) {
        node = node->FirstChild() ; 

        while(node!=NULL){
            listVector->push_back( (node->FirstChild())->Value()) ; 
            if( ( (node->Type())==TiXmlNode::ELEMENT )  && ( node->ToElement()) != NULL)
                if(  ( node->ToElement())->Attribute("selected") != NULL ) {
                    if(selectedValue!=NULL){
                        *selectedValue = counter  ; 
                }
            }
            
            node = node->NextSibling() ; 
            ++counter ; 
        }
    }

    return listVector ; 
}

string TiListParser::createList(vector<string>* list,string selectedValue) 
{
    string returnString = "" ; 
    returnString += "<"+TiListParser::LIST+">" ;
    if(list!=NULL){
        for(int i = 0 ; i < list->size() ; i++){
//            returnString += "\t<"+TiListParser::ITEM ;
            returnString += "<"+TiListParser::ITEM ;
            if( (*list)[i]==selectedValue){
                returnString += " "+TiListParser::SELECTED ;
            }
            returnString += ">" ;
            returnString +=  (*list)[i] ; 
            returnString += "</"+TiListParser::ITEM+">" ;
//            returnString += "\n" ; 
        }
    }
    else{
        cout << "fileBox is NULL" << endl ; 
    }
    returnString += "</"+TiListParser::LIST+">" ;


    return returnString ; 
}

string TiListParser::getSelectedValue(string xmlString) 
{

    TiXmlDocument *doc = new TiXmlDocument() ;
    doc->Parse( xmlString.c_str()  ) ; 

    if ( doc->Error() )
    {
        printf( "Error in %s: %s\n", doc->Value(), doc->ErrorDesc() );
        throw "PARSE ERROR IN COMMAND" ; 
    }


    TiXmlElement* rootElement = doc->RootElement() ; 
    TiXmlNode* node = (TiXmlNode*) rootElement ; 


    int counter = 0 ; 
    if ( node->Type()== TiXmlNode::ELEMENT && (node->ToElement())->Value() == LIST) {
        node = node->FirstChild() ; 

        while(node!=NULL){
            if( ( (node->Type())==TiXmlNode::ELEMENT )  && ( node->ToElement()) != NULL){
                if(  ( node->ToElement())->Attribute("selected") != NULL ) {
                    return  (node->FirstChild())->Value() ; 
                }
            }
            
            node = node->NextSibling() ; 
            ++counter ; 
        }
    }

    return xmlString  ; 
}




const string TiListParser::LIST = "list" ; 
const string TiListParser::ITEM = "item" ; 
const string TiListParser::SELECTED = "selected='true'" ; 



