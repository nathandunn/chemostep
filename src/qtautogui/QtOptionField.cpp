// -*- C++ -*-

#include "QtOptionField.h"

#include "Renderer.hpp" 

QtOptionField::QtOptionField(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QLineEdit ( text, parent, name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    setMaxLength(73) ;  // tinyxml or something seems to blow up if longer than this
//    connect(this,SIGNAL(lostFocus()),this,SLOT(updateOption())) ; 
    // added for the POWER64LINUX, but works for both
    connect(this,SIGNAL(textChanged(const QString &)),this,SLOT(updateOption(const QString &))) ; 
}

void QtOptionField::updateOption() 
{
        ((Renderer*) thisParent)->setOptionFromGui( this,text().ascii() ) ; 
}


void QtOptionField::updateOption(const QString & newText) 
{
        ((Renderer*) thisParent)->setOptionFromGui( this,newText.ascii()) ; 
}




