// -*- C++ -*-
// FILE: "/Users/nathandunn/tla/auto3--dev--1.3.2--patch-8/src/qtautogui/QtBoolField.cpp"
// LAST MODIFICATION: "Wed, 17 Mar 2004 17:30:34 -0800 (nathandunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtBoolField.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "QtBoolField.h"

#include "NameHandler.hpp" 
#include "CommandButton.hpp" 
#include "Renderer.hpp" 
#include "InterfaceTypes.hpp" 

#include <qcheckbox.h>


QtBoolField::QtBoolField(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QCheckBox (  parent, name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    connect(this,SIGNAL(toggled(bool)),this,SLOT(updateOption(bool))) ; 
//    connect(this,SIGNAL(lostFocus()),this,SLOT(updateOption())) ; 
}

void QtBoolField::updateOption(bool newOption)
{
    if(newOption==true){
        ((Renderer*) thisParent)->setOptionFromGui( this,InterfaceTypes::OPT_BOOL_TRUE) ; 
    }
    else{
        ((Renderer*) thisParent)->setOptionFromGui( this,InterfaceTypes::OPT_BOOL_FALSE) ; 
    }

}




