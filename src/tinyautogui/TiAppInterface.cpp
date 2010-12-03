/*
 * $Id$
 */

#include <iostream>
using std::cout ; 
using std::endl ; 


#include <map>
using std::map ; 
#include <vector>
using std::vector ; 
#include <string>
using std::string ; 

#include <InterfaceXmlString.hpp>
#include <Option.hpp>
#include <Command.hpp>
#include "TiListParser.hpp"

#include "TiAppInterface.hpp"


TiAppInterface::TiAppInterface(string interfaceName,string typeName,AppInterface* parent)  : AppInterface(interfaceName,typeName,parent)
{
}

/// Here, we want to automatically look this up, if possible. :
string TiAppInterface::doLocalCommand(Command *theCommand) {

   // get command from map 
    cout << "TiAppInterface local commandMap: " << commandMap << endl ; 
    cout << "TiAppInterface local commandMap->size(): " << commandMap->size() << endl ; 

    string name = theCommand->getName() ; 

    Command* tempCommand = NULL ; 
    map<string,Command*>::iterator commandIter = commandMap->find(name)  ; 
    char buffer[20]  ; 
    if(commandIter != commandMap->end()){
        cout << "CONTAINS: " << name << endl ; 
        tempCommand = commandIter->second ; 
        if(tempCommand->getRef()!=NULL){
            cout << "ref is not NULL for: " << name << endl ; 
            (tempCommand->getRef()) ; 
        }else{
          cout << "no ref for command: " << name << endl ; 
        }
    }
    else{
        cout << "failed to find the command: " << name << endl ; 
    }

    return InterfaceXmlString::COMMANDSTATUS_FAILURE; 
}

string TiAppInterface::getLocalOption(string name) 
{
//    cout << "TiAppInterface local optionMap: " << optionMap << endl ; 
//    cout << "TiAppInterface local optionMap->size(): " << optionMap->size() << endl ; 

    Option* tempOption = NULL ; 
    map<string,Option*>::iterator optionIter = optionMap->find(name)  ; 
    char buffer[20]  ; 
    if(optionIter != optionMap->end()){
//        cout << "CONTAINS: " << name << endl ; 
        tempOption = optionIter->second ; 
        if(tempOption->getRef()!=NULL){
//            cout << "ref is not NULL for: " << name << endl ; 
            if(tempOption->getType()==OPT_DOUBLE){
//                cout << "trying to set double option for: " << name << endl ; 
                sprintf(buffer,"%f",*((double*)tempOption->getRef())) ; 
            }
            else
            if(tempOption->getType()==OPT_INT){
//                cout << "trying to set int option for: " << name << endl ; 
                sprintf(buffer,"%f",*((int*)tempOption->getRef())) ; 
            }
            else
            if(
                tempOption->getType()==LIST_TYPE || 
                tempOption->getType()==OPT_STRING  || 
                tempOption->getType()==OPT_FILE_SAVE || 
                tempOption->getType()==OPT_FILE_LOAD  
                ){
//                cout << "trying to set string option for: " << name << endl ; 
                sprintf(buffer,"%f",(*((string*)tempOption->getRef())).c_str()) ; 
            }
            else
            if(tempOption->getType()==OPT_BOOL){
//                cout << "trying to get bool option for: " << name << endl ; 
                if(*((bool*)tempOption->getRef()) == true){
                    return OPT_BOOL_TRUE ; 
                }
                else{
                    return OPT_BOOL_FALSE; 
                }
            /// Don't need to handle these yet,but we would just use TiListParser, to parse them up again
            }else{
                cout << "type not specified: " << tempOption->getType() << endl; 
                return NULL ; 
            }
            return buffer ; 
        } // if ref not null
    }else{  // option name is not in map
        cout << "does not contain: " << name << endl ; 
        return NULL ;
    }
    
}

bool TiAppInterface::setLocalOption(string name, string value) 
{
//    cout << "AppInterface set local optionMap: " << optionMap << endl ; 
//    cout << "AppInterface set local optionMap->size(): " << optionMap->size() << endl ; 

    Option* tempOption = NULL ; 
    map<string,Option*>::iterator optionIter = optionMap->find(name)  ; 
    if(optionIter != optionMap->end()){
//        cout << "CONTAINS: " << name << endl ; 
        tempOption = optionIter->second ; 
        if(tempOption->getRef()!=NULL){
//            cout << "ref is not NULL for: " << name << endl ; 
            if(tempOption->getType()==OPT_DOUBLE){
//                cout << "trying to set double option for: " << name << endl ; 
                    *((double*)tempOption->getRef()) = atof(value.c_str()) ; 
                    return true ; 
            }
            else
            if(tempOption->getType()==OPT_INT){
//                cout << "trying to set int option for: " << name << endl ; 
                    *((int*)tempOption->getRef()) = atoi(value.c_str()) ; 
                    return true ; 
            }
            else
            if( tempOption->getType()==OPT_STRING  || 
                tempOption->getType()==OPT_FILE_SAVE || 
                tempOption->getType()==OPT_FILE_LOAD  
                ){
//                cout << "trying to set string option for: " << name << endl ; 
                    *((string*)tempOption->getRef()) = value ; 
                    return true ; 
            }
            else
            if(tempOption->getType()==OPT_BOOL){
//                cout << "trying to set bool option for: " << name << " to: " << value << endl ; 
//                cout << "OPT_BOOL_TRUE: " << OPT_BOOL_TRUE << endl ; 
//                cout << "OPT_BOOL_FALSE: " << OPT_BOOL_FALSE << endl ; 
                if(value==OPT_BOOL_TRUE){
//                    cout << "in true" << endl ; 
                    *((bool*)tempOption->getRef()) = true ; 
                    return true ; 
                }
                else {
//                    cout << "in false" << endl ; 
                    *((bool*)tempOption->getRef()) = false ; 
                    return true ; 
                }
            }
            else
            if( tempOption->getType()==LIST_TYPE){
                *((string*)tempOption->getRef())= TiListParser::getSelectedValue(value) ; 
            }
            else
            if(tempOption->getType()==LIST_FILE_LOAD || 
                tempOption->getType() == LIST_FILE_SAVE ){
//                cout << "LIST_FILE_LOAD: trying to get the ref from a value: " << value << endl ;  
                *((vector<string>**)tempOption->getRef())= (new TiListParser())->parseList(value) ; 
            }
            else{
                cout << "type not specified: " << tempOption->getType() << endl; 
                return false ;  
            }
        }
    }else{
        cout << "does not contain: " << name << endl ; 
        return false ;
    }

    return true ; 
}

/* Function int main(int argc, char **argv) {{{ */
//int main(int argc, char **argv)
//{


//    return 0;
//} /* }}} */


/* Modeline for ViM {{{
 * vim:set ts=4:
 * vim600:fdm=marker fdl=0 fdc=3:
 * }}} */

// -*- C++ -*-
// (C) 2004 by Nathan Dunn, <ndunn@mac.com>
// $Id:$

