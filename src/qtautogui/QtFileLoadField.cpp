// -*- C++ -*-
// FILE: "/mnt/sanfs/home/users/ndunn/tla/auto3--p690--1.4.6--base-0/src/qtautogui/QtFileLoadField.cpp"
// LAST MODIFICATION: "Tue, 24 Aug 2004 13:34:26 -0700 (ndunn)"
// (C) 2003 by Nathan Dunn, <ndunn@mac.com>
// $Id: QtFileLoadField.cpp,v 1.2 2004/01/13 20:43:36 ndunn Exp $

#include "QtFileLoadField.h"

#include "NameHandler.hpp" 
#include "CommandButton.hpp" 
#include "Renderer.hpp" 

#include <qfiledialog.h>
#include <qpushbutton.h>
#include <qlineedit.h>
#include <qframe.h>
#include <qlayout.h>


QtFileLoadField::QtFileLoadField(const QString & text, QWidget *parent, const char* name,Renderer *referenceObject, string newType) :   QFrame(   parent,name ) , CommandButton( NameHandler::getNameFromPath(name) ,NameHandler::getAllButNameFromPath(name) ,newType , referenceObject)
{
    connect(this,SIGNAL(lostFocus()),this,SLOT(updateOption())) ; 

    // add a QLineEdit and a QPushButton
    localLayout = new QHBoxLayout(this,5) ; 

//    theLabel  = new QLabel(text,this) ; 
    fileNameField = new QLineEdit(this) ;    
    loadFileNameButton = new QPushButton("choose ...",this) ;    

    localLayout->addWidget(fileNameField) ; 
    localLayout->addWidget(loadFileNameButton) ; 

    // connect QPushButton to the QFileDialog
    connect(loadFileNameButton,SIGNAL(clicked()),this,SLOT(loadFile())) ; 

}

void QtFileLoadField::loadFile() 
{
    QString fileName  = QFileDialog::getOpenFileName(fileNameField->text().latin1()) ; 
    // returns QString::null on cancel
    if(fileName != QString::null){
        fileNameField->setText(fileName) ; 
        updateOption() ;   
    }
}

string QtFileLoadField::getFileName() 
{
    return (fileNameField->text()).latin1() ; 
}

void QtFileLoadField::setFileName(string newFileName) 
{
    fileNameField->setText(newFileName.c_str()) ; 
}



void QtFileLoadField::updateOption()
{
        ((Renderer*) thisParent)->setOptionFromGui( this,(fileNameField->text()).latin1()) ; 
}




