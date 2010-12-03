// -*- C++ -*-

#include "QtCommandButton.h" 

#include "QtFlatRenderer.h"
#include "CommandButton.hpp"
#include "Renderer.hpp"
#include "NameHandler.hpp"

#include <iostream>
using std::cout ; 
using std::endl ; 

QtCommandButton::QtCommandButton(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QPushButton( text, parent, name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    connect(this,SIGNAL(clicked()),this,SLOT(convertClicked())) ; 
    setFocusPolicy(QWidget::StrongFocus) ; 
}

void QtCommandButton::convertClicked() 
{
//    cout << "convertClicked " << endl ;
//    cout << "thisParent: " << thisParent << endl ; 
    ((Renderer*) thisParent)->doCommandButton(this) ; 
}





