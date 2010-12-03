// -*- C++ -*-
// FILE: "/Users/ndunn/tlalocal/auto3--localdev--1.3.3--base-0/src/autogui/Command.hpp"
// LAST MODIFICATION: "Thu, 18 Mar 2004 19:57:56 -0800 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: Command.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

/**
 *  An abstraction of class methods exposed to the client. 
 *
 */

#ifndef _COMMAND_HPP_
#define _COMMAND_HPP_

#include "CommandArgumentField.hpp"

#include <string>
#include <iostream>
#include <map>



class Command{

public:
    Command(string newName="",void* newCommand=NULL,string newType="",string newId="") ; 
    virtual bool addCommandArgument(string argName,string argType,string value="",string valueFromOption="",bool set=false) ; 
    virtual bool addCommandArgument(CommandArgumentField* newCommandArgumentField) ; 
    virtual map<string,CommandArgumentField*> *getArguments() ; 
    virtual string getArgumentName(int number) ; // count starts at 0
    virtual string getArgumentByName(string name) ; // accessor for the server
    virtual string getArgumentType(int number) ; // count starts at 0
    virtual CommandArgumentField *getField(int number) ; // count starts at 0
    virtual int numArgs() ; 
    // {{{
    /*!
     * \brief	Get name.
     *
     * \return	name as a string.
     */ // }}}
    string getName()
    {
        return(mName);
    }
    // {{{
    /*!
     * \brief	Set name.
     *
     * \param	_name	The new value for name (as a string).
     */ // }}}
    void setName(string _name)
    {
        mName = _name;
        return;
    }

    // {{{
    /*!
     * \brief	Get type.
     *
     * \return	type as a string.
     */ // }}}
    string getType()
    {
        return(mType);
    }
    // {{{
    /*!
     * \brief	Set type.
     *
     * \param	_type	The new value for type (as a string).
     */ // }}}
    void setType(string _type)
    {
        mType = _type;
        return;
    }
  
    void setId(string newId){
        mId = newId ; 
    }

    string getId(){
        return mId ; 
    }


    void* getRef() {
        return(mCommandRef);
    }
    void setRef(void* newCommand ) {
        mCommandRef= newCommand ;
        return;
    }




protected:
	string mName ; 
	void* mCommandRef ; 
	string mType ; 
	string mId ; 
    map<string,CommandArgumentField*> *mArgs ; 
    
} ;

#endif


