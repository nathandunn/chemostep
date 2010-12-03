// -*- C++ -*-
// FILE: "/Users/ndunn/tlalocal/auto3--localdev--1.3.3--base-0/src/autogui/Command.cpp"
// LAST MODIFICATION: "Thu, 18 Mar 2004 19:43:18 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: Command.cpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#include "Command.hpp" 

Command::Command(string newName,void* newCommand,string newType,string newId) {
    mName = newName ; 
    mType = newType ; 
    mId = newId ; 
    mArgs = NULL ; 
}

bool Command::addCommandArgument(CommandArgumentField* newCommandArgumentField) 
{
    if(mArgs==NULL){
       mArgs= new map<string,CommandArgumentField*>() ;
    }
    cout << "pre arg size: "<< mArgs->size()  << endl ;  
    cout << "adding for: "<< newCommandArgumentField->getName()  << endl ;  
    mArgs->insert(pair<string,CommandArgumentField*> (newCommandArgumentField->getName(),newCommandArgumentField)) ; 
    cout << "inserted arg: "<< mArgs->size() << " for cmd: "<< getName() << endl ;  
    return true ; 
}

map<string,CommandArgumentField*> *Command::getArguments() {
    if(mArgs==NULL) {
        return NULL ; 
    }else{
        return mArgs ; 
    }
}

string Command::getArgumentName(int number) 
{
    if(mArgs==NULL || mArgs->size()==0 || number > mArgs->size()){
       return NULL ; 
    }
        
    map<string,CommandArgumentField*>::iterator argumentIterator = mArgs->begin() ; 
    int counter = 0 ; 
    string argumentName = "" ; 
        
    while(counter <= number){
        argumentName = argumentIterator->first ; 
        
        ++counter ; 
        ++argumentIterator ; 
    }
        
    return argumentName ; 
}

int Command::numArgs() 
{
    if(mArgs==NULL){
        return 0 ; 
    }
    else {
        return mArgs->size() ; 
    }
}

CommandArgumentField *Command::getField(int number) { // count starts at 0
    if(mArgs==NULL || mArgs->size()==0 || number > mArgs->size()){
       return NULL ; 
    }
    map<string,CommandArgumentField*>::iterator argumentIterator = mArgs->begin() ; 
    int counter = 0 ; 
    while(counter < number){
        ++counter ; 
        ++argumentIterator ; 
    }
    return  ( (CommandArgumentField*) argumentIterator->second) ; 
}

string Command::getArgumentByName(string thisName) {
    cout << "getting for thisName: " << thisName << endl ;  
    cout << "mArgs: "<< mArgs << endl ; 
//    cout << "args->size: "<< args->size() << endl ; 
    if(mArgs==NULL || mArgs->size()==0 ){
       return NULL ; 
    }
    map<string,CommandArgumentField*>::iterator argumentIterator = mArgs->begin() ; 
    for(  ; argumentIterator != mArgs->end() ; argumentIterator++){
        cout << "thisName: "<< thisName << " versus " << argumentIterator->first << endl ;
        if(argumentIterator->first==thisName){
            return  ( (CommandArgumentField*) argumentIterator->second)->getValue() ; 
        }
    }
    return NULL ; 
}


string Command::getArgumentType(int number) 
{
    if(mArgs==NULL || mArgs->size()==0 || number > mArgs->size()){
       return NULL ; 
    }
    map<string,CommandArgumentField*>::iterator argumentIterator = mArgs->begin() ; 
    int counter = 0 ; 
    string argumentType = "" ; 
    while(counter <= number){
        argumentType = ( (CommandArgumentField*) argumentIterator->second)->getType() ; 
        ++counter ; 
        ++argumentIterator ; 
    }
    return argumentType ; 
}


bool Command::addCommandArgument(string argName,string argType,string value,string valueFromOption,bool set) 
{
   return addCommandArgument(new CommandArgumentField(argName,argType,value,valueFromOption,set) ) ; 
}






