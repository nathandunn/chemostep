// -*- C++ -*-
// FILE: "/Users/nathandunn/cvs/AUTOGUI_1/source/appinterface/CommandArgumentField.hpp"
// LAST MODIFICATION: "Tue, 16 Sep 2003 18:07:26 -0700 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@idiom.com>
// $Id: CommandArgumentField.hpp,v 1.1.1.1 2003/10/24 19:59:22 ndunn Exp $

#ifndef _COMMANDARGUMENTFIELD_HPP_
#define _COMMANDARGUMENTFIELD_HPP_



#include "InterfaceTypes.hpp"


#include <string>
using namespace std ; 

class CommandArgumentField: public InterfaceTypes{

public:
    CommandArgumentField(string argName,string argType,string value="",string valueFromOption="",bool set=false) ; 
    CommandArgumentField() ; 

    // {{{
    /*!
     * \brief	Get valueFromOption.
     *
     * \return	valueFromOption as a string.
     */ // }}}
    string getValueFromOption() {
        return(valueFromOption);
    }
    // {{{
    /*!
     * \brief	Set valueFromOption.
     *
     * \param	_valueFromOption	The new value for valueFromOption (as a string).
     */ // }}}
    void setValueFromOption(string _valueFromOption) {
        valueFromOption = _valueFromOption;
        return;
    }



    // {{{
    /*!
     * \brief	Get type.
     *
     * \return	type as a string.
     */ // }}}
    string getType() {
        return(type);
    }
    // {{{
    /*!
     * \brief	Set type.
     *
     * \param	_type	The new value for type (as a string).
     */ // }}}
    void setType(string _type) {
        type = _type;
        return;
    }



    // {{{
    /*!
     * \brief	Get value.
     *
     * \return	value as a string.
     */ // }}}
    string getValue() {
        return(value);
    }
    // {{{
    /*!
     * \brief	Set value.
     *
     * \param	_value	The new value for value (as a string).
     */ // }}}
    void setValue(string _value) {
        value = _value;
        return;
    }



    // {{{
    /*!
     * \brief	Get name.
     *
     * \return	name as a string.
     */ // }}}
    string getName() {
        return(name);
    }
    // {{{
    /*!
     * \brief	Set name.
     *
     * \param	_name	The new value for name (as a string).
     */ // }}}
    void setName(string _name) {
        name = _name;
        return;
    }


    // {{{
    /*!
     * \brief	Get isSet.
     *
     * \return	isSet as a string
     */ // }}}
    string getIsSet() {
        return(isSet);
    }
    // {{{
    /*!
     * \brief	Set isSet.
     *
     * \param	_isSet	The new value for isSet (as a string).
     */ // }}}
    void setIsSet(string _isSet) {
        isSet = _isSet;
        return;
    }




protected:
    string isSet ; 
    string name ; 
    string value ; 
    string type ; 
    string valueFromOption ; 

} ;

#endif

