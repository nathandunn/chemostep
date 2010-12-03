// -*- C++ -*-
// FILE: "/home/ndunn/tla/auto3--nathanevo--1.4.1--base-0/src/qtautogui/QtIntField.cpp"
// LAST MODIFICATION: "Fri, 25 Jun 2004 15:12:10 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtIntField.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "QtIntField.h"

#include "CommandButton.hpp" 
#include "Renderer.hpp" 

#include <stdlib.h>

//QtIntField::QtIntField(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QSpinBox (  parent, name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
QtIntField::QtIntField(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QSpinBox ( INT_MIN,INT_MAX, 1 ,  parent, name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    setValue(0) ; 
    connect(this,SIGNAL(valueChanged(int)),this,SLOT(updateOption(int))) ; 
}

void QtIntField::updateOption(int updatedValue)
{
    char intChar[256] ; 
    sprintf(intChar,"%i",updatedValue) ; 
//    cout << "setting output option to: " << updatedValue << endl ; 
    ((Renderer*) thisParent)->setOptionFromGui( this,intChar ) ; 
}




